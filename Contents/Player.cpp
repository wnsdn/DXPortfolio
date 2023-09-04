#include "PreCompile.h"
#include "Player.h"

#include <GameEngineCore/GameEngineRenderer.h>
#include <GameEngineCore/GameEngineSpriteRenderer.h>
#include <GameEngineCore/GameEngineTexture.h>

#include "PlayMap.h"

void Player::Start()
{
	MainSpriteRenderer = CreateComponent<GameEngineSpriteRenderer>(0);
	MainSpriteRenderer->CreateAnimation("Run", "HoHoYee_AttackABC", 0.05f, -1, -1, true);
	MainSpriteRenderer->ChangeAnimation("Run");
	MainSpriteRenderer->SetSamplerState(SamplerOption::LINEAR);
	MainSpriteRenderer->Transform.SetLocalPosition({ 100.0f, 0.0f, 0.0f });

	MainSpriteRenderer->SetEndEvent("Run", std::bind(&Player::TestEvent, this, std::placeholders::_1));

	MainSpriteRenderer->AutoSpriteSizeOn();
	MainSpriteRenderer->SetAutoScaleRatio(2.0f);

	auto HalfWindowScale = GameEngineWindow::GetInst().GetScale().Half();
	Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
}

void Player::Update(float _Delta)
{
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

	GameEngineColor Color = PlayMap::MainMap->GetColor(Transform.GetWorldPosition(), GameEngineColor::RED);

	if (GameEngineColor::RED != Color)
	{
		GravityForce.Y -= _Delta * 100.0f;
		Transform.AddLocalPosition(GravityForce * _Delta);
	}
	else
	{
		GravityForce = 0.0f;
	}
}

void Player::TestEvent(GameEngineRenderer* _Renderer)
{
	int a = 0;
}
