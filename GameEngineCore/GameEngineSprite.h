#pragma once
#include "GameEngineTexture.h"

class SpriteData
{
public:
	std::shared_ptr<GameEngineTexture> Texture;
	float4 SpritePivot;

	float4 GetScale();
};

class GameEngineSprite : public GameEngineResources<GameEngineSprite>
{
private:
	std::vector<SpriteData> SpriteDatas;
protected:
	void ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y);
public:
	static std::shared_ptr<GameEngineSprite> CreateFolder()
	{
		auto NewRes = CreateRes();
		return NewRes;
	}

	static std::shared_ptr<GameEngineSprite> CreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y)
	{
		auto NewRes = CreateRes(_Name);
		NewRes->ResCreateCut(_Name, _X, _Y);
		return NewRes;
	}

	static std::shared_ptr<GameEngineSprite> CreateSingle(std::string_view _Name)
	{
		auto NewRes = CreateRes(_Name);
		NewRes->ResCreateCut(_Name, 1, 1);
		return NewRes;
	}

	SpriteData GetSpriteData(unsigned int _Index);

	GameEngineSprite() {}
	~GameEngineSprite() {}
	GameEngineSprite(const GameEngineSprite&) = delete;
	GameEngineSprite(GameEngineSprite&&) noexcept = delete;
	void operator=(const GameEngineSprite&) = delete;
	void operator=(GameEngineSprite&&) noexcept = delete;
};

