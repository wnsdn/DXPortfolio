#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class Player;
class Tile_Main;
class TitleLevel : public GameEngineLevel
{
public:
	TitleLevel();
	~TitleLevel();
	TitleLevel(const TitleLevel&) = delete;
	TitleLevel(TitleLevel&&) noexcept = delete;
	void operator=(const TitleLevel&) = delete;
	void operator=(TitleLevel&&) noexcept = delete;
protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
private:
	std::shared_ptr<Player> MainPlayer;

	static const int MainX = 5;
	static const int MainY = 5;

	static const int WorldX = 7;

	std::shared_ptr<Tile_Main> MainTile[MainY][MainX];
	std::shared_ptr<Tile_Main> WorldTile[WorldX];
};
