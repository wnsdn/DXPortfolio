#pragma once
#include <string>
#include <string_view>
#include <map>
#include <list>
#include <memory>
#include "GameEngineTransform.h"

class GameEngineObject
{
private:
	GameEngineTransform Transform{};
	std::string Name{};
	float LiveTime = 0.0f;
	int Order = 0;
	bool bUpdate = true;
	bool bDeath = false;

	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}
protected:
	GameEngineObject* Parent = nullptr;
	std::map<int, std::list<std::shared_ptr<GameEngineObject>>> Childs;
public:
	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Release() {}

	template <typename Object>
	std::shared_ptr<Object> CreateChild(int _Order = 0)
	{
		std::shared_ptr<GameEngineObject> NewChild = std::make_shared<Object>();

		NewChild->Start();
		NewChild->Parent = this;
		Childs[_Order].push_back(NewChild);

		return std::dynamic_pointer_cast<Object>(NewChild);
	}

	virtual void AllUpdate(float _Delta);
#pragma region GetSet
	virtual bool GetUpdate() const
	{
		if (Parent)
		{
			return Parent->bUpdate && bUpdate && !bDeath;
		}
		else
		{
			return bUpdate && !bDeath;
		}
	}
	virtual void SetUpdate(bool _bUpdate)
	{
		bUpdate = _bUpdate;
	}
	virtual bool GetDeath() const
	{
		if (Parent)
		{
			return Parent->bDeath && bDeath;
		}
		else
		{
			return bDeath;
		}
	}
	void SetDeath(bool _bDeath)
	{
		bDeath = _bDeath;
	}
	int GetOrder() const
	{
		return Order;
	}
	template <typename Enum>
	void SetOrder(Enum _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}
	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}
	float GetLiveTime() const
	{
		return LiveTime;
	}
	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}
	std::string GetName() const
	{
		return Name;
	}
	void SetName(std::string_view _Name)
	{
		Name = _Name;
	}
#pragma endregion
public:
	GameEngineObject() {}
	virtual ~GameEngineObject() {}
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;
};