#pragma once
#include "GameEngineCollision.h"

class GameEngineCollisionGroup : public GameEngineObject
{
	friend class GameEngineLevel;
private:
	std::list<std::shared_ptr<class GameEngineCollision>> Collisions;

	void PushCollision(std::shared_ptr<class GameEngineCollision> _Col);
protected:
	void AllReleaseCheck() override;
public:
	GameEngineCollisionGroup();
	~GameEngineCollisionGroup();
	GameEngineCollisionGroup(const GameEngineCollisionGroup&) = delete;
	GameEngineCollisionGroup(GameEngineCollisionGroup&&) noexcept = delete;
	void operator=(const GameEngineCollisionGroup&) = delete;
	void operator=(GameEngineCollisionGroup&&) noexcept = delete;

	bool Collision(std::shared_ptr<GameEngineCollision> _Col);
	bool Collision(std::shared_ptr<GameEngineCollision> _Col, const float4& _NextPos);
	bool Collision(std::shared_ptr<GameEngineCollision> _Col, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Col)> _Function);
	bool Collision(std::shared_ptr<GameEngineCollision> _Col, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Col)> _Function);
	bool CollisionEvent(std::shared_ptr<GameEngineCollision> _Col, const EventParameter& _Event);
};
