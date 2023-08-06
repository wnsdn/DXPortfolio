#include "PreCompile.h"
#include "GameEngineDC.h"

#include <GameEngineBase/GameEngineDebug.h>

GameEngineDC::GameEngineDC(HDC _Hdc, int _X, int _Y)
{
	Hdc = CreateCompatibleDC(_Hdc);
	Hbmp = CreateCompatibleBitmap(_Hdc, _X, _Y);
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
