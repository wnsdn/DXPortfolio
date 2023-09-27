#pragma once
#include <string>
#include <string_view>
#include <map>
#include <list>
#include <memory>
#include "GameEngineTransform.h"

class GameEngineObjectBase
{
public:
	int GetOrder()
	{
		return Order;
	}

	template <typename EnumType>
	void SetOrder(EnumType _Order)
	{
		SetOrder(static_cast<int>(_Order));
	}
	virtual void SetOrder(int _Order)
	{
		Order = _Order;
	}

	virtual void On()
	{
		IsUpdateValue = true;
	}
	virtual void Off()
	{
		IsUpdateValue = false;
	}

	void Death()
	{
		this->IsDeathValue = true;
	}

	virtual bool IsUpdate()
	{
		return IsUpdateValue && !IsDeathValue;
	}
	virtual bool IsDeath()
	{
		return IsDeathValue;
	}

protected:
	int Order = 0;
	bool IsUpdateValue = true;
	bool IsDeathValue = false;
};

class GameEngineObject : public std::enable_shared_from_this<GameEngineObject>, public GameEngineObjectBase
{
	friend class GameEngineLevel;
	friend class GameEngineCore;
public:
	GameEngineObject() {}
	virtual ~GameEngineObject() {}
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;

	GameEngineTransform Transform;

	virtual void Start() {};
	virtual void Update(float _Delta) {};
	virtual void Release() {};
	virtual void LevelStart(class GameEngineLevel* _PrevLevel) {};
	virtual void LevelEnd(class GameEngineLevel* _NextLevel) {};

	float GetLiveTime() const
	{
		return LiveTime;
	}
	float ResetLiveTime()
	{
		LiveTime = 0.0f;
	}

	void SetName(const std::string& _Name)
	{
		Name = _Name;
	}
	std::string GetName() const
	{
		return Name;
	}

	void AllLevelStart(class GameEngineLevel* _PrevLevel);
	void AllLevelEnd(class GameEngineLevel* _NextLevel);
	virtual void AllReleaseCheck();
	virtual void AllUpdate(float _Delta);

	template <typename ChildType>
	std::shared_ptr<GameEngineObject> CreateChild(int _Order)
	{
		std::shared_ptr<GameEngineObject> NewChild = std::make_shared<ChildType>();
		NewChild->SetOrder(_Order);
		NewChild->SetParent(this, _Order);
		NewChild->Start();
		return NewChild;
	}

	void SetParent(GameEngineObject* _Parent, int _Order)
	{
		Parent = _Parent;
		Parent->Childs[_Order].push_back(shared_from_this());
		Transform.SetParent(_Parent->Transform);
	}
	template <typename ParentType>
	void SetParent(std::shared_ptr<ParentType> _Parent)
	{
		Parent = _Parent.get();
		Transform.SetParent(_Parent->Transform);
	}

	GameEngineObject* GetParentObject() const
	{
		return Parent;
	}

	template <typename ParentType>
	ParentType* GetParent()
	{
		return dynamic_cast<ParentType*>(Parent);
	}

	template <typename ConvertType>
	std::shared_ptr<ConvertType> GetDynamic_Cast_This()
	{
		auto Object = shared_from_this();
		auto Convert = std::dynamic_pointer_cast<ConvertType>(Object);

		if (!Convert)
		{
			assert(false);
			return nullptr;
		}

		return Convert;
	}

	template <typename EnumType>
	std::list<std::shared_ptr<GameEngineObject>> GetObjectGroup(EnumType _GroupIndex)
	{
		return GetObjectGroup(static_cast<int>(_GroupIndex));
	}
	template <typename ObjectType>
	std::list<std::shared_ptr<GameEngineObject>> GetObjectGroup(int _GroupIndex)
	{
		auto& Group = Childs[_GroupIndex];
		return Group;
	}

	template <typename ObjectType, typename EnumType>
	std::list<std::shared_ptr<ObjectType>> GetObjectGroupConvert(EnumType _GroupIndex)
	{
		return GetObjectGroupConvert<ObjectType>(static_cast<int>(_GroupIndex));
	}
	template <typename ObjectType>
	std::list<std::shared_ptr<ObjectType>> GetObjectGroupConvert(int _GroupIndex)
	{
		std::list<std::shared_ptr<ObjectType>> Result;
		auto& Group = Childs[_GroupIndex];
		for (auto& Object : Group)
		{
			auto Ptr = Object->GetDynamic_Cast_This<ObjectType>();

			if (!Ptr)
			{
				continue;
			}

			Result.push_back(Ptr);
		}

		return Result;
	}

	bool IsUpdate() override
	{
		if (!Parent)
		{
			return IsUpdateValue && !IsDeathValue;
		}
		else
		{
			return Parent->IsUpdate() && IsUpdateValue && !IsDeath();
		}
	}
	bool IsDeath() override
	{
		if (!Parent)
		{
			return IsDeathValue;
		}
		else
		{
			return Parent->IsDeath() || IsDeathValue;
		}
	}
protected:
	GameEngineObject* Parent = nullptr;
	std::map<int, std::list<std::shared_ptr<class GameEngineObject>>> Childs;
private:
	std::string Name{};
	float LiveTime = 0.0f;

	void AddLiveTime(float _Delta)
	{
		LiveTime += _Delta;
	}

	void AllRelease();
};