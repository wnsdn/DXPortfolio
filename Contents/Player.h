#pragma once
#include <GameEngineCore/GameEngineActor.h>

class GameEngineSpriteRenderer;
class Player : public GameEngineActor
{
private:
	std::shared_ptr<GameEngineSpriteRenderer> MainSpriteRenderer;
	std::shared_ptr<GameEngineComponent> TestCollision;
	float4 GravityForce{ 0.0f, 0.0f, 0.0f, 1.0f };

	std::shared_ptr<GameEngineCollision> Col;
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

	void TestEvent(GameEngineRenderer* _Renderer);
};