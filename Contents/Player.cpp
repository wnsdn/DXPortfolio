#include "PreCompile.h"
#include "Player.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

void Player::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
	MainSpriteRenderer->SetSprite("TestPlayer.png", 5);
}

void Player::Update(float _Delta)
{
	float Speed = 150.0f;

	if (GameEngineInput::IsPress('A'))
	{
		Transform.AddLocalPosition(float4::Left * _Delta * Speed);
	}
	else if (GameEngineInput::IsPress('D'))
	{
		Transform.AddLocalPosition(float4::Right * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('W'))
	{
		Transform.AddLocalPosition(float4::Up * _Delta * Speed);
	}
	else if (GameEngineInput::IsPress('S'))
	{
		Transform.AddLocalPosition(float4::Down * _Delta * Speed);
	}

	if (GameEngineInput::IsPress('Q'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, 360.0f * _Delta });
	}
	else if (GameEngineInput::IsPress('E'))
	{
		Transform.AddLocalRotation({ 0.0f, 0.0f, -360.0f * _Delta });
	}
}
