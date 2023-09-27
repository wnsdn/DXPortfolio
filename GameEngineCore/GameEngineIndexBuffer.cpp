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
		assert(false);
		return;
	}
}

void GameEngineIndexBuffer::Setting()
{
	if (!Buffer)
	{
		assert(false);
		return;
	}

	GameEngineCore::GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
}
