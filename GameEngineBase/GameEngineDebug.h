#pragma once
#include <Windows.h>
#include <string>
#include <cassert>

class GameEngineDebug
{
private:
	GameEngineDebug(const GameEngineDebug&) = delete;
	GameEngineDebug(GameEngineDebug&&) noexcept = delete;
	void operator=(const GameEngineDebug&) = delete;
	void operator=(GameEngineDebug&&) noexcept = delete;
public:
	static void LeakCheck();
};

#define MsgBoxAssert(Text)\
std::string Value = Text;\
MessageBoxA(nullptr, Value.c_str(), "Error", MB_OK); assert(false);