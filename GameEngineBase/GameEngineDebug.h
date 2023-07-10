#pragma once
#include <Windows.h>
#include <assert.h>
#include <string>

class GameEngineDebug
{
public:
	static void LeakCheck();
private:
	GameEngineDebug();
	~GameEngineDebug();
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;
};

#define MsgBoxAssert(Text)\
std::string Value = Text;\
MessageBoxA(nullptr, Value.c_str(), "Error", MB_OK);\
assert(false);