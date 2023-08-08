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
	std::string Name{};
	float LiveTime = 0.0f;
	int UpdateOrder = 0;
	bool bUpdate = true;
	bool bDeath = false;
protected:
	GameEngineObject* Parent = nullptr;
	std::map<int, std::list<std::shared_ptr<GameEngineObject>>> Childs;
public:
	//GameEngineTransform Transform{};

	virtual void Start() {}
	virtual void Update(float _Delta) {}
	virtual void Release() {}

	virtual void AllUpdate(float _Delta);
#pragma region GetSet
	bool IsUpdate() const
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
	void SetUpdate(bool _bUpdate)
	{
		bUpdate = _bUpdate;
	}
	bool IsDeath() const
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
		return UpdateOrder;
	}
	template <typename EnumType>
	void SetUpdateOrder(EnumType _Order)
	{
		SetUpdateOrder(static_cast<int>(_Order));
	}
	void SetUpdateOrder(int _Order)
	{
		UpdateOrder = _Order;
	}
	float GetLiveTime() const
	{
		return LiveTime;
	}
	void ResetLiveTime()
	{
		LiveTime = 0.0f;
	}
	void AddLiveTime(float _DeltaTime)
	{
		LiveTime += _DeltaTime;
	}
	std::string GetName() const
	{
		return Name;
	}
	void SetName(std::string_view _Name)
	{
		Name = _Name;
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
	void SetParent(GameEngineObject* _Parent)
	{
		Parent = _Parent;
	}
	template <typename ParentType>
	void SetParent(std::shared_ptr<ParentType> _Parent)
	{
		Parent = _Parent.get();
		//Transform.SetParent(_Parent->Transform);
	}
	template <typename ConvertType>
	std::shared_ptr<ConvertType> GetDynamic_Cast_This()
	{
		std::shared_ptr<GameEngineObject> ObjectPtr = shared_from_this();
		std::shared_ptr<ConvertType> CameraPtr =
			std::dynamic_pointer_cast<ConvertType>(ObjectPtr);

		if (!CameraPtr)
		{
			GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		}

		return CameraPtr;
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