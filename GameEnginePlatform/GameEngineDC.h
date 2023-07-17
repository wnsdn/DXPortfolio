#pragma once
#include <Windows.h>

class GameEngineDC
{
private:
	HDC Hdc = nullptr;
	HBITMAP Hbmp = nullptr;
	BITMAP Info{};

	bool IsMainDc = false;
public:
	HDC GetHdc() const
	{
		return Hdc;
	}
public:
	GameEngineDC(HDC _Hdc);
	GameEngineDC(GameEngineDC* const _Dc);
	~GameEngineDC() {}
	GameEngineDC(const GameEngineDC& _Ref) = delete;
	GameEngineDC(GameEngineDC&& _Rvalue) noexcept = delete;
	GameEngineDC& operator=(const GameEngineDC& _Ref) = delete;
	GameEngineDC& operator=(GameEngineDC&& _Rvalue) noexcept = delete;
};

