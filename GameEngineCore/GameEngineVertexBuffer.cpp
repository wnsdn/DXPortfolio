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
		MsgBoxAssert("버텍스 버퍼 생성에 실패했습니다.");
		return;
	}
}

void GameEngineVertexBuffer::Setting()
{
	if (!Buffer)
	{
		MsgBoxAssert("만들어지지도 않은 버텍스 버퍼를 세팅할 수는 없습니다.");
		return;
	}

	GameEngineCore::GetContext()->
		IASetVertexBuffers(0, 1, &Buffer, &VertexSize, &Offset);
}
