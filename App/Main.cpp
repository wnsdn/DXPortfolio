#include <GameEnginePlatform/GameEngineWindow.h>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")

int APIENTRY WinMain(_In_ HINSTANCE _Hinst, _In_opt_ HINSTANCE, _In_ char*, _In_ int)
{
	GameEngineWindow::GetInst().Init(_Hinst, "MyWindow");
	GameEngineWindow::GetInst().MessageLoop();

	return 0;
}