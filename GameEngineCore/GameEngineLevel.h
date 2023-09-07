#pragma once
#include "GameEngineObject.h"

class GameEngineActor;
class GameEngineCamera;
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCamera;
	friend class GameEngineCore;
	friend class GameEngineCollision;
private:
	std::map<int, std::shared_ptr<GameEngineCamera>> Cameras;

	virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

	void AllUpdate(float _Delta) override;
	void Render(float _Delta);

	void ActorInit(std::shared_ptr<GameEngineActor> _Actor, int _Order);
	void Release() override;

	void AllReleaseCheck() override;

	void PushCollision(std::shared_ptr<class GameEngineCollision> _Collision);

	std::map<int, std::shared_ptr<class GameEngineCollisionGroup>> Collisions;
protected:
public:
	std::shared_ptr<GameEngineCamera> CreateCamera(int _Order, int _CameraOrder);

	template <typename ObjectType, typename EnumType>
	std::shared_ptr<ObjectType> CreateActor(EnumType _Order)
	{
		return CreateActor<ObjectType>(static_cast<int>(_Order));
	}

	template <typename ObjectType>
	std::shared_ptr<ObjectType> CreateActor(int _Order = 0)
	{
		std::shared_ptr<GameEngineActor> NewChild = std::make_shared<ObjectType>();

		ActorInit(NewChild, _Order);

		return std::dynamic_pointer_cast<ObjectType>(NewChild);
	}

	std::shared_ptr<GameEngineCamera> GetMainCamera()
	{
		return Cameras[0];
	}

	std::shared_ptr<GameEngineCamera> GetCamera(int _Select)
	{
		return Cameras[_Select];
	}

	GameEngineLevel();
	~GameEngineLevel();
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;
};