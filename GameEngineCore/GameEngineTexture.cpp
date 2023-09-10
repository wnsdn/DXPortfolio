#include "PreCompile.h"
#include "GameEngineTexture.h"

#include "GameEngineCore.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif

const GameEngineColor GameEngineColor::RED{ 255, 0, 0, 255 };

GameEngineTexture::~GameEngineTexture()
{
	SafeRelease(SRV);
	SafeRelease(RTV);
	SafeRelease(Texture2D);
}

void GameEngineTexture::ResLoad(std::string_view _Path)
{
	GameEnginePath NewPath;
	NewPath.SetPath(_Path);

	std::string Ext = NewPath.GetExtension();
	std::wstring wPath = GameEngineString::AnsiToUnicode(_Path);

	if (Ext == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image))
		{
			assert(false);
		}
	}
	else if (Ext == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image))
		{
			assert(false);
		}
	}
	else if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		assert(false);
	}

	Check(DirectX::CreateShaderResourceView(GameEngineCore::GetDevice(), Image.GetImages(), Image.GetImageCount(), Image.GetMetadata(), &SRV));

	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);
}

GameEngineColor GameEngineTexture::GetColor(unsigned int _X, unsigned int _Y, GameEngineColor _DefaultColor) const
{
	if (_X < 0 || _X >= GetScale().uiX() ||
		_Y < 0 || _Y >= GetScale().uiY())
	{
		return _DefaultColor;
	}

	DXGI_FORMAT Fmt = Image.GetMetadata().format;

	unsigned char* Ptr = Image.GetPixels();

	switch (Fmt)
	{
	case DXGI_FORMAT_R8G8B8A8_TYPELESS:
	case DXGI_FORMAT_R8G8B8A8_UNORM:
	{
		GameEngineColor ResultColor;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4;
		ResultColor.B = Ptr[0];
		ResultColor.G = Ptr[1];
		ResultColor.R = Ptr[2];
		ResultColor.A = Ptr[3];
		return ResultColor;
	}
	case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
	case DXGI_FORMAT_R8G8B8A8_UINT:
	case DXGI_FORMAT_R8G8B8A8_SNORM:
	case DXGI_FORMAT_R8G8B8A8_SINT:
	{
		GameEngineColor ResultColor;
		Ptr += ((_Y * GetScale().iX()) + _X) * 4;
		ResultColor.R = Ptr[0];
		ResultColor.G = Ptr[1];
		ResultColor.B = Ptr[2];
		ResultColor.A = Ptr[3];
		return ResultColor;
	}
	default:
		MsgBoxAssert("색깔을 처리하는 함수를 만들지 없는 포맷입니다");
		break;
	}

	return _DefaultColor;
}

void GameEngineTexture::CreateRenderTargetView()
{
	if (RTV)
	{
		return;
	}
	if (Texture2D)
	{
		GameEngineCore::GetDevice()->CreateRenderTargetView(Texture2D, nullptr, &RTV);
	}
}

void GameEngineTexture::VSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->VSSetShaderResources(_Slot, 1, &SRV);
}

void GameEngineTexture::PSSetting(UINT _Slot)
{
	GameEngineCore::GetContext()->PSSetShaderResources(_Slot, 1, &SRV);
}
