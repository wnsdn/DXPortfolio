#include "PreCompile.h"
#include "GameEngineRasterizer.h"

GameEngineRasterizer::~GameEngineRasterizer()
{
	SafeRelease(State);
}

void GameEngineRasterizer::ResCreate(const D3D11_RASTERIZER_DESC& _Desc)
{
	Desc = _Desc;
	Check(GameEngineCore::GetDevice()->CreateRasterizerState(&_Desc, &State));
}

void GameEngineRasterizer::Setting()
{
	if (!State)
	{
		assert(false);
		return;
	}

	GameEngineCore::GetContext()->RSSetState(State);
}
