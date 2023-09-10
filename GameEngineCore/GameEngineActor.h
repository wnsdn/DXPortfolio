#pragma once
#include "GameEngineCoreObject.h"

class GameEngineComponent;
class GameEngineLevel;
class GameEngineActor : public GameEngineCoreObject
{
private:
	void ComponentInit(std::shared_ptr<GameEngineComponent> _Component, int _Order);
protected:
public:
	GameEngineActor() {}
	~GameEngineActor() {}
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;

	template <typename ObjectType, typename EnumType>
	std::shared_ptr<ObjectType> CreateComponent(EnumType _Order)
	{
		return std::dynamic_pointer_cast<ObjectType>(CreateChild<ObjectType>(static_cast<int>(_Order)));
	}

	GameEngineLevel* GetLevel();
};