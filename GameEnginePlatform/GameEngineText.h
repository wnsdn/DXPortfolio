#pragma once
#include <format>
#include <string>
#include <string_view>
#include "GameEngineWindow.h"

class GameEngineText
{
private:
	//static std::string Buffer;

	GameEngineText() {}
	~GameEngineText() {}
	GameEngineText(const GameEngineText& _Other) = delete;
	GameEngineText(GameEngineText&& _Other) noexcept = delete;
	GameEngineText& operator=(const GameEngineText& _Other) = delete;
	GameEngineText& operator=(GameEngineText&& _Other) noexcept = delete;
public:
	template <typename Arg>
	static void FormatTextOut(std::string_view _Sv, int _X, int _Y, const Arg& _Arg)
	{
		std::string Buffer{_Sv};

		std::format_to(std::back_inserter(Buffer), " : {}", _Arg);

		TextOutA(GameEngineWindow::GetInst().GetMemDc(), _X, _Y, Buffer.c_str(), static_cast<int>(Buffer.size()));
	}

	/*template <typename... Args>
	static void FormatTextOut(int _X, int _Y, const Args&... _Args)
	{
		Buffer.reserve(32);
		if (Buffer.capacity() < 32)
		{
			GameEngineDebug::MsgBoxAssert("GameEngineText::FormatTextOut()");
			return;
		}

		Buffer.clear();

		(std::format_to(std::back_inserter(Buffer), "{} ", _Args), ...);

		TextOutA(GameEngineWindow::GetInst().GetMemDc(), _X, _Y, Buffer.c_str(), static_cast<int>(Buffer.size()));
	}*/
};