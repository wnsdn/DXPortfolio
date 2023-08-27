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
		break;
	}

	MsgBoxAssert("처리할수 없는 포맷을 사용했습니다.");
	return -1;
}

void GameEngineInputLayoutInfo::AddInputLayoutDesc(
	LPCSTR _SemanticName,
	DXGI_FORMAT _Format,
	UINT _SemanticIndex,
	UINT _AlignedByteOffset,
	D3D11_INPUT_CLASSIFICATION _InputSlotClass,
	UINT _InputSlot,
	UINT _InstanceDataStepRate)
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
	if (Layout)
	{
		Layout->Release();
		Layout = nullptr;
	}
}

void GameEngineInputLayout::ResCreate(
	std::shared_ptr<GameEngineVertexBuffer> _Buffer,
	std::shared_ptr<GameEngineVertexShader> _Shader)
{
	auto& Infos = _Buffer->VertexInfoPtr->Infos;

	GameEngineCore::GetDevice()->CreateInputLayout(
		&Infos[0],
		static_cast<UINT>(Infos.size()),
		_Shader->BinaryCode->GetBufferPointer(),
		_Shader->BinaryCode->GetBufferSize(),
		&Layout);
	if (!Layout)
	{
		MsgBoxAssert("레이아웃 생성에 실패했습니다.");
		return;
	}
}

void GameEngineInputLayout::Setting()
{
	if (!Layout)
	{
		MsgBoxAssert("만들어지지도 않은 버텍스 버퍼를 세팅할 수는 없습니다.");
		return;
	}

	GameEngineCore::GetContext()->IASetInputLayout(Layout);
}
