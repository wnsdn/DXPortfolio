#include "PreCompile.h"
#include "Player.h"

void Player::Start()
{
	float4 WndCenter{ GameEngineWindow::GetInst().GetScale().Half() };
	WndCenter.Y *= -1.0f;

	auto Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
	Renderer->SetSprite("TestRect");
	Renderer->SetImageScale({ 50.0f, 50.0f });

	Collision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Player);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale(Renderer->GetImageScale());

	Transform.SetLocalPosition(WndCenter);
}

void Player::Update(float _Delta)
{
	float Speed = 300.0f;
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
	if (GameEngineInput::IsDown('Z'))
	{
		//MainSpriteRenderer->AnimationPauseSwitch();
	}
}
