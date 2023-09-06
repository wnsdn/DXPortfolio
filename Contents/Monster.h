#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Monster : public GameEngineActor
{
private:

protected:
	void Start() override;
public:
	Monster();
	~Monster();
	Monster(const Monster&) = delete;
	Monster(Monster&&) noexcept = delete;
	void operator=(const Monster&) = delete;
	void operator=(Monster&&) noexcept = delete;

	std::shared_ptr<GameEngineSpriteRenderer> Renderer;
};
