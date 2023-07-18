#include "PreCompile.h"
#include "GameEngineDC.h"

#include <GameEngineBase/GameEngineDebug.h>

GameEngineDC::GameEngineDC(const int _X, const int _Y)
{
	Hdc = CreateCompatibleDC(nullptr);
	Hbmp = CreateCompatibleBitmap(Hdc, _X, _Y);
	SelectObject(Hdc, Hbmp);
	GetObjectA(Hbmp, sizeof(BITMAP), &Info);
}

GameEngineDC::~GameEngineDC()
{
	if (Hdc)
	{
		DeleteDC(Hdc);
		Hdc = nullptr;
	}
	if (Hbmp)
	{
		DeleteObject(Hbmp);
		Hbmp = nullptr;
	}
}
