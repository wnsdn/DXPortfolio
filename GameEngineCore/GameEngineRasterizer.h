#pragma once
#include "GameEngineResources.h"

class GameEngineRasterizer : public GameEngineResources<GameEngineRasterizer>
{
private:
	D3D11_RASTERIZER_DESC Desc{};
	ID3D11RasterizerState* State = nullptr;
protected:
	void ResCreate(const D3D11_RASTERIZER_DESC& _Desc);
public:
	static std::shared_ptr<GameEngineRasterizer> Create(std::string_view _Name, const D3D11_RASTERIZER_DESC& _Desc)
	{
		auto Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(_Desc);
		return Res;
	}

	void Setting();

	GameEngineRasterizer() {}
	~GameEngineRasterizer();
	GameEngineRasterizer(const GameEngineRasterizer&) = delete;
	GameEngineRasterizer(GameEngineRasterizer&&) noexcept = delete;
	void operator=(const GameEngineRasterizer&) = delete;
	void operator=(GameEngineRasterizer&&) noexcept = delete;
};

