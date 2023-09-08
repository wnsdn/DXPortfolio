#pragma once
#include "GameEngineResources.h"

class GameEngineSampler : public GameEngineResources<GameEngineSampler>
{
private:
	D3D11_SAMPLER_DESC Desc{};
	ID3D11SamplerState* State = nullptr;
protected:
	void ResCreate(const D3D11_SAMPLER_DESC& _Desc);
public:
	static std::shared_ptr<GameEngineSampler> Create(std::string_view _Name, const D3D11_SAMPLER_DESC& _Desc)
	{
		auto Res = CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

	GameEngineSampler() {}
	~GameEngineSampler();
	GameEngineSampler(const GameEngineSampler&) = delete;
	GameEngineSampler(GameEngineSampler&&) noexcept = delete;
	void operator=(const GameEngineSampler&) = delete;
	void operator=(GameEngineSampler&&) noexcept = delete;
};

