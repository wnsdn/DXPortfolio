#pragma once
#include "GameEngineCoreObject.h"

class GameEngineLevel;
class GameEngineComponent;
class GameEngineActor : public GameEngineCoreObject
{
private:
protected:
public:
	template <typename ObjectType>
	std::shared_ptr<ObjectType> CreateComponent(int _Order = 0)
	{
		std::shared_ptr<GameEngineComponent> NewChild = std::make_shared<ObjectType>();
		NewChild->SetParent(this);
		NewChild->Start();
		Childs[_Order].push_back(NewChild);

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