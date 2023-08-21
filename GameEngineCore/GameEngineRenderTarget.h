#pragma once
#include <vector>
#include "GameEngineTexture.h"

class GameEngineRenderTarget : public GameEngineResources<GameEngineRenderTarget>
{
private:
	//왜 텍스쳐 안에 RTV가 있는데 따로 또 vector<RTV>를 했는지 잘 모르겠음...
	std::vector<std::shared_ptr<GameEngineTexture>> Textures;
	std::vector<struct ID3D11RenderTargetView*> RTV;
	std::vector<float4> ClearColor;
protected:
public:
	static std::shared_ptr<GameEngineRenderTarget> Create(std::shared_ptr<GameEngineTexture> _Texture,
		const float4& _Color = float4::BLUE)
	{
		std::shared_ptr<GameEngineRenderTarget> NewRes = GameEngineResources::CreateRes();
		NewRes->ClearColor.push_back(_Color);
		NewRes->Textures.push_back(_Texture);
		_Texture->CreateRenderTargetView();
		NewRes->RTV.push_back(_Texture->GetRTV());
		return NewRes;
	}

	void Clear();
	void Setting();

#pragma region Constructor
	GameEngineRenderTarget() {}
	~GameEngineRenderTarget() {}
	GameEngineRenderTarget(const GameEngineRenderTarget&) = delete;
	GameEngineRenderTarget(GameEngineRenderTarget&&) noexcept = delete;
	GameEngineRenderTarget& operator=(const GameEngineRenderTarget&) = delete;
	GameEngineRenderTarget& operator=(GameEngineRenderTarget&&) noexcept = delete;
#pragma endregion
};