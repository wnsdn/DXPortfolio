#include <Windows.h>
#include <GameEngineCore/GameEngineCore.h>
#include <Contents/ContentsCore.h>

#pragma comment(lib, "GameEngineBase.lib")
#pragma comment(lib, "GameEnginePlatform.lib")
#pragma comment(lib, "GameEngineCore.lib")
#pragma comment(lib, "Contents.lib")

int WINAPI WinMain(_In_ HINSTANCE _Hinst, _In_opt_ HINSTANCE, _In_ char*, _In_ int)
{
	float4x4 Left{};
	float4x4 Right{};

	Left.Scale({ 3, 3, 3 });

	Right.Position({ 100, 100, 100 });

	float4x4 Result = Left * Right;

	GameEngineCore::EngineStart<ContentsCore>(_Hinst);

	return 0;
}