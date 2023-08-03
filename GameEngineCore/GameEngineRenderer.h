#pragma once
#include "GameEngineObject.h"

class GameEngineRenderer : public GameEngineObject
{
private:
public:
	GameEngineRenderer() {}
	~GameEngineRenderer() {}
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;
};