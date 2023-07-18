#pragma once
#include <Windows.h>

class GameEngineCore
{
private:

public:
	static void EngineStart(HINSTANCE _Hinst);
public:
	GameEngineCore() {}
	~GameEngineCore() {}
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;
};