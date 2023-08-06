#pragma once
#include "GameEngineObject.h"

class GameEngineLevel;
class GameEngineActor;
class GameEngineCoreObject : public GameEngineObject
{
private:
protected:
	GameEngineLevel* GetLevel();
	GameEngineActor* GetActor();
public:
	GameEngineCoreObject() {}
	~GameEngineCoreObject() {}
	GameEngineCoreObject(const GameEngineCoreObject& _Other) = delete;
	GameEngineCoreObject(GameEngineCoreObject&& _Other) noexcept = delete;
	GameEngineCoreObject& operator=(const GameEngineCoreObject& _Other) = delete;
	GameEngineCoreObject& operator=(GameEngineCoreObject&& _Other) noexcept = delete;
};