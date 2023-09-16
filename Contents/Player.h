#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Tile_Main;
class Player : public GameEngineActor
{
public:
	Player() {}
	~Player() {}
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;

	void Init(std::shared_ptr<Tile_Main> _CurTile);
	void SoundUpdate(UINT _Repeat);

	std::shared_ptr<Tile_Main> CurTile = nullptr;
	bool IsOnWorldTile = false;
	bool IsMove = false;
protected:
	void Start() override;
	void Update(float _Delta) override;
private:
	std::shared_ptr<GameEngineSpriteRenderer> Orbit = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Ball1 = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Ball2 = nullptr;
	//std::shared_ptr<GameEngineSpriteRenderer> CurBall = nullptr;

	static const int EffectNum = 10;
	std::shared_ptr<GameEngineSpriteRenderer> Effect[EffectNum]{};
	bool Deploy[EffectNum]{};

	std::shared_ptr<GameEngineCollision> Col = nullptr;

};