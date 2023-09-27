#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Tile_Main : public GameEngineActor
{
public:
	Tile_Main() {}
	~Tile_Main() {}
	Tile_Main(const Tile_Main&) = delete;
	Tile_Main(Tile_Main&&) noexcept = delete;
	void operator=(const Tile_Main&) = delete;
	void operator=(Tile_Main&&) noexcept = delete;

	void Init(const float4& _Pos);
	void SpriteChange();
	void SpriteReset(UINT _Repeat);
	void Release() override;

	std::vector<std::shared_ptr<Tile_Main>> Others;
	std::shared_ptr<GameEngineSpriteRenderer> Renderer = nullptr;
	std::shared_ptr<GameEngineSpriteRenderer> Effect = nullptr;
	bool EffectOn = false;
	std::shared_ptr<GameEngineCollision> Col = nullptr;
protected:
	void Start() override;
	void Update(float _Delta) override;
};
