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
	template <typename ObjectType>
	std::shared_ptr<ObjectType> CreateComponent(int _Order = 0)
	{
		std::shared_ptr<GameEngineComponent> NewChild = std::make_shared<ObjectType>();
		ComponentInit(NewChild, _Order);

		return std::dynamic_pointer_cast<ObjectType>(NewChild);
	}

	GameEngineLevel* GetLevel();

	GameEngineActor() {}
	~GameEngineActor() {}
	GameEngineActor(const GameEngineActor& _Other) = delete;
	GameEngineActor(GameEngineActor&& _Other) noexcept = delete;
	GameEngineActor& operator=(const GameEngineActor& _Other) = delete;
	GameEngineActor& operator=(GameEngineActor&& _Other) noexcept = delete;
};