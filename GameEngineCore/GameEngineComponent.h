#pragma once
#include "GameEngineObject.h"

class GameEngineComponent : public GameEngineObject
{
private:
public:
	GameEngineComponent() {}
	~GameEngineComponent() {}
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;
};