#pragma once
#include "GameEngineTexture.h"

class SpriteData
{
	std::shared_ptr<GameEngineTexture> Texture;
};

class GameEngineSprite : public GameEngineResources<GameEngineSprite>
{
private:
	std::vector<SpriteData> GameEngineSpriteData;
public:
	static std::shared_ptr<GameEngineSprite> CreateFolder()
	{
		auto NewRes = CreateRes();
		return NewRes;
	}

	static std::shared_ptr<GameEngineSprite> CreateCut()
	{
		auto NewRes = CreateRes();
		return NewRes;
	}

	GameEngineSprite() {}
	~GameEngineSprite() {}
	GameEngineSprite(const GameEngineSprite&) = delete;
	GameEngineSprite(GameEngineSprite&&) noexcept = delete;
	void operator=(const GameEngineSprite&) = delete;
	void operator=(GameEngineSprite&&) noexcept = delete;
};

