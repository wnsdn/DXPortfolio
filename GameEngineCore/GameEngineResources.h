#pragma once
#include <map>
#include <string>
#include <memory>

template <typename ResourcesType>
class GameEngineResources
{
public:
	GameEngineResources() {}
	~GameEngineResources() {}

	static std::shared_ptr<ResourcesType> Find(std::string_view _Name)
	{
		auto FindIter = NameRes.find(std::string(_Name));
		if (NameRes.find(std::string(_Name)) == NameRes.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

	static void Release(std::string_view _Name)
	{
		auto FindIter = NameRes.find(std::string(_Name));
		if (FindIter == NameRes.end())
		{
			assert(false);
			return;
		}

		NameRes.erase(FindIter);
	}

	void SetName(std::string_view _Name)
	{
		Name = _Name;
	}
	std::string GetName() const
	{
		return Name;
	}
protected:
	static std::shared_ptr<ResourcesType> CreateRes()
	{
		auto NewRes = std::make_shared<ResourcesType>();
		UnNameRes.push_back(NewRes);
		return NewRes;
	}
	static std::shared_ptr<ResourcesType> CreateRes(std::string_view _Name)
	{
		auto NewRes = std::make_shared<ResourcesType>();
		NewRes->Name = _Name;
		NameRes.emplace(_Name, NewRes);
		return NewRes;
	}
	static std::shared_ptr<ResourcesType> CreateRes(std::string_view _Name, std::string_view _Path)
	{
		auto NewRes = std::make_shared<ResourcesType>(ResourcesType);
		NewRes->Name = _Name;
		NewRes->Path = _Path;
		NameRes.emplace(_Name, NewRes);
	}

	std::string Name{};
	GameEnginePath Path{};
private:
	static std::map<std::string, std::shared_ptr<ResourcesType>> NameRes;
	static std::list<std::shared_ptr<ResourcesType>> UnNameRes;
};

template <typename ResourcesType>
std::map<std::string, std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::NameRes;

template <typename ResourcesType>
std::list<std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::UnNameRes;
