#pragma once
#include "GameEngineSpriteRenderer.h"

class GameEngineUIRenderer : public GameEngineSpriteRenderer
{
public:
	GameEngineUIRenderer();
	~GameEngineUIRenderer();
	GameEngineUIRenderer(const GameEngineUIRenderer&) = delete;
	GameEngineUIRenderer(GameEngineUIRenderer&&) noexcept = delete;
	void operator=(const GameEngineUIRenderer&) = delete;
	void operator=(GameEngineUIRenderer&&) noexcept = delete;
protected:
	void Start() override;
private:

};
