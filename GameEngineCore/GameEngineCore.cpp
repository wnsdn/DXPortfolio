#include "PreCompile.h"
#include "GameEngineCore.h"

#include <GameEnginePlatform/GameEngineWindow.h>

void GameEngineCore::EngineStart(HINSTANCE _Hinst)
{
	GameEngineWindow::GetInst().Init(_Hinst, "MyWindow", 100, 100, 1080, 720);
	GameEngineWindow::GetInst().MessageLoop();
}
