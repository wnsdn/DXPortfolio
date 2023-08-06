#pragma once
#include <Windows.h>
#include <memory>
#include <map>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>

class GameEngineObject;
class GameEngineLevel;
class GameEngineCore
{
private:
	static std::shared_ptr<GameEngineObject> CoreObject;
	static std::shared_ptr<GameEngineLevel> CurLevel;
	static std::shared_ptr<GameEngineLevel> NextLevel;
	static std::map<std::string, std::shared_ptr<GameEngineLevel>> AllLevel;

	static void EngineStart(HINSTANCE _Hinst, std::string_view _Name,
		const POINT& _Pos, const POINT& _Scale);
	static void Start();
	static void Update();
	static void Release();

	static void LevelInit(std::shared_ptr<GameEngineLevel> _Level);

	GameEngineCore() {}
	~GameEngineCore() {}
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;
public:
	template <typename CoreType>
	static void EngineStart(HINSTANCE _Hinst)
	{
		CoreObject = std::make_shared<CoreType>();
		EngineStart(_Hinst,
			CoreType::GetWndName(),
			CoreType::GetWndPos(),
			CoreType::GetWndScale());
	}

	template <typename LevelType>
	static void CreateLevel(std::string_view _LevelName)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_LevelName);

		if (AllLevel.find(Upper) != AllLevel.end())
		{
			GameEngineDebug::MsgBoxAssert(Upper + "Already Exist");
			return;
		}

		std::shared_ptr<GameEngineLevel> NewLevel = std::make_shared<LevelType>();
		LevelInit(NewLevel);
		AllLevel.emplace(Upper, NewLevel);
	}
	static void ChangeLevel(std::string_view _LevelName)
	{
		std::string Upper = GameEngineString::ToUpperReturn(_LevelName);
		auto FindIter = AllLevel.find(Upper);

		if (FindIter == AllLevel.end())
		{
			GameEngineDebug::MsgBoxAssert(Upper + "Not Exist");
			return;
		}

		NextLevel = FindIter->second;
	}
};