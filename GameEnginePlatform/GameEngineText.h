#pragma once
#include <format>
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineWindow.h"

class GameEngineText
{
private:
	GameEngineText() {}
	~GameEngineText() {}
	GameEngineText(const GameEngineText& _Other) = delete;
	GameEngineText(GameEngineText&& _Other) noexcept = delete;
	GameEngineText& operator=(const GameEngineText& _Other) = delete;
	GameEngineText& operator=(GameEngineText&& _Other) noexcept = delete;
public:
	template <typename ArgType>
	static void FormatTextOut(const std::string_view& _Text, const ArgType& _Ptr, const Point4<int>& _Pos)
	{
		std::string Buffer(_Text);
		std::format_to(std::back_inserter(Buffer), "{}", _Ptr);
		TextOutA(GameEngineWindow::GetInst().GetMemDc(), _Pos.X, _Pos.Y, Buffer.c_str(), static_cast<int>(Buffer.size()));
	}
};