#pragma once
#include <string>
#include <memory>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineBase/GameEngineString.h>

template <typename ResourcesType>
class GameEngineResources
{
private:
	static std::map<std::string, std::shared_ptr<ResourcesType>> NameRes;
	static std::list<std::shared_ptr<ResourcesType>> UnNameRes;

	std::string Name{};
	GameEnginePath Path{};
protected:
	static std::shared_ptr<ResourcesType> CreateRes()
	{
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();
		UnNameRes.push_back(NewRes);
		return NewRes;
	}
	static std::shared_ptr<ResourcesType> CreateRes(std::string_view _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>();
		NewRes->Name = Upper;
		NameRes.emplace(Upper, NewRes);

		return NewRes;
	}
	static std::shared_ptr<ResourcesType> CreateRes(std::string_view _Name,
		std::string_view _Path)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);
		std::shared_ptr<ResourcesType> NewRes = std::make_shared<ResourcesType>(ResourcesType);
		NewRes->Path = _Path;
		NewRes->Name = Upper;
		NameRes.emplace(Upper, NewRes);
	}
public:
	static std::shared_ptr<ResourcesType> Find(std::string_view _Name)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_Name);
		auto FindIter = NameRes.find(Upper);

		if (FindIter == NameRes.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

#pragma region Constructor
	GameEngineResources() {}
	~GameEngineResources() {}
	GameEngineResources(const GameEngineResources&) = delete;
	GameEngineResources(GameEngineResources&&) noexcept = delete;
	GameEngineResources& operator=(const GameEngineResources&) = delete;
	GameEngineResources& operator=(GameEngineResources&&) noexcept = delete;
#pragma endregion
};

template <typename ResourcesType>
std::map<std::string, std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::NameRes;

template <typename ResourcesType>
std::list<std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::UnNameRes;
