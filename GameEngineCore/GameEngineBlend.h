#pragma once
#include "GameEngineResources.h"

class GameEngineBlend : public GameEngineResources<GameEngineBlend>
{
public:
	GameEngineBlend();
	~GameEngineBlend();
	GameEngineBlend(const GameEngineBlend&) = delete;
	GameEngineBlend(GameEngineBlend&&) noexcept = delete;
	void operator=(const GameEngineBlend&) = delete;
	void operator=(GameEngineBlend&&) noexcept = delete;

	static std::shared_ptr<GameEngineBlend> Create(std::string_view _Name, const D3D11_BLEND_DESC& _Desc)
	{
		auto Res = CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting();
protected:
	void ResCreate(const D3D11_BLEND_DESC& _Desc);
private:
	D3D11_BLEND_DESC Desc{};
	ID3D11BlendState* State = nullptr;
	float4 Factor;
	UINT Mask = 0xffffffff;
};
