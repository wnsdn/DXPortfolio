#pragma once

class GameEngineInput
{
private:
	class GameEngineKey
	{
	public:
		unsigned char Key = 0;
		bool Down = false;
		bool Press = false;
		bool Up = false;
		bool Free = true;
	public:
		GameEngineKey()
			: Key(0)
		{
		}
		GameEngineKey(const unsigned char _Key)
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

	static bool IsDown(const unsigned char _Key)
	{
		return AllKey[_Key].Down;
	}
	static bool IsUp(const unsigned char _Key)
	{
		return AllKey[_Key].Up;
	}
	static bool IsPress(const unsigned char _Key)
	{
		return AllKey[_Key].Press;
	}
	static bool IsFree(const unsigned char _Key)
	{
		return AllKey[_Key].Free;
	}
};