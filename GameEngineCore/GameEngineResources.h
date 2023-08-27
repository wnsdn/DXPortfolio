#pragma once

template <typename ResourcesType>
class GameEngineResources
{
private:
	static std::map<std::string, std::shared_ptr<ResourcesType>> NameRes;
	static std::list<std::shared_ptr<ResourcesType>> UnNameRes;
protected:
	std::string Name{};
	GameEnginePath Path{};
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
	static std::shared_ptr<ResourcesType> CreateRes(
		std::string_view _Name,
		std::string_view _Path)
	{
		auto NewRes = std::make_shared<ResourcesType>(ResourcesType);
		NewRes->Name = _Name;
		NewRes->Path = _Path;
		NameRes.emplace(_Name, NewRes);
	}
public:
	static std::shared_ptr<ResourcesType> Find(const std::string& _Name)
	{
		auto FindIter = NameRes.find(_Name);

		if (FindIter == NameRes.end())
		{
			return nullptr;
		}

		return FindIter->second;
	}

	void SetName(std::string_view _Name)
	{
		Name = _Name;
	}

	GameEngineResources() {}
	~GameEngineResources() {}
	GameEngineResources(const GameEngineResources&) = delete;
	GameEngineResources(GameEngineResources&&) noexcept = delete;
	void operator=(const GameEngineResources&) = delete;
	void operator=(GameEngineResources&&) noexcept = delete;
};

template <typename ResourcesType>
std::map<std::string, std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::NameRes;

template <typename ResourcesType>
std::list<std::shared_ptr<ResourcesType>> GameEngineResources<ResourcesType>::UnNameRes;
