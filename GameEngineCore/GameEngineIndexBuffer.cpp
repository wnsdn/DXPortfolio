#include "PreCompile.h"
#include "GameEngineIndexBuffer.h"

void GameEngineIndexBuffer::ResCreate(const void* _Data, size_t _IndexCount)
{
	IndexCount = static_cast<UINT>(_IndexCount);

	BufferInfo.BindFlags = D3D11_BIND_INDEX_BUFFER;
	BufferInfo.ByteWidth = static_cast<UINT>(IndexSize * IndexCount);
	BufferInfo.CPUAccessFlags = 0;
	BufferInfo.Usage = D3D11_USAGE_DEFAULT;

	D3D11_SUBRESOURCE_DATA Data{};
	Data.pSysMem = _Data;
	if (GameEngineCore::MainDevice.GetDevice()->CreateBuffer(&BufferInfo, &Data, &Buffer) == E_FAIL)
	{
		MsgBoxAssert("���ؽ� ���� ������ �����߽��ϴ�.");
		return;
	}
}

void GameEngineIndexBuffer::Setting()
{
	if (!Buffer)
	{
		MsgBoxAssert("����������� ���� ���ؽ� ���۸� ������ ���� �����ϴ�.");
	}

	GameEngineCore::MainDevice.GetContext()->IASetIndexBuffer(Buffer, Format, Offset);
}
