#include "PreCompile.h"
#include "Player.h"

#include <GameEngineCore/GameEngineTexture.h>

#include "ContentsEnum.h"
#include "PlayMap.h"
#include "Monster.h"

void Player::Start()
{
	{
		TestCollision = CreateComponent<GameEngineComponent>(30);
		TestCollision->Transform.SetLocalScale({ 30, 30, 1 });

		MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(30);
		MainSpriteRenderer->SetSprite("HoHoYee_AttackABC2");
		MainSpriteRenderer->Transform.SetLocalScale({ -100.0f, 100.0f, 1.0f });
	}

	{
		Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
		Col->Transform.SetLocalScale({ -100.0f, 100.0f, 1.0f });
	}

	auto HalfWindowScale = GameEngineWindow::GetInst().GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
}

void Player::Update(float _Delta)
{
	EventParameter Event;

	Event.Enter = [](GameEngineCollision* Col)
		{
			int a = 0;
		};
	Event.Stay = [](GameEngineCollision* Col)
		{
			int a = 0;
		};
	Event.Exit = [](GameEngineCollision* Col)
		{
			Col->GetActor()->Death();
			int a = 0;
		};
	Col->CollisionEvent(ContentsCollisionType::Monster, Event);

	float Speed = 150.0f;

	if (GameEngineInput::IsDown('Z'))
	{
		MainSpriteRenderer->AnimationPauseSwitch();
	}

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

void Player::TestEvent(GameEngineRenderer* _Renderer)
{
	int a = 0;
}
