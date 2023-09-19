#include "PreCompile.h"
#include "GameEngineShaderResHelper.h"

void GameEngineConstantBufferSetter::Setting()
{

}

void GameEngineConstantBufferSetter::Reset()
{

}

void GameEngineTextureSetter::Setting()
{

}

void GameEngineTextureSetter::Reset()
{

}

void GameEngineSamplerSetter::Setting()
{

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

void GameEngineShaderResHelper::ShaderResCheck(std::string _FunctionName, ID3DBlob* _CompileCode)
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
}
