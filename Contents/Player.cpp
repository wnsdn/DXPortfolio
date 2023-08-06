#include "PreCompile.h"
#include "Player.h"

#include <GameEngineCore/GameEngineRenderer.h>

void Player::Start()
{
	std::shared_ptr<GameEngineRenderer> Renderer = CreateComponent<GameEngineRenderer>(0);
}

void Player::Update(float _Delta)
{
}
