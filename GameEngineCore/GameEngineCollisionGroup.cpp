#include "PreCompile.h"
#include "GameEngineCollisionGroup.h"

#include "GameEngineCollision.h"

GameEngineCollisionGroup::GameEngineCollisionGroup()
{
}

GameEngineCollisionGroup::~GameEngineCollisionGroup()
{
}

void GameEngineCollisionGroup::AllReleaseCheck()
{
	auto Beg = Collisions.begin();
	auto End = Collisions.end();

	for (; Beg != End;)
	{
		if (!(*Beg)->IsDeath())
		{
			++Beg;
			continue;
		}

		Beg = Collisions.erase(Beg);
	}
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Col)
{
	for (auto& Col : Collisions)
	{
		if (Col == _Col)
		{
			continue;
		}

		if (GameEngineTransform::Collision({
			_Col->Transform.ColData,
			Col->Transform.ColData,
			_Col->GetCollisionType(),
			Col->GetCollisionType() }))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Col, const float4& _NextPos)
{
	auto Data = _Col->Transform.ColData;
	Data.OBB.Center.x += _NextPos.X;
	Data.OBB.Center.y += _NextPos.Y;
	Data.OBB.Center.z += _NextPos.Z;

	for (auto& Col : Collisions)
	{
		if (Col == _Col)
		{
			continue;
		}

		if (GameEngineTransform::Collision({
			Data,
			Col->Transform.ColData,
			_Col->GetCollisionType(),
			Col->GetCollisionType() }))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Col, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Col)> _Function)
{
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (auto& Col : Collisions)
	{
		if (Col == _Col)
		{
			continue;
		}

		if (GameEngineTransform::Collision({
			_Col->Transform.ColData,
			Col->Transform.ColData,
			_Col->GetCollisionType(),
			Col->GetCollisionType() }))
		{
			ResultCollision.push_back(Col);
		}
	}

	if (!ResultCollision.empty())
	{
		_Function(ResultCollision);
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Col, const float4& _NextPos, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Col)> _Function)
{
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	auto Data = _Col->Transform.ColData;
	Data.OBB.Center.x += _NextPos.X;
	Data.OBB.Center.y += _NextPos.Y;
	Data.OBB.Center.z += _NextPos.Z;

	for (auto& Col : Collisions)
	{
		if (Col == _Col)
		{
			continue;
		}

		if (GameEngineTransform::Collision({
			Data,
			Col->Transform.ColData,
			_Col->GetCollisionType(),
			Col->GetCollisionType() }))
		{
			ResultCollision.push_back(Col);
		}
	}

	if (!ResultCollision.empty())
	{
		_Function(ResultCollision);
	}

	return false;
}

bool GameEngineCollisionGroup::CollisionEvent(std::shared_ptr<GameEngineCollision> _Col, const EventParameter& _Event)
{
	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (auto& Col : Collisions)
	{
		if (Col == _Col)
		{
			continue;
		}

		if (GameEngineTransform::Collision({
			_Col->Transform.ColData,
			Col->Transform.ColData,
			_Col->GetCollisionType(),
			Col->GetCollisionType() }))
		{
			ResultCollision.push_back(Col);
			continue;
		}

		auto Other = Col.get();
		if (_Col->Others.contains(Other))
		{
			if (_Event.Exit)
			{
				_Event.Exit(Other);
				Other->Others.erase(_Col.get());
				_Col->Others.erase(Other);
			}
		}
	}

	if (!ResultCollision.empty())
	{
		for (auto& ResCol : ResultCollision)
		{
			auto Other = ResCol.get();
			if (!_Col->Others.contains(Other))
			{
				if (_Event.Enter)
				{
					_Event.Enter(Other);
					Other->Others.insert(_Col.get());
					_Col->Others.insert(Other);
				}
				else
				{
					if (_Event.Stay)
					{
						_Event.Stay(Other);
					}
				}
			}
		}
	}

	return false;
}

void GameEngineCollisionGroup::PushCollision(std::shared_ptr<class GameEngineCollision> _Col)
{
	if (!_Col)
	{
		MsgBoxAssert("존재하지 않는 콜리전을 사용하려고 했습니다.");
		return;
	}

	Collisions.push_back(_Col);
}
