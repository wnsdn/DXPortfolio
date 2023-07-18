#pragma once
#include <Windows.h>

class GameEngineDC
{
private:
	HDC Hdc = nullptr;
	HBITMAP Hbmp = nullptr;
	BITMAP Info{};
public:
	HDC GetHdc() const
	{
		return Hdc;
	}
	int GetWidth() const
	{
		return Info.bmWidth;
	}
	int GetHeight() const
	{
		return Info.bmHeight;
	}
public:
	GameEngineDC(const int _X, const int _Y);
	~GameEngineDC();
	GameEngineDC(const GameEngineDC& _Ref) = delete;
	GameEngineDC(GameEngineDC&& _Rvalue) noexcept = delete;
	GameEngineDC& operator=(const GameEngineDC& _Ref) = delete;
	GameEngineDC& operator=(GameEngineDC&& _Rvalue) noexcept = delete;
};

