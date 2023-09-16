#pragma once
#include "GameEngineTexture.h"

class GameEngineRenderTarget : public GameEngineResources<GameEngineRenderTarget>
{
public:
	GameEngineRenderTarget() {}
	~GameEngineRenderTarget() {}
	GameEngineRenderTarget(const GameEngineRenderTarget&) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&&) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&&) noexcept = delete;

	static std::shared_ptr<GameEngineRenderTarget> Create(std::shared_ptr<GameEngineTexture> _Texture,
		const float4& _Color = float4::BLUE)
	{
		auto NewRes = CreateRes();
		NewRes->ClearColor.push_back(_Color);
		NewRes->Textures.push_back(_Texture);
		_Texture->CreateRenderTargetView();
		NewRes->RTV.push_back(_Texture->GetRTV());
		return NewRes;
	}

	void Clear();
	void Setting();

	void SetClearColor(const float4& _Color, int _Index = 0)
	{
		ClearColor[_Index] = _Color;
	}
protected:

private:
	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<struct ID3D11RenderTargetView*> RTV;
	std::vector<float4> ClearColor;
};