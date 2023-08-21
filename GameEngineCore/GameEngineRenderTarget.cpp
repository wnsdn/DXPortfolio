#include "PreCompile.h"
#include "GameEngineRenderTarget.h"

#include "GameEngineCore.h"
#include <d3d11.h>
#pragma comment	(lib, "d3d11")

void GameEngineRenderTarget::Clear()
{
	for (int i = 0; i < RTV.size(); ++i)
	{
		GameEngineCore::MainDevice.GetContext()->ClearRenderTargetView(
			RTV[i], ClearColor[i]);
	}
}

void GameEngineRenderTarget::Setting()
{
	if (RTV.size() <= 0)
	{
		MsgBoxAssert(__FUNCTION__);
		return;
	}

	GameEngineCore::MainDevice.GetContext()->
		OMSetRenderTargets(static_cast<UINT>(RTV.size()), &RTV[0], nullptr);
}
