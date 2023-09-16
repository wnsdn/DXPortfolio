#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSpriteRenderer.h"

class Tile
{
public:
	SpriteData Data;
	int Index = -1;
};

class CreateTileParameter
{
public:
	size_t TileCountX = 10;
	size_t TileCountY = 10;
	float4 TileScale{ 50.0f, 50.0f };
	std::string_view SpriteName = "";
};

class SetTileParameterIndex
{
public:
	size_t X = -1;
	size_t Y = -1;
	unsigned int Index = 0;
	std::string_view SpriteName = "";
};

class SetTileParameterPos
{
public:
	float4 Pos;
	unsigned int Index = 0;
	std::string_view SpriteName = "";

	SetTileParameterPos(const float4& _Pos, unsigned int _Index = 0, std::string_view _SpriteName = "")
		: Pos(_Pos), Index(_Index), SpriteName(_SpriteName)
	{
	}
};

class GameEngineTilemap : public GameEngineRenderer
{
public:
	GameEngineTilemap();
	~GameEngineTilemap();
	GameEngineTilemap(const GameEngineTilemap&) = delete;
	GameEngineTilemap(GameEngineTilemap&&) noexcept = delete;
	void operator=(const GameEngineTilemap&) = delete;
	void operator=(GameEngineTilemap&&) noexcept = delete;

	void CreateTileMap(const CreateTileParameter& _Parameter);
	void SetTileIndex(const SetTileParameterIndex& _Parameter);
	void SetTilePos(const SetTileParameterPos& _Parameter);
protected:
	void Render(GameEngineCamera* _Camera, float _Delta) override;
private:
	CreateTileParameter TileData;
	std::shared_ptr<GameEngineSprite> DefaultSprite;
	std::vector<std::vector<Tile>> Tiles;
};
