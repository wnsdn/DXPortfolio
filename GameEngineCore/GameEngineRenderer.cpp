#include "PreCompile.h"
#include "GameEngineRenderer.h"

#include "GameEngineCamera.h"
#include "GameEngineLevel.h"

#include "GameEngineVertexBuffer.h"

void GameEngineRenderer::Start()
{
	SetViewCameraSelect(0);
}

void GameEngineRenderer::Render(float _Delta)
{
	std::shared_ptr<GameEngineVertexBuffer> VertexBuffer =
		GameEngineVertexBuffer::Find("Rect");
	VertexBuffer->Setting();
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();
	std::shared_ptr<GameEngineCamera> Camera = Level->GetCamera(_Order);

	if (!Camera)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	Camera->Renderers[_Order].emplace_back(GetDynamic_Cast_This<GameEngineRenderer>());
	ViewInfo[Camera.get()] = _Order;
}
