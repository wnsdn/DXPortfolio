#include "PreCompile.h"
#include "GameEngineCore.h"

#include <GameEngineBase/GameEngineTime.h>

GameEngineWindow GameEngineCore::MainWindow;
std::unique_ptr<GameEngineObject> GameEngineCore::CoreObject;

void GameEngineCore::EngineStart(HINSTANCE _Hinst, std::string_view _Name,
	const POINT& _Pos, const POINT& _Scale)
{
	GameEngineDebug::LeakCheck();

	MainWindow.Init(_Hinst, _Name, _Pos, _Scale);
	MainWindow.MessageLoop(Start, Update, Release);
}

void GameEngineCore::Start()
{
	GameEngineTime::Init();
	GameEngineInput::Init();

	CoreObject->Start();
}

void GameEngineCore::Update()
{
	GameEngineTime::Update();
	const float DeltaTime = GameEngineTime::GetFloatDelta();
	GameEngineInput::Update();

	CoreObject->Update(DeltaTime);
}

void GameEngineCore::Release()
{
	CoreObject->Release();
}
