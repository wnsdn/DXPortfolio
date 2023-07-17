#include "PreCompile.h"
#include "GameEngineDebug.h"

#include <crtdbg.h>
#include <cassert>

void GameEngineDebug::LeakCheck()
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
}

void GameEngineDebug::MsgBoxAssert(std::string_view _Text)
{
	MessageBoxA(nullptr, _Text.data(), "Error", MB_OK);
	assert(false);
}
