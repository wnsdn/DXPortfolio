#pragma once

class GameEngineInput
{
private:
	class GameEngineKey
	{
	public:
		unsigned char Key = 0;
		unsigned char State = 1;
	public:
		GameEngineKey()
			: Key(0), State(1)
		{}
	};

	static const unsigned char KeyMax = 255;
	static GameEngineKey AllKey[KeyMax];

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
		return AllKey[_Key].State & 8 ? true : false;
	}
	static bool IsPress(const unsigned char _Key)
	{
		return AllKey[_Key].State & 4 ? true : false;
	}
	static bool IsUp(const unsigned char _Key)
	{
		return AllKey[_Key].State & 2 ? true : false;
	}
	static bool IsFree(const unsigned char _Key)
	{
		return AllKey[_Key].State & 1 ? true : false;
	}
};