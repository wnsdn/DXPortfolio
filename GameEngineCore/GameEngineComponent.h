#pragma once
#include "GameEngineCoreObject.h"

class GameEngineComponent : public GameEngineCoreObject
{
private:
protected:
public:
	GameEngineComponent() {}
	~GameEngineComponent() {}
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;
};