#include "PreCompile.h"
#include "GameEngineActor.h"

#include "GameEngineLevel.h"

GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetParent<GameEngineLevel>();
}
