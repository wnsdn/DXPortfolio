#pragma once
#include "GameEngineTexture.h"

class SpriteData
{
public:
	std::shared_ptr<GameEngineTexture> Texture;
	float4 Pivot;

	float4 GetScale();
};

class GameEngineSprite : public GameEngineResources<GameEngineSprite>
{
public:
	GameEngineSprite() {}
	~GameEngineSprite() {}
	GameEngineSprite(const GameEngineSprite&) = delete;
	GameEngineSprite(GameEngineSprite&&) noexcept = delete;
	void operator=(const GameEngineSprite&) = delete;
	void operator=(GameEngineSprite&&) noexcept = delete;

	static std::shared_ptr<GameEngineSprite> CreateFolder(std::string_view _Path)
	{
		GameEnginePath Path;
		Path.SetPath(_Path);
		return CreateFolder(Path.GetPath(), Path.GetFilename());
	}

	static std::shared_ptr<GameEngineSprite> CreateFolder(std::string_view _Path, std::string_view _Name)
	{
		auto NewRes = CreateRes(_Name);
		NewRes->ResCreateFolder(_Path);
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
	unsigned int GetSpriteCount()
	{
		return static_cast<unsigned int>(SpriteDatas.size());
	}
protected:
	void ResCreateCut(std::string_view _Name, unsigned int _X, unsigned int _Y);
	void ResCreateFolder(std::string_view _Path);
private:
	std::vector<SpriteData> SpriteDatas;
};

