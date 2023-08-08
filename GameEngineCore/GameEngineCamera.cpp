#include "PreCompile.h"
#include "GameEngineCamera.h"

#include "GameEngineLevel.h"
#include "GameEngineRenderer.h"

void GameEngineCamera::Start()
{
	GameEngineActor::Start();
	GameEngineLevel* Level = GetLevel();

	if (!Level)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	//Transform.GetTransformDataRef().Rotation = { 0.0f, 0.0f, 1.0f, 1.0f };
}

void GameEngineCamera::Update(float _Delta)
{
	GameEngineActor::Update(_Delta);

	/*float4 Position = Transform.GetWorldPosition();
	float4 Degree = Transform.GetTransformDataRef().Rotation;

	Transform.View(Position, Degree);*/
}

void GameEngineCamera::Render(float _Delta)
{
	if (Renderers.empty())
	{
		return;
	}

	for (auto& Pair : Renderers)
	{
		for (auto Renderer : Pair.second)
		{
			Renderer->Render(_Delta);
		}
	}
}

void GameEngineCamera::SetCameraOrder(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	if (!Level)
	{
		GameEngineDebug::MsgBoxAssert("Level == nullptr");
		return;
	}

	if (Level->Cameras[CameraOrder] == shared_from_this())
	{
		Level->Cameras[CameraOrder] = nullptr;
	}
	CameraOrder = _Order;
	Level->Cameras[CameraOrder] = GetDynamic_Cast_This<GameEngineCamera>();
}
