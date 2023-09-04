#pragma once
#include <string>
#include <string_view>
#include <map>
#include <list>
#include <memory>
#include "GameEngineTransform.h"

class GameEngineObject : public std::enable_shared_from_this<GameEngineObject>
{
private:
protected:
	std::string Name{};
	float LiveTime = 0.0f;
	int UpdateOrder = 0;
	bool bUpdate = true;
	bool bDeath = false;

	GameEngineObject* Parent = nullptr;
	std::map<int, std::list<std::shared_ptr<GameEngineObject>>> Childs;
public:
	GameEngineTransform Transform{};

	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Release() {}
	virtual void LevelStart(GameEngineLevel* _PrevLevel) {}
	virtual void LevelEnd(GameEngineLevel* _NextLevel) {}

	void AllLevelStart(GameEngineLevel* _PrevLevel);
	void AllLevelEnd(GameEngineLevel* _NextLevel);

	virtual void AllReleaseCheck();
	virtual void AllUpdate(float _Delta);

	template <typename ConvertType>
	std::shared_ptr<ConvertType> GetDynamic_Cast_This()
	{
		std::shared_ptr<GameEngineObject> ObjectPtr = shared_from_this();
		std::shared_ptr<ConvertType> CameraPtr =
			std::dynamic_pointer_cast<ConvertType>(ObjectPtr);

		if (!CameraPtr)
		{
			MsgBoxAssert(__FUNCTION__);
		}

		return CameraPtr;
	}

	template <typename ObjectType>
	std::list<std::shared_ptr<ObjectType>> GetObjectGroupConvert(int _GroupIndex)
	{
		std::list<std::shared_ptr<ObjectType>> Result;
		for (auto& Object : Childs[_GroupIndex])
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

#pragma region BasicFunction
	std::string_view GetName() const
	{
		return Name;
	}
	void SetName(std::string_view _Name)
	{
		Name = _Name;
	}
	float GetLiveTime() const
	{
		return LiveTime;
	}
	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}
	void AddLiveTime(float _Delta)
	{
		LiveTime += _Delta;
	}
	int GetOrder() const
	{
		return UpdateOrder;
	}
	template <typename EnumType>
	void SetOrder(EnumType _Order)
	{
		UpdateOrder = static_cast<int>(_Order);
	}
	bool IsUpdate() const
	{
		if (Parent)
		{
			return Parent->IsUpdate() && bUpdate && !IsDeath();
		}
		else
		{
			return bUpdate && !bDeath;
		}
	}
	void On()
	{
		bUpdate = true;
	}
	void Off()
	{
		bUpdate = false;
	}
	bool IsDeath() const
	{
		if (Parent)
		{
			return Parent->IsDeath() || bDeath;
		}
		else
		{
			return bDeath;
		}
	}
	void Death()
	{
		bDeath = true;
		bUpdate = false;
	}
	GameEngineObject* GetParent() const
	{
		return Parent;
	}
	template <typename ParentType>
	ParentType* GetParent() const
	{
		return dynamic_cast<ParentType*>(Parent);
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
#pragma endregion

#pragma region Constructor
	GameEngineObject() {}
	virtual ~GameEngineObject() {}
	GameEngineObject(const GameEngineObject& _Other) = delete;
	GameEngineObject(GameEngineObject&& _Other) noexcept = delete;
	GameEngineObject& operator=(const GameEngineObject& _Other) = delete;
	GameEngineObject& operator=(GameEngineObject&& _Other) noexcept = delete;
#pragma endregion
};