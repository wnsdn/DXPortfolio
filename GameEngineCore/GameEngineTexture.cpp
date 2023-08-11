#include "PreCompile.h"
#include "GameEngineTexture.h"

#include "GameEngineCore.h"
#include <d3d11.h>
#pragma comment	(lib, "d3d11")

void GameEngineTexture::CreateRenderTargetView()
{
	if (RTV)
	{
		return;
	}
	if (!Texture2D)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	HRESULT Result = GameEngineCore::MainDevice.GetDevice()->CreateRenderTargetView(Texture2D,
		nullptr, &RTV);
	if (Result != S_OK)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}
}

GameEngineTexture::~GameEngineTexture()
{
	if (Texture2D)
	{
		Texture2D->Release();
		Texture2D = nullptr;
	}
	if (RTV)
	{
		RTV->Release();
		RTV = nullptr;
	}
}
