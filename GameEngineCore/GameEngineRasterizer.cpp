#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::~GameEngineRasterizer()
{
	if (State)
	{
		State->Release();
		State = nullptr;
	}
}

void GameEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Desc)
{
	Desc = _Desc;
	if (GameEngineCore::MainDevice.GetDevice()->CreateRasterizerState(&_Desc, &State) == E_FAIL)
	{
		MsgBoxAssert("�����Ͷ����� ������ ����µ� �����߽��ϴ�.");
		return;
	}
}

void GameEngineRasterizer::Setting()
{
	if (!State)
	{
		MsgBoxAssert("������ ������ ������ �������� �۴µ� �����Ϸ��� �߽��ϴ�.");
		return;
	}

	GameEngineCore::MainDevice.GetContext()->RSSetState(State);
}
