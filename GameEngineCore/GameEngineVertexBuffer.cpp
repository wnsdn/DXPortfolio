#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"

void GameEngineVertexBuffer::ResCreate(const void* _Data, size_t _VertexSize, size_t _VertexCount)
{
	VertexSize = static_cast<UINT>(_VertexSize);
	VertexCount = static_cast<UINT>(_VertexCount);

	D3D11_SUBRESOURCE_DATA Data{};
	Data.pSysMem = _Data;

	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferInfo.ByteWidth = VertexSize * VertexCount;
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	HRESULT Hresult = GameEngineCore::GetDevice()->
		CreateBuffer(&BufferInfo, &Data, &Buffer);
	if (Hresult == E_FAIL)
	{
		assert(false);
		return;
	}
}

void GameEngineVertexBuffer::Setting()
{
	if (!Buffer)
	{
		assert(false);
		return;
	}

	GameEngineCore::GetContext()->IASetVertexBuffers(0, 1, &Buffer, &VertexSize, &Offset);
}
