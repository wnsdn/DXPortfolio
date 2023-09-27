#pragma once
#include <Windows.h>
#include <memory>
#include <map>
#include <GameEngineBase/GameEngineString.h>
#include <GameEngineBase/GameEngineDebug.h>
#include "GameEngineDevice.h"
#include <assert.h>
#include <d3d11.h>

class GameEngineObject;
class GameEngineLevel;
class GameEngineCore
{
public:
	template <typename CoreType>
	static void EngineStart(HINSTANCE _Hinst)
	{
		CoreObject = std::make_shared<CoreType>();
		EngineStart(_Hinst, CoreType::GetWndName(), CoreType::GetWndPos(), CoreType::GetWndScale());
	}

	template <typename LevelType>
	static void CreateLevel(const std::string& _Name)
	{
		if (AllLevel.find(_Name) != AllLevel.end())
		{
			assert(false);
			return;
		}

		auto NewLevel = std::make_shared<LevelType>();
		LevelInit(NewLevel);
		AllLevel.emplace(_Name, NewLevel);
	}
	static void ChangeLevel(const std::string& _Name)
	{
		auto FindIter = AllLevel.find(_Name);

		if (FindIter == AllLevel.end())
		{
			assert(false);
			return;
		}

		NextLevel = FindIter->second;
	}
	//static std::shared_ptr<GameEngineLevel> FindLevel()

	static ID3D11Device* GetDevice()
	{
		return MainDevice.GetDevice();
	}
	static ID3D11DeviceContext* GetContext()
	{
		return MainDevice.GetContext();
	}
	static std::shared_ptr<GameEngineRenderTarget> GetBackBufferRenderTarget()
	{
		return MainDevice.GetBackBufferRenderTarget();
	}
private:
	static std::shared_ptr<GameEngineObject> CoreObject;
	static std::shared_ptr<GameEngineLevel> CurLevel;
	static std::shared_ptr<GameEngineLevel> NextLevel;
	static std::map<std::string, std::shared_ptr<GameEngineLevel>> AllLevel;
	static GameEngineDevice MainDevice;

	static void EngineStart(HINSTANCE _Hinst, std::string_view _Name, const POINT& _Pos, const POINT& _Scale);
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
};