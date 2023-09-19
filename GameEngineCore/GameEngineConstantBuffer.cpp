#include "PreCompile.h"
#include "GameEngineConstantBuffer.h"

std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> GameEngineConstantBuffer::ConstantBuffers;

void GameEngineConstantBuffer::ResCreate(int _ByteSize)
{
	BufferInfo.BindFlags = D3D11_BIND_CONSTANT_BUFFER;
	BufferInfo.ByteWidth = _ByteSize;
	BufferInfo.CPUAccessFlags = D3D11_CPU_ACCESS_WRITE;
	BufferInfo.Usage = D3D11_USAGE_DYNAMIC;

	Check(GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, nullptr, &Buffer));
}

void GameEngineConstantBuffer::ChangeData(const void* _Data, UINT _Size)
{
	if (!_Data)
	{
		MsgBoxAssert(Name + "nullptr인 데이터를 세팅하려고 했습니다.");
		return;
	}

	if (BufferInfo.ByteWidth != _Size)
	{
		MsgBoxAssert(Name + "크기가 다른 데이터로 상수버퍼를 세팅하려고 했습니다.");
		return;
	}

	D3D11_MAPPED_SUBRESOURCE Data{};

	GameEngineCore::GetContext()->Map(Buffer, 0, D3D11_MAP_WRITE_DISCARD, 0, &Data);

	if (!Data.pData)
	{
		MsgBoxAssert(Name + "버퍼 수정 권한을 얻어내지 못했습니다.");
		return;
	}

	memcpy_s(Data.pData, BufferInfo.ByteWidth, _Data, BufferInfo.ByteWidth);

	GameEngineCore::GetContext()->Unmap(Buffer, 0);
}

void GameEngineConstantBuffer::Setting(UINT _Slot)
{
	GameEngineCore::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
	/*switch (Type)
	{
	case ShaderType::None:
		break;
	case ShaderType::Vertex:
		GameEngineCore::GetContext()->VSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	case ShaderType::Hull:
		break;
	case ShaderType::Tessellator:
		break;
	case ShaderType::Domain:
		break;
	case ShaderType::Geometry:
		break;
	case ShaderType::Pixel:
		GameEngineCore::GetContext()->PSSetConstantBuffers(_Slot, 1, &Buffer);
		break;
	case ShaderType::Max:
		break;
	default:
		break;
	}*/
}
