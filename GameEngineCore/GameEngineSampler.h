#pragma once
#include "GameEngineResources.h"

class GameEngineSampler : public GameEngineResources<GameEngineSampler>
{
public:
	GameEngineSampler() {}
	~GameEngineSampler();
	GameEngineSampler(const GameEngineSampler&) = delete;
	GameEngineSampler(GameEngineSampler&&) noexcept = delete;
	void operator=(const GameEngineSampler&) = delete;
	void operator=(GameEngineSampler&&) noexcept = delete;

	static std::shared_ptr<GameEngineSampler> Create(std::string_view _Name, const D3D11_SAMPLER_DESC& _Desc)
	{
		auto Res = CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	static std::shared_ptr<GameEngineSampler> Create(D3D11_FILTER _Filter, D3D11_TEXTURE_ADDRESS_MODE _Address)
	{
		if (!OptionSamplers.contains(_Filter))
		{
			OptionSamplers[_Filter];
		}

		auto& Add = OptionSamplers[_Filter];
		if (Add.contains(_Address))
		{
			return Add[_Address];
		}

		D3D11_SAMPLER_DESC Desc{};
		Desc.Filter = _Filter;
		Desc.AddressU = _Address;
		Desc.AddressV = _Address;
		Desc.AddressW = _Address;
		Desc.MaxAnisotropy = 1;
		Desc.ComparisonFunc = D3D11_COMPARISON_ALWAYS;
		Desc.MaxLOD = FLT_MAX;
		Desc.MinLOD = -FLT_MAX;

		auto NewSampler = std::make_shared<GameEngineSampler>();
		NewSampler->ResCreate(Desc);
		Add[_Address] = NewSampler;
		return NewSampler;
	}

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
protected:
	void ResCreate(const D3D11_SAMPLER_DESC& _Desc);
private:
	static std::map<D3D11_FILTER, std::map<D3D11_TEXTURE_ADDRESS_MODE, std::shared_ptr<GameEngineSampler>>> OptionSamplers;

	D3D11_SAMPLER_DESC Desc{};
	ID3D11SamplerState* State = nullptr;
};

