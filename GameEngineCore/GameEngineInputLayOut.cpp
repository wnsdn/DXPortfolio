#include "PreCompile.h"
#include "GameEngineInputLayout.h"

UINT GameEngineInputLayoutInfo::FormatSize(DXGI_FORMAT _Format)
{
	switch (_Format)
	{
	case DXGI_FORMAT_R32G32B32A32_TYPELESS:
	case DXGI_FORMAT_R32G32B32A32_FLOAT:
	case DXGI_FORMAT_R32G32B32A32_UINT:
	case DXGI_FORMAT_R32G32B32A32_SINT:
		return 16;
	case DXGI_FORMAT_R32G32B32_TYPELESS:
	case DXGI_FORMAT_R32G32B32_FLOAT:
	case DXGI_FORMAT_R32G32B32_UINT:
	case DXGI_FORMAT_R32G32B32_SINT:
		return 12;
	default:
		assert(false);
		return -1;
	}
}

void GameEngineInputLayoutInfo::AddInputLayoutDesc(LPCSTR _SemanticName, DXGI_FORMAT _Format, UINT _SemanticIndex, UINT _AlignedByteOffset, D3D11_INPUT_CLASSIFICATION _InputSlotClass, UINT _InputSlot, UINT _InstanceDataStepRate)
{
	D3D11_INPUT_ELEMENT_DESC Desc{};
	Desc.SemanticName = _SemanticName;
	Desc.SemanticIndex = _SemanticIndex;
	Desc.Format = _Format;
	Desc.InputSlot = _InputSlot;
	Desc.InputSlotClass = _InputSlotClass;
	Desc.InstanceDataStepRate = _InstanceDataStepRate;

	if (_AlignedByteOffset == -1)
	{
		Desc.AlignedByteOffset = Offset;
	}
	else
	{
		Desc.AlignedByteOffset = _AlignedByteOffset;
	}

	Offset += FormatSize(_Format);
	Infos.push_back(Desc);
}

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"

GameEngineInputLayout::~GameEngineInputLayout()
{
	SafeRelease(Layout);
}

void GameEngineInputLayout::ResCreate(std::shared_ptr<GameEngineVertexBuffer> _Buffer, std::shared_ptr<GameEngineVertexShader> _Shader)
{
	auto& Infos = _Buffer->VertexInfoPtr->Infos;
	Check(GameEngineCore::GetDevice()->CreateInputLayout(&Infos[0], static_cast<UINT>(Infos.size()), _Shader->BinaryCode->GetBufferPointer(), _Shader->BinaryCode->GetBufferSize(), &Layout))
}

void GameEngineInputLayout::Setting()
{
	if (!Layout)
	{
		assert(false);
		return;
	}

	GameEngineCore::GetContext()->IASetInputLayout(Layout);
}
