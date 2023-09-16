#include "PreCompile.h"
#include "GameEngineBlend.h"

GameEngineBlend::GameEngineBlend()
{
}

GameEngineBlend::~GameEngineBlend()
{
	SafeRelease(State);
}

void GameEngineBlend::ResCreate(const D3D11_BLEND_DESC& _Desc)
{
	Desc = _Desc;
	Check(GameEngineCore::GetDevice()->CreateBlendState(&_Desc, &State));
}

void GameEngineBlend::Setting()
{
	if (!State)
	{
		assert(false);
	}

	GameEngineCore::GetContext()->OMSetBlendState(State, Factor, Mask);
}
