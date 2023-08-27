#include "PreCompile.h"
#include "GameEngineTexture.h"

#include "GameEngineCore.h"

#ifdef _DEBUG
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Debug\\DirectXTex.lib")
#else
#pragma comment(lib, "..\\GameEngineCore\\ThirdParty\\DirectXTex\\lib\\Release\\DirectXTex.lib")
#endif


GameEngineTexture::~GameEngineTexture()
{
	SafeRelease(SRV);
	SafeRelease(RTV);
	SafeRelease(Texture2D);
}

void GameEngineTexture::ResLoad(std::string_view _Path)
{
	GameEnginePath NewPath = _Path;
	std::string Ext = NewPath.GetExtension();
	std::wstring wPath = GameEngineString::AnsiToUnicode(_Path);

	if (Ext == ".DDS")
	{
		if (S_OK != DirectX::LoadFromDDSFile(wPath.c_str(), DirectX::DDS_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
		}
	}
	else if (Ext == ".TGA")
	{
		if (S_OK != DirectX::LoadFromTGAFile(wPath.c_str(), DirectX::TGA_FLAGS_NONE, &Data, Image))
		{
			MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
		}

	}
	else if (S_OK != DirectX::LoadFromWICFile(wPath.c_str(), DirectX::WIC_FLAGS_NONE, &Data, Image))
	{
		MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
	}

	if (S_OK != DirectX::CreateShaderResourceView
	(
		GameEngineCore::GetDevice(),
		Image.GetImages(),
		Image.GetImageCount(), // 이미지가 겹쳐있을수 있다.
		Image.GetMetadata(),
		&SRV
	))
	{
		MsgBoxAssert("텍스처 로드에 실패했습니다." + std::string(_Path.data()));
	}

	Desc.Width = static_cast<UINT>(Data.width);
	Desc.Height = static_cast<UINT>(Data.height);
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
