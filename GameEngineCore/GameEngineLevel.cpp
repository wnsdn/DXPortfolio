#include "PreCompile.h"
#include "GameEngineLevel.h"

#include "GameEngineCamera.h"
#include "GameEngineCollision.h"
#include "GameEngineCollisionGroup.h"

bool GameEngineLevel::IsDebug = true;

GameEngineLevel::GameEngineLevel()
{
	CreateCamera(0, ECAMERAORDER::Main);
	CreateCamera(0, ECAMERAORDER::UI);
}

GameEngineLevel::~GameEngineLevel()
{
}

std::shared_ptr<GameEngineCamera> GameEngineLevel::CreateCamera(int _Order, int _CameraOrder)
{
	std::shared_ptr<GameEngineCamera> NewCamera = CreateActor<GameEngineCamera>(_Order);
	NewCamera->SetCameraOrder(_CameraOrder);
	return NewCamera;
}

void GameEngineLevel::AllUpdate(float _Delta)
{
	GameEngineDebug::GameEngineDebugCore::CurLevel = this;

	Update(_Delta);

	for (auto& Pair : Childs)
	{
		for (auto& Actor : Pair.second)
		{
			if (!Actor->IsUpdate())
			{
				continue;
			}

			Actor->AddLiveTime(_Delta);
			Actor->AllUpdate(_Delta);
		}
	}
}

void GameEngineLevel::Render(float _Delta)
{
	for (auto& CameraPair : Cameras)
	{
		if (!CameraPair.second)
		{
			continue;
		}

		CameraPair.second->Render(_Delta);
	}

	if (IsDebug)
	{
		GameEngineDebug::GameEngineDebugCore::DebugRender();
	}
}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order)
{
	_Actor->SetParent(this, _Order);
	_Actor->Start();
}

void GameEngineLevel::Release()
{
}

void GameEngineLevel::AllReleaseCheck()
{
	for (auto& Pair : Cameras)
	{
		if (!Pair.second)
		{
			continue;
		}

		Pair.second->AllReleaseCheck();
	}

	for (auto& Pair : Collisions)
	{
		if (!Pair.second)
		{
			continue;
		}

		Pair.second->AllReleaseCheck();
	}

	for (auto& Pair : Childs)
	{
		auto Beg = Pair.second.begin();
		auto End = Pair.second.end();

		for (; Beg != End;)
		{
			(*Beg)->AllReleaseCheck();

			if (!(*Beg)->IsDeath())
			{
				++Beg;
				continue;
			}

			Beg = Pair.second.erase(Beg);
		}
	}
}

void GameEngineLevel::PushCollision(std::shared_ptr<class GameEngineCollision> _Collision)
{
	if (!_Collision)
	{
		assert(false);
		return;
	}

	if (!Collisions.contains(_Collision->GetOrder()))
	{
		Collisions[_Collision->GetOrder()] = std::make_shared<GameEngineCollisionGroup>();
	}

	Collisions[_Collision->GetOrder()]->PushCollision(_Collision);
}
