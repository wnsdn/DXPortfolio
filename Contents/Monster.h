#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Monster : public GameEngineActor
{
private:

protected:
	void Start() override;
	void Update(float _Delta) override;
public:
	Monster();
	~Monster();
	Monster(const Monster&) = delete;
	Monster(Monster&&) noexcept = delete;
	void operator=(const Monster&) = delete;
	void operator=(Monster&&) noexcept = delete;
};
