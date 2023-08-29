#include "PreCompile.h"
#include "GameEngineCore.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEngineTime.h>
#include "GameEngineObject.h"
#include "GameEngineLevel.h"

GameEngineDevice GameEngineCore::MainDevice{};
std::shared_ptr<GameEngineObject> GameEngineCore::CoreObject;
std::shared_ptr<GameEngineLevel> GameEngineCore::CurLevel;
std::shared_ptr<GameEngineLevel> GameEngineCore::NextLevel;
std::map<std::string, std::shared_ptr<GameEngineLevel>> GameEngineCore::AllLevel;

void GameEngineCore::EngineStart(HINSTANCE _Hinst, std::string_view _Name,
	const POINT& _Pos, const POINT& _Scale)
{
	GameEngineDebug::LeakCheck();
	//_CrtSetBreakAlloc(158);

	GameEngineWindow::GetInst().Init(_Hinst, _Name, _Pos, _Scale);
	MainDevice.Initialize(GameEngineWindow::GetInst());
	GameEngineWindow::GetInst().MessageLoop(Start, Update, Release);
}

void GameEngineCore::Start()
{
	GameEngineTime::Init();
	GameEngineInput::Init();

	CoreObject->Start();
}

void GameEngineCore::Update()
{
	if (NextLevel)
	{
		if (CurLevel)
		{
			CurLevel->AllLevelEnd(NextLevel.get());
		}

		NextLevel->AllLevelStart(CurLevel.get());

		CurLevel = NextLevel;
		NextLevel = nullptr;

		GameEngineTime::Reset();
	}

	if (!CurLevel)
	{
		return;
	}

	GameEngineTime::Update();
	float DeltaTime = GameEngineTime::GetFloatDelta();
	if (GameEngineWindow::GetInst().IsFocus())
	{
		GameEngineInput::Update();
	}
	else
	{
		GameEngineInput::Reset();
	}

	CoreObject->Update(DeltaTime);
	CurLevel->AddLiveTime(DeltaTime);
	CurLevel->AllUpdate(DeltaTime);

	MainDevice.RenderStart();
	CurLevel->Render(DeltaTime);
	MainDevice.RenderEnd();
}

void GameEngineCore::Release()
{
	CoreObject->Release();
}

void GameEngineCore::LevelInit(std::shared_ptr<GameEngineLevel> _Level)
{
	_Level->Start();
}
