#pragma once
#include "GameEngineObject.h"
#include "GameEngineComponent.h"

class GameEngineCollision;
class EventParameter
{
public:
	std::function<void(GameEngineCollision*, GameEngineCollision*)> Enter = nullptr;
	std::function<void(GameEngineCollision*, GameEngineCollision*)> Stay = nullptr;
	std::function<void(GameEngineCollision*, GameEngineCollision*)> Exit = nullptr;
};

class GameEngineCollision : public GameEngineComponent
{
	friend class GameEngineCollisionGroup;
private:
	ColType CollisionType = ColType::SPHERE2D;
	std::set<std::shared_ptr<GameEngineCollision>> Others;
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Release() override;
public:
	GameEngineCollision();
	~GameEngineCollision();
	GameEngineCollision(const GameEngineCollision&) = delete;
	GameEngineCollision(GameEngineCollision&&) noexcept = delete;
	void operator=(const GameEngineCollision&) = delete;
	void operator=(GameEngineCollision&&) noexcept = delete;

	template <typename EnumType>
	bool Collision(EnumType _Order)
	{
		return Collision(static_cast<int>(_Order));
	}
	bool Collision(int _Order);

	template <typename EnumType>
	bool Collision(EnumType _Order, const float4& _NextPos)
	{
		return Collision(static_cast<int>(_Order), _NextPos);
	}
	bool Collision(int _Order, const float4& _NextPos);

	template <typename EnumType>
	bool Collision(EnumType _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)> _Collision)
	{
		return Collision(static_cast<int>(_Order), _Collision);
	}
	bool Collision(int _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)> _Collision);

	template <typename EnumType>
	bool Collision(EnumType _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)> _Collision)
	{
		return Collision(static_cast<int>(_Order), _Next, _Collision);
	}
	bool Collision(int _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)> _Collision);

	template <typename EnumType>
	bool CollisionEvent(EnumType _Order, const EventParameter& _Event)
	{
		return CollisionEvent(static_cast<int>(_Order), _Event);
	}
	bool CollisionEvent(int _Order, const EventParameter& _Event);

	void SetCollisionType(ColType _CollisionType)
	{
		CollisionType = _CollisionType;
	}
	ColType GetCollisionType() const
	{
		return CollisionType;
	}
};
