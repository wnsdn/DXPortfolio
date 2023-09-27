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
	if (!_Col->IsUpdate())
	{
		return false;
	}

	for (auto& Col : Collisions)
	{
		if (Col == _Col)
		{
			continue;
		}

		if (!Col->IsUpdate())
		{
			continue;
		}

		if (GameEngineTransform::Collision({ _Col->Transform.ColData, Col->Transform.ColData, _Col->GetCollisionType(), Col->GetCollisionType() }))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Col, const float4& _NextPos)
{
	if (!_Col->IsUpdate())
	{
		return false;
	}

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

		if (!Col->IsUpdate())
		{
			continue;
		}

		if (GameEngineTransform::Collision({ Data, Col->Transform.ColData, _Col->GetCollisionType(), Col->GetCollisionType() }))
		{
			return true;
		}
	}

	return false;
}

bool GameEngineCollisionGroup::Collision(std::shared_ptr<GameEngineCollision> _Col, std::function<void(std::vector<std::shared_ptr<GameEngineCollision>>& _Col)> _Function)
{
	if (!_Col->IsUpdate())
	{
		return false;
	}

	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (auto& Col : Collisions)
	{
		if (Col == _Col)
		{
			continue;
		}

		if (!Col->IsUpdate())
		{
			continue;
		}

		if (GameEngineTransform::Collision({ _Col->Transform.ColData, Col->Transform.ColData, _Col->GetCollisionType(), Col->GetCollisionType() }))
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
	if (!_Col->IsUpdate())
	{
		return false;
	}

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

		if (!Col->IsUpdate())
		{
			continue;
		}

		if (GameEngineTransform::Collision({ Data, Col->Transform.ColData, _Col->GetCollisionType(), Col->GetCollisionType() }))
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
	if (!_Col->IsUpdate())
	{
		return false;
	}

	static std::vector<std::shared_ptr<GameEngineCollision>> ResultCollision;
	ResultCollision.clear();

	for (auto& Col : Collisions)
	{
		if (Col == _Col)
		{
			continue;
		}

		if (!Col->IsUpdate())
		{
			continue;
		}

		if (GameEngineTransform::Collision({ _Col->Transform.ColData, Col->Transform.ColData, _Col->GetCollisionType(), Col->GetCollisionType() }))
		{
			ResultCollision.push_back(Col);
			continue;
		}

		if (_Col->Others.contains(Col))
		{
			if (_Event.Exit)
			{
				_Event.Exit(_Col.get(), Col.get());
			}

			_Col->Others.erase(Col);
		}
	}

	if (!ResultCollision.empty())
	{
		for (auto& Other : ResultCollision)
		{
			if (!_Col->Others.contains(Other))
			{
				if (_Event.Enter)
				{
					_Event.Enter(_Col.get(), Other.get());
				}

				_Col->Others.insert(Other);
			}
			else
			{
				if (_Event.Stay)
				{
					_Event.Stay(_Col.get(), Other.get());
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
		assert(false);
		return;
	}

	Collisions.push_back(_Col);
}
