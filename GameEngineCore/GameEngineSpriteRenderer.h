#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"

class GameEngineSpriteRenderer : public GameEngineRenderer
{
private:
	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;
protected:
	int Index = 0;

	void Render(GameEngineCamera* _Camera, float _Delta) override;
public:
	void SetSprite(std::string_view _Name, unsigned int _Index = 0);

	GameEngineSpriteRenderer() {}
	~GameEngineSpriteRenderer() {}
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer&) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&&) noexcept = delete;
	void operator=(const GameEngineSpriteRenderer&) = delete;
	void operator=(GameEngineSpriteRenderer&&) noexcept = delete;
};

