#pragma once
#include <Windows.h>
#include <memory>
#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineObject.h"

class GameEngineCore
{
private:
	static GameEngineWindow MainWindow;
	static std::unique_ptr<GameEngineObject> CoreObject;

	static void EngineStart(HINSTANCE _Hinst, std::string_view _Name,
		const POINT& _Pos, const POINT& _Scale);
	static void Start();
	static void Update();
	static void Release();

	GameEngineCore() {}
	~GameEngineCore() {}
	GameEngineCore(const GameEngineCore& _Other) = delete;
	GameEngineCore(GameEngineCore&& _Other) noexcept = delete;
	GameEngineCore& operator=(const GameEngineCore& _Other) = delete;
	GameEngineCore& operator=(GameEngineCore&& _Other) noexcept = delete;
public:
	template <typename ObjectType>
	static void EngineStart(HINSTANCE _Hinst)
	{
		CoreObject = std::make_unique<ObjectType>();
		EngineStart(_Hinst, ObjectType::GetWndName(),
			ObjectType::GetWndPos(), ObjectType::GetWndScale());
	}
public:
	static GameEngineWindow& GetWindow()
	{
		return MainWindow;
	}
};