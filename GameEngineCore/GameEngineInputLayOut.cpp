#include "PreCompile.h"
#include "GameEngineInputLayout.h"

#include <d3d11.h>
#pragma comment(lib, "d3d11")

GameEngineInputLayout::~GameEngineInputLayout()
{
	if (Layout)
	{
		Layout->Release();
		Layout = nullptr;
	}
}

void GameEngineInputLayout::ResCreate()
{
}

void GameEngineInputLayout::Setting()
{
	if (!Layout)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	GameEngineCore::MainDevice.GetContext()->IASetInputLayout(Layout);
}
