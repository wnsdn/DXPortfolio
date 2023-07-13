#include <GameEnginePlatform/GameEngineWindow.h>

#pragma comment(lib, "GameEnginePlatform.lib")

int WINAPI WinMain(_In_ HINSTANCE _Hinst, _In_opt_ HINSTANCE, _In_ char*, _In_ int)
{
	GameEngineForm WndForm{ {100, 100}, {1280, 720}, true };

	GameEngineWindow::GetInst().Init(_Hinst, "MyWindow", WndForm);
	GameEngineWindow::GetInst().MessageLoop();

	return 0;
}