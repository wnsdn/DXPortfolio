#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"

#include "GameEngineShader.h"

void GameEngineConstantBufferSetter::Setting()
{
	if (!CPUDataPtr)
	{
		assert(false);
		return;
	}

	ShaderType Type = ParentShader->GetShaderType();

	Res->ChangeData(CPUDataPtr, DataSize);

	switch (Type)
	{
	case ShaderType::Vertex:
		Res->VSSetting(BindPoint);
		break;
	case ShaderType::Pixel:
		Res->PSSetting(BindPoint);
		break;
	default:
		assert(false);
		break;
	}
}

void GameEngineConstantBufferSetter::Reset()
{

}

void GameEngineTextureSetter::Setting()
{
	ShaderType Type = ParentShader->GetShaderType();

	switch (Type)
	{
	case ShaderType::Vertex:
		Res->VSSetting(BindPoint);
		break;
	case ShaderType::Pixel:
		Res->PSSetting(BindPoint);
		break;
	default:
		assert(false);
		break;
	}
}

void GameEngineTextureSetter::Reset()
{
}

void GameEngineSamplerSetter::Setting()
{
	ShaderType Type = ParentShader->GetShaderType();

	switch (Type)
	{
	case ShaderType::Vertex:
		Res->VSSetting(BindPoint);
		break;
	case ShaderType::Pixel:
		Res->PSSetting(BindPoint);
		break;
	default:
		assert(false);
		break;
	}
}

void GameEngineSamplerSetter::Reset()
{

}

GameEngineShaderResHelper::GameEngineShaderResHelper()
{

}

GameEngineShaderResHelper::~GameEngineShaderResHelper()
{

}

void GameEngineShaderResHelper::ShaderResCheck(std::string _FunctionName, GameEngineShader* _Shader, ID3DBlob* _CompileCode)
{
	if (!_CompileCode)
	{
		assert(false);
		return;
	}

	ID3D11ShaderReflection* CompileInfo = nullptr;
	Check(D3DReflect(_CompileCode->GetBufferPointer(), _CompileCode->GetBufferSize(), IID_ID3D11ShaderReflection, reinterpret_cast<void**>(&CompileInfo)));

	D3D11_SHADER_DESC Info{};
	CompileInfo->GetDesc(&Info);

	D3D11_SHADER_INPUT_BIND_DESC ResDesc{};
	for (UINT i = 0; i < Info.BoundResources; ++i)
	{
		CompileInfo->GetResourceBindingDesc(i, &ResDesc);
		std::string Name = ResDesc.Name;

		D3D_SHADER_INPUT_TYPE Type = ResDesc.Type;
		switch (Type)
		{
		case D3D_SIT_CBUFFER:
		{
			ID3D11ShaderReflectionConstantBuffer* BufferInfo = CompileInfo->GetConstantBufferByName(ResDesc.Name);

			D3D11_SHADER_BUFFER_DESC BufferDesc{};
			BufferInfo->GetDesc(&BufferDesc);

			auto CBuffer = GameEngineConstantBuffer::CreateAndFind(BufferDesc.Size, Name, BufferDesc);

			_FunctionName;
			GameEngineConstantBufferSetter NewSetter;
			NewSetter.ParentShader = _Shader;
			NewSetter.Res = CBuffer;
			NewSetter.Name = Name;
			NewSetter.BindPoint = ResDesc.BindPoint;
			NewSetter.DataSize = BufferDesc.Size;
			ConstantBufferSetters.insert(std::make_pair(Name, NewSetter));

			break;
		}
		case D3D_SIT_TEXTURE:
		{
			auto Res = GameEngineTexture::Find("NSet.png");

			_FunctionName;
			GameEngineTextureSetter NewSetter;
			NewSetter.ParentShader = _Shader;
			NewSetter.Res = Res;
			NewSetter.Name = Name;
			NewSetter.BindPoint = ResDesc.BindPoint;
			TextureSetters.insert(std::make_pair(Name, NewSetter));

			break;
		}
		case D3D_SIT_SAMPLER:
		{
			auto Res = GameEngineSampler::Find("Sampler");

			_FunctionName;
			GameEngineSamplerSetter NewSetter;
			NewSetter.ParentShader = _Shader;
			NewSetter.Res = Res;
			NewSetter.Name = Name;
			NewSetter.BindPoint = ResDesc.BindPoint;
			SamplerSetters.insert(std::make_pair(Name, NewSetter));

			break;
		}
		default:
			break;
		}
	}
}

void GameEngineShaderResHelper::ShaderResCopy(GameEngineShader* _Shader)
{
	auto& OtherConstantBufferSetters = _Shader->ResHelper.ConstantBufferSetters;
	auto& OtherTextureSetters = _Shader->ResHelper.TextureSetters;
	auto& OtherSamplerSetters = _Shader->ResHelper.SamplerSetters;

	for (auto& Pair : OtherConstantBufferSetters)
	{
		ConstantBufferSetters.insert(Pair);
	}
	for (auto& Pair : OtherTextureSetters)
	{
		TextureSetters.insert(Pair);
	}
	for (auto& Pair : OtherSamplerSetters)
	{
		SamplerSetters.insert(Pair);
	}

	for (auto& Pair : OtherTextureSetters)
	{
		std::string SamplerName = Pair.first + "SAMPLER";

		if (IsSampler(SamplerName))
		{
			auto Sampler = Pair.second.Res->GetBaseSampler();
			SetSampler(SamplerName, Sampler);
		}
	}
}

void GameEngineShaderResHelper::AllShaderResourcesSetting()
{
	for (auto& Pair : ConstantBufferSetters)
	{
		if (!Pair.second.Res)
		{
			assert(false);
			return;
		}

		Pair.second.Setting();
	}
	for (auto& Pair : TextureSetters)
	{
		if (!Pair.second.Res)
		{
			assert(false);
			return;
		}

		Pair.second.Setting();
	}
	for (auto& Pair : SamplerSetters)
	{
		if (!Pair.second.Res)
		{
			assert(false);
			return;
		}

		Pair.second.Setting();
	}
}

void GameEngineShaderResHelper::SetConstantBufferLink(std::string_view _Name, const void* _Data, size_t _Size)
{
	if (!IsConstantBuffer(_Name))
	{
		assert(false);
		return;
	}

	std::string Name{ _Name };
	auto NameStartIter = ConstantBufferSetters.lower_bound(Name);
	auto NameEndIter = ConstantBufferSetters.upper_bound(Name);

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		GameEngineConstantBufferSetter& Setter = NameStartIter->second;
		if (Setter.DataSize != _Size)
		{
			assert(false);
		}

		Setter.CPUDataPtr = _Data;
	}
}

void GameEngineShaderResHelper::SetTexture(std::string_view _Name, std::string_view _TextureName)
{
	auto Texture = GameEngineTexture::Find(_TextureName);
	if (!Texture)
	{
		assert(false);
		return;
	}

	SetTexture(_Name, Texture);
}

void GameEngineShaderResHelper::SetTexture(std::string_view _Name, std::shared_ptr<GameEngineTexture> _Texture)
{
	if (!IsTexture(_Name))
	{
		assert(false);
		return;
	}

	std::string Name{ _Name };
	auto NameStartIter = TextureSetters.lower_bound(Name);
	auto NameEndIter = TextureSetters.upper_bound(Name);

	std::string SamplerName = NameStartIter->first + "SAMPLER";
	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		auto& Setter = NameStartIter->second;
		Setter.Res = _Texture;

		if (IsSampler(SamplerName))
		{
			auto Sampler = Setter.Res->GetBaseSampler();
			SetSampler(SamplerName, Sampler);
		}
	}
}

void GameEngineShaderResHelper::SetSampler(std::string_view _Name, std::shared_ptr<GameEngineSampler> _TextureSampler)
{
	if (!IsSampler(_Name))
	{
		assert(false);
		return;
	}

	std::string Name{ _Name };
	auto NameStartIter = SamplerSetters.lower_bound(Name);
	auto NameEndIter = SamplerSetters.upper_bound(Name);

	for (; NameStartIter != NameEndIter; ++NameStartIter)
	{
		auto& Setter = NameStartIter->second;
		Setter.Res = _TextureSampler;
	}
}

void GameEngineShaderResHelper::ResClear()
{
	ConstantBufferSetters.clear();
	TextureSetters.clear();
	SamplerSetters.clear();
}
