#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class Player : public GameEngineActor
{
private:
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer;
protected:
	void Start() override;
	void Update(float _Delta) override;
public:
	Player() {}
	~Player() {}
	Player(const Player& _Other) = delete;
	Player(Player&& _Other) noexcept = delete;
	Player& operator=(const Player& _Other) = delete;
	Player& operator=(Player&& _Other) noexcept = delete;
};