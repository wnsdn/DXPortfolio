#include "PreCompile.h"
#include "GameEngineVertexBuffer.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11")

void GameEngineVertexBuffer::ResCreate(const void* _Data, size_t _VertexSize, size_t _VertexCount)
{
	size_t VertexSize = _VertexSize;
	size_t VertexCount = _VertexCount;

	D3D11_SUBRESOURCE_DATA Data{};
	Data.pSysMem = _Data;

	BufferInfo.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	BufferInfo.ByteWidth = static_cast<UINT>(VertexSize * VertexCount);
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	HRESULT Hr = GameEngineCore::MainDevice.GetDevice()->CreateBuffer(
		&BufferInfo, &Data, &Buffer);
	if (FAILED(Hr))
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}
}

void GameEngineVertexBuffer::Setting()
{
	if (!Buffer)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	GameEngineCore::MainDevice.GetContext()->IASetVertexBuffers(0, 1, &Buffer,
		&VertexSize, &Offset);
}
