#pragma once
#include "GameEngineObject.h"

class GameEngineActor;
class GameEngineCamera;
class GameEngineLevel : public GameEngineObject
{
	friend class GameEngineCamera;
	friend class GameEngineCore;
	friend class GameEngineCollision;
public:
	static bool IsDebug;

	static void OnDebug() { IsDebug = true; }
	static void OffDebug() { IsDebug = false; }

	GameEngineLevel();
	~GameEngineLevel();
	GameEngineLevel(const GameEngineLevel& _Other) = delete;
	GameEngineLevel(GameEngineLevel&& _Other) noexcept = delete;
	GameEngineLevel& operator=(const GameEngineLevel& _Other) = delete;
	GameEngineLevel& operator=(GameEngineLevel&& _Other) noexcept = delete;

	std::shared_ptr<class GameEngineCamera> CreateCamera(int _Order, ECAMERAORDER _CameraOrder)
	{
		return CreateCamera(_Order, static_cast<int>(_CameraOrder));
	}
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
		return Cameras[static_cast<int>(ECAMERAORDER::Main)];
	}
	std::shared_ptr<GameEngineCamera> GetCamera(int _Select)
	{
		return Cameras[_Select];
	}
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
};