#pragma once
#include <string_view>

class GameEngineDebug
{
private:
	GameEngineDebug() {}
	~GameEngineDebug() {}
	GameEngineDebug(const GameEngineDebug& _Other) = delete;
	GameEngineDebug(GameEngineDebug&& _Other) noexcept = delete;
	GameEngineDebug& operator=(const GameEngineDebug& _Other) = delete;
	GameEngineDebug& operator=(GameEngineDebug&& _Other) noexcept = delete;
public:
	static void LeakCheck();
	static void MsgBoxAssert(std::string_view _Text);
};
