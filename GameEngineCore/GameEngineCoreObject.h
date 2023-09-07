#pragma once
#include "GameEngineObject.h"

class GameEngineCoreObject : public GameEngineObject
{
public:
	GameEngineCoreObject() {}
	~GameEngineCoreObject() {}
	GameEngineCoreObject(const GameEngineCoreObject& _Other) = delete;
	GameEngineCoreObject(GameEngineCoreObject&& _Other) noexcept = delete;
	GameEngineCoreObject& operator=(const GameEngineCoreObject& _Other) = delete;
	GameEngineCoreObject& operator=(GameEngineCoreObject&& _Other) noexcept = delete;

	class GameEngineLevel* GetLevel();
	class GameEngineActor* GetActor();
};