#pragma once
#include "GameEngineResources.h"

class GameEngineTexture : public GameEngineResources<GameEngineTexture>
{
private:
	struct ID3D11Texture2D* Texture2D = nullptr;
	struct ID3D11RenderTargetView* RTV = nullptr;
protected:
public:
	static std::shared_ptr<GameEngineTexture> Create(struct ID3D11Texture2D* _Res)
	{
		std::shared_ptr<GameEngineTexture> NewRes = CreateRes();
		NewRes->Texture2D = _Res;
		return NewRes;
	}

	struct ID3D11RenderTargetView* GetRTV() const
	{
		return RTV;
	}

	void CreateRenderTargetView();

#pragma region Constructor
	GameEngineTexture() {}
	~GameEngineTexture();
	GameEngineTexture(const GameEngineTexture&) = delete;
	GameEngineTexture(GameEngineTexture&&) noexcept = delete;
	GameEngineTexture& operator=(const GameEngineTexture&) = delete;
	GameEngineTexture& operator=(GameEngineTexture&&) noexcept = delete;
#pragma endregion
};