#include <Windows.h>
#include <GameEngineCore/GameEngineCore.h>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "Contents.lib")

int WINAPI WinMain(_In_ HINSTANCE _Hinst, _In_opt_ HINSTANCE, _In_ char*, _In_ int)
{
	GameEngineCore::EngineStart(_Hinst);

	return 0;
}