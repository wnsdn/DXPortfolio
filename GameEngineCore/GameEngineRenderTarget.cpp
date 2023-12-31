#include "PreCompile.h"
#include "GameEngineRenderTarget.h"

void GameEngineRenderTarget::Clear()
{
	for (int i = 0; i < RTV.size(); ++i)
	{
		GameEngineCore::GetContext()->ClearRenderTargetView(RTV[i], ClearColor[i]);
	}
}

void GameEngineRenderTarget::Setting()
{
	if (RTV.size() <= 0)
	{
		assert(false);
		return;
	}

	GameEngineCore::GetContext()->
		OMSetRenderTargets(static_cast<UINT>(RTV.size()), &RTV[0], nullptr);
}
