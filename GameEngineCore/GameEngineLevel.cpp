#include "PreCompile.h"
#include "GameEngineLevel.h"

#include "GameEngineCamera.h"

GameEngineLevel::GameEngineLevel()
{
	CreateCamera(0, 0);
	CreateCamera(0, 100);
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
	for (auto& Pair : Cameras)
	{
		Pair.second->Render(_Delta);
	}
}

void GameEngineLevel::ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order)
{
	_Actor->SetParent(this, _Order);
	_Actor->Start();
}

void GameEngineLevel::Release()
{
	assert(false);
}

void GameEngineLevel::AllReleaseCheck()
{
	for (auto& Pair : Cameras)
	{
		Pair.second->AllReleaseCheck();
	}

	for (auto& Pair : Childs)
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
