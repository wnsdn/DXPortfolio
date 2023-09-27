#include "PreCompile.h"
#include "GameEngineCollision.h"

#include "GameEngineActor.h"
#include "GameEngineLevel.h"
#include "GameEngineCollisionGroup.h"

GameEngineCollision::GameEngineCollision()
{
}

GameEngineCollision::~GameEngineCollision()
{
}

void GameEngineCollision::Start()
{
	GetActor()->GetLevel()->PushCollision(GetDynamic_Cast_This<GameEngineCollision>());
}

void GameEngineCollision::Update(float _Delta)
{
	if (GameEngineLevel::IsDebug)
	{
		switch (CollisionType)
		{
		case ColType::SPHERE2D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::AABBBOX2D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::OBBBOX2D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::SPHERE3D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::AABBBOX3D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::OBBBOX3D:
			GameEngineDebug::DrawBox2D(Transform);
			break;
		case ColType::MAX:
			break;
		default:
			break;
		}
	}
}

bool GameEngineCollision::Collision(int _Order)
{
	if (!GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}

	auto& OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>());
}

bool GameEngineCollision::Collision(int _Order, const float4& _NextPos)
{
	if (!GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}

	auto& OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _NextPos);
}

bool GameEngineCollision::Collision(int _Order, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)> _Collision)
{
	if (!GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}

	auto& OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _Collision);
}

bool GameEngineCollision::Collision(int _Order, const float4& _Next, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Collision)> _Collision)
{
	if (!GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}

	auto& OtherGroup = GetLevel()->Collisions[_Order];
	return OtherGroup->Collision(GetDynamic_Cast_This<GameEngineCollision>(), _Next, _Collision);
}

bool GameEngineCollision::CollisionEvent(int _Order, const EventParameter& _Event)
{
	if (!GetLevel()->Collisions.contains(_Order))
	{
		return false;
	}

	auto& OtherGroup = GetLevel()->Collisions[_Order];

	auto Beg = Others.begin();
	auto End = Others.end();

	for (; Beg != End;)
	{
		if (!(*Beg)->IsDeath())
		{
			++Beg;
			continue;
		}

		Beg = Others.erase(Beg);
	}

	return OtherGroup->CollisionEvent(GetDynamic_Cast_This<GameEngineCollision>(), _Event);
}

void GameEngineCollision::Release()
{
	int a = 0;
}
