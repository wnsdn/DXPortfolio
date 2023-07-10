#pragma once
#include <Windows.h>

class GameEngineTime
{
public:
	static void Init();
	static void Reset();
	static void Update();

	static float GetFloatDelta()
	{
		return FloatDelta;
	}
private:
	static LARGE_INTEGER Freq;
	static LARGE_INTEGER Prev;
	static LARGE_INTEGER Cur;
	static double DoubleDelta;
	static float FloatDelta;

	GameEngineTime();
	~GameEngineTime();
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;
};