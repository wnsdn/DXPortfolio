#include <GameEnginePlatform/GameEngineWindow.h>

#pragma comment(lib, "GameEnginePlatform.lib")

int WINAPI WinMain(_In_ HINSTANCE _Hinst, _In_opt_ HINSTANCE, _In_ char*, _In_ int)
{
	GameEngineWindow::GetInst().Init(_Hinst, "MyWindow", 100, 100, 1080, 720);
	GameEngineWindow::GetInst().MessageLoop();

	return 0;
}