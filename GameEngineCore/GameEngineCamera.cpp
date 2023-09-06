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
		MsgBoxAssert(__FUNCTION__);
		return;
	}
}

void GameEngineCamera::Update(float _Delta)
{
	GameEngineActor::Update(_Delta);

	float4 Position = Transform.GetWorldPosition();
	float4 Forward = Transform.GetWorldFrontVector();
	float4 Up = Transform.GetWorldUpVector();

	Transform.View(Position, Forward, Up);

	float4 WndScale = GameEngineWindow::GetInst().GetScale();

	switch (ProjectionType)
	{
	case EPROJECTIONTYPE::Perspective:
		Transform.Perspective(FOV, WndScale.X, WndScale.Y, Far, Near);
		break;
	case EPROJECTIONTYPE::Orthographic:
		Transform.Orthographic(WndScale.X, WndScale.Y, Far, Near);
		break;
	default:
		break;
	}
}

void GameEngineCamera::Render(float _Delta)
{
	if (Renderers.empty())
	{
		return;
	}

	for (auto& Pair : Renderers)
	{
		for (auto& Renderer : Pair.second)
		{
			if (!Renderer->IsUpdate())
			{
				continue;
			}

			Renderer->Transform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());
			Renderer->Render(this, _Delta);
		}
	}
}

void GameEngineCamera::AllReleaseCheck()
{
	if (Renderers.empty())
	{
		return;
	}

	for (auto& Pair : Renderers)
	{
		auto Beg = Pair.second.begin();
		auto End = Pair.second.end();

		for (; Beg != End;)
		{
			if (!(*Beg)->IsDeath())
			{
				(*Beg)->AllReleaseCheck();
				++Beg;
				continue;
			}

			Beg = Pair.second.erase(Beg);
		}
	}
}

void GameEngineCamera::SetCameraOrder(int _Order)
{
	GameEngineLevel* Level = GetLevel();

	if (!Level)
	{
		MsgBoxAssert(__FUNCTION__);
		return;
	}

	if (Level->Cameras[CameraOrder] == shared_from_this())
	{
		Level->Cameras[CameraOrder] = nullptr;
	}
	CameraOrder = _Order;
	Level->Cameras[CameraOrder] = GetDynamic_Cast_This<GameEngineCamera>();
}
