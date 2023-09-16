#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Tile_Play : public GameEngineActor
{
public:
	Tile_Play() {}
	~Tile_Play() {}
	Tile_Play(const Tile_Play&) = delete;
	Tile_Play(Tile_Play&&) noexcept = delete;
	void operator=(const Tile_Play&) = delete;
	void operator=(Tile_Play&&) noexcept = delete;
protected:
	void Start() override;
	void Update(float _Delta) override;
private:

};
