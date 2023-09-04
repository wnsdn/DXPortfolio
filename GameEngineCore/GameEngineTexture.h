#pragma once
#include "GameEngineResources.h"

#include "..\\GameEngineCore\\ThirdParty\\DirectXTex\\inc\\DirectXTex.h"

struct GameEngineColor
{
	static const GameEngineColor RED;

	unsigned char R = 0;
	unsigned char G = 0;
	unsigned char B = 0;
	unsigned char A = 0;

	bool operator==(const GameEngineColor& _Other) const
	{
		return memcmp(this, &_Other, sizeof(GameEngineColor)) == 0;
	}
};

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

	static std::shared_ptr<GameEngineTexture> Load(std::string_view _Path)
	{
		GameEnginePath Path;
		Path.SetPath(_Path);
		return Load(Path.GetPath(), Path.GetFilename());
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
	float4 GetScale() const
	{
		return { static_cast<float>(Desc.Width), static_cast<float>(Desc.Height), 1.0f, 0.0f };
	}
	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor) const
	{
		return GetColor(_Pos.iX(), _Pos.iY(), _DefaultColor);
	}
	GameEngineColor GetColor(unsigned int _X, unsigned int _Y, GameEngineColor _DefaultColor) const;

	void CreateRenderTargetView();
	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);

	GameEngineTexture() : Data{}, Desc{} {}
	~GameEngineTexture();
	GameEngineTexture(const GameEngineTexture&) = delete;
	GameEngineTexture(GameEngineTexture&&) noexcept = delete;
	void operator=(const GameEngineTexture&) = delete;
	void operator=(GameEngineTexture&&) noexcept = delete;
};