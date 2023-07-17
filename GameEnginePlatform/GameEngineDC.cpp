#include "PreCompile.h"
#include "GameEngineDC.h"

#include <GameEngineBase/GameEngineDebug.h>

GameEngineDC::GameEngineDC(HDC _Hdc)
	: Hdc(_Hdc)
	, Hbmp(static_cast<HBITMAP>(GetCurrentObject(Hdc, OBJ_BITMAP)))
	, IsMainDc(true)
{
	GetObjectA(Hbmp, sizeof(BITMAP), &Info);
}

GameEngineDC::GameEngineDC(GameEngineDC* const _Dc)
{
	if (!_Dc->GetHdc())
	{
		GameEngineDebug::MsgBoxAssert("GameEngineDC::No MainDc");
		return;
	}

	Hdc = CreateCompatibleDC(_Dc->GetHdc());
	Hbmp = CreateCompatibleBitmap()
}
