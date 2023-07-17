#pragma once
#include <format>
#include <string>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineWindow.h"

class GameEngineText
{
private:
	static std::string Buffer;

	GameEngineText() {}
	~GameEngineText() {}
	GameEngineText(const GameEngineText& _Other) = delete;
	GameEngineText(GameEngineText&& _Other) noexcept = delete;
	GameEngineText& operator=(const GameEngineText& _Other) = delete;
	GameEngineText& operator=(GameEngineText&& _Other) noexcept = delete;
public:
	static void Init();

	template <typename... Args>
	static std::string FormatTextOut(const Args&... _Args)
	{
		if (Buffer.capacity() < 32)
		{
			GameEngineDebug::MsgBoxAssert("GameEngineText()::FormatTextOut");
			return std::string();
		}

		Buffer.clear();

		(std::format_to(std::back_inserter(Buffer), "{} ", _Args), ...);

		return Buffer;
	}
};