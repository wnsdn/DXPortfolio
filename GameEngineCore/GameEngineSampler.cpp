#include "PreCompile.h"
#include "GameEngineSampler.h"

std::map<D3D11_FILTER, std::map<D3D11_TEXTURE_ADDRESS_MODE, std::shared_ptr<GameEngineSampler>>> GameEngineSampler::OptionSamplers;

GameEngineSampler::~GameEngineSampler()
{
	SafeRelease(State);
}

void GameEngineSampler::ResCreate(const D3D11_SAMPLER_DESC& _Desc)
{
	Desc = _Desc;
	GameEngineCore::GetDevice()->CreateSamplerState(&_Desc, &State);
}

void GameEngineSampler::VSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->VSSetSamplers(_Slot, 1, &State);
}

void GameEngineSampler::PSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->PSSetSamplers(_Slot, 1, &State);
}
