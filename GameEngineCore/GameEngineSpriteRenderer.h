#pragma once
#include "GameEngineRenderer.h"

class GameEngineSpriteRenderer : public GameEngineRenderer
{
protected:
	void Render(GameEngineCamera* _Camera, float _Delta) override;
public:
	void SetSprite(std::string_view _Name);

	GameEngineSpriteRenderer() {}
	~GameEngineSpriteRenderer() {}
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer&) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&&) noexcept = delete;
	void operator=(const GameEngineSpriteRenderer&) = delete;
	void operator=(GameEngineSpriteRenderer&&) noexcept = delete;
};

