#pragma once
#include "GameEngineResources.h"

#include "..\\GameEngineCore\\ThirdParty\\DirectXTex\\inc\\DirectXTex.h"

class GameEngineTexture : public GameEngineResources<GameEngineTexture>
{
private:
	D3D11_TEXTURE2D_DESC Desc;

	ID3D11Texture2D* Texture2D = nullptr;

	ID3D11RenderTargetView* RTV = nullptr;
	ID3D11ShaderResourceView* SRV = nullptr;

	DirectX::TexMetadata Data;
	DirectX::ScratchImage Image;

	void ResLoad(std::string_view _Path);
public:
	static std::shared_ptr<GameEngineTexture> Create(ID3D11Texture2D* _Res)
	{
		auto NewRes = CreateRes();
		NewRes->Texture2D = _Res;
		return NewRes;
	}

	static std::shared_ptr<GameEngineTexture> Load(std::string_view _Path, std::string_view _Name)
	{
		auto NewRes = CreateRes(_Name);
		NewRes->ResLoad(_Path);
		return NewRes;
	}

	ID3D11RenderTargetView* GetRTV() const
	{
		return RTV;
	}
	ID3D11ShaderResourceView* GetSRV() const
	{
		return SRV;
	}

	float4 GetScale()
	{
		return { static_cast<float>(Desc.Width), static_cast<float>(Desc.Height), 1.0f, 0.0f };
	}

	void CreateRenderTargetView();

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

	GameEngineTexture() {}
	~GameEngineTexture();
	GameEngineTexture(const GameEngineTexture&) = delete;
	GameEngineTexture(GameEngineTexture&&) noexcept = delete;
	void operator=(const GameEngineTexture&) = delete;
	void operator=(GameEngineTexture&&) noexcept = delete;
};