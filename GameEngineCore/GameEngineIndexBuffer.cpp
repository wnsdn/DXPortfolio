#include "PreCompile.h"
#include "GameEngineIndexBuffer.h"

void GameEngineIndexBuffer::ResCreate(const void* _Data, size_t _IndexCount)
{
	IndexCount = static_cast<UINT>(_IndexCount);

	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.ByteWidth = static_cast<UINT>(IndexSize * IndexCount);

	D3D11_SUBRESOURCE_DATA Data{};
	Data.pSysMem = _Data;

	if (GameEngineCore::GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer) == E_FAIL)
	{
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void GameEngineIndexBuffer::Setting()
{
	if (!Buffer)
	{
		MsgBoxAssert("만들어지지도 않은 버텍스 버퍼를 세팅할 수는 없습니다.");
	}

	GameEngineCore::GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
}
