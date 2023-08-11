#include "PreCompile.h"
#include "GameEngineActor.h"

#include "GameEngineComponent.h"
#include "GameEngineLevel.h"

void GameEngineActor::ComponentInit(std::shared_ptr<GameEngineComponent> _Component, int _Order)
{
	_Component->SetParent(this, _Order);
	_Component->Start();
}

GameEngineLevel* GameEngineActor::GetLevel()
{
	return GetParent<GameEngineLevel>();
}
