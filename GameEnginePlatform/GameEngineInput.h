#pragma once

#include <Windows.h>

class GameEngineInput
{
private:
	class GameEngineKey
	{
		friend class GameEngineInput;
	private:
		int Key = -1;
		bool Down = false;
		bool Press = false;
		bool Up = false;
		bool Free = true;

		void Reset()
		{
			if (Press)
			{
				Down = false;
				Press = false;
				Up = true;
				Free = true;
			}
			else if (Up)
			{
				Down = false;
				Press = false;
				Up = false;
				Free = true;
			}
		}

		void Update(float _Delta);
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
public:
	GameEngineInput();
	~GameEngineInput();
	GameEngineInput(const GameEngineInput& _Other) = delete;
	GameEngineInput(GameEngineInput&& _Other) noexcept = delete;
	GameEngineInput& operator=(const GameEngineInput& _Other) = delete;
	GameEngineInput& operator=(GameEngineInput&& _Other) noexcept = delete;

	static void Init();
	static void Reset();
	static void Update(float _Delta);

	static bool IsDown(int _Key);
	static bool IsUp(int _Key);
	static bool IsPress(int _Key);
	static bool IsFree(int _Key);
private:
	static GameEngineKey AllKey[255];
};