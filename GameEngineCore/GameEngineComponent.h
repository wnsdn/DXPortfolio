#pragma once

class GameEngineComponent
{
private:
public:
	GameEngineComponent() {}
	~GameEngineComponent() {}
	GameEngineComponent(const GameEngineComponent& _Other) = delete;
	GameEngineComponent(GameEngineComponent&& _Other) noexcept = delete;
	GameEngineComponent& operator=(const GameEngineComponent& _Other) = delete;
	GameEngineComponent& operator=(GameEngineComponent&& _Other) noexcept = delete;
};