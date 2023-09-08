#pragma once

class GameEngineTime
{
private:
	static LARGE_INTEGER Freq;
	static LARGE_INTEGER Prev;
	static LARGE_INTEGER Cur;
	static double Delta;

	GameEngineTime() {}
	~GameEngineTime() {}
	GameEngineTime(const GameEngineTime& _Other) = delete;
	GameEngineTime(GameEngineTime&& _Other) noexcept = delete;
	GameEngineTime& operator=(const GameEngineTime& _Other) = delete;
	GameEngineTime& operator=(GameEngineTime&& _Other) noexcept = delete;
public:
	static void Init();
	static void Reset();
	static void Update();

	static float GetFloatDelta()
	{
		return static_cast<float>(Delta);
	}
};