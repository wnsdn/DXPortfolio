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
		MsgBoxAssert("레스터라이저 세팅을 만드는데 실패했습니다.");
		return;
	}
}

void GameEngineRasterizer::Setting()
{
	if (!State)
	{
		MsgBoxAssert("레스터 라이저 세팅이 존재하지 앟는데 세팅하려고 했습니다.");
		return;
	}

	GameEngineCore::MainDevice.GetContext()->RSSetState(State);
}
