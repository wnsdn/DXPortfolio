#include "PreCompile.h"
#include "GameEngineText.h"

std::string GameEngineText::Buffer{};

void GameEngineText::Init()
{
	Buffer.reserve(32);
}
