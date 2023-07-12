#pragma once

#include <Windows.h>

class GameEngineInput
{
private:
	class GameEngineKey
	{
	public:
		int Key = -1;
		bool Down = false;
		bool Press = false;
		bool Up = false;
		bool Free = true;
	public:
		void Reset();
		void Update();
	public:
		GameEngineKey()
			: Key(-1)
		{
		}
		GameEngineKey(int _Key)
			: Key(_Key)
		{
		}
	};

	static GameEngineKey AllKey[255];

	GameEngineInput() {}
	~GameEngineInput() {}
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;
public:
	static void Init();
	static void Reset();
	static void Update();

	static bool IsDown(int _Key)
	{
		return AllKey[_Key].Down;
	}
	static bool IsUp(int _Key)
	{
		return AllKey[_Key].Up;
	}
	static bool IsPress(int _Key)
	{
		return AllKey[_Key].Press;
	}
	static bool IsFree(int _Key)
	{
		return AllKey[_Key].Free;
	}
};