#include "PreCompile.h"
#include "PlayLevel.h"

#include "Player.h"

void PlayLevel::Start()
{
	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();
}

void PlayLevel::Update(float _Delta)
{
	float Speed = 300.0f;
	if (GameEngineInput::IsPress('A'))
	{
		GetMainCamera()->Transform.GetTransformDataRef().Position += float4::Left * Speed * _Delta;
	}
	else if (GameEngineInput::IsPress('D'))
	{
		GetMainCamera()->Transform.GetTransformDataRef().Position += float4::Right * Speed * _Delta;
	}
	if (GameEngineInput::IsPress('W'))
	{
		GetMainCamera()->Transform.GetTransformDataRef().Position += float4::Front * Speed * _Delta;
	}
	else if (GameEngineInput::IsPress('S'))
	{
		GetMainCamera()->Transform.GetTransformDataRef().Position += float4::Back * Speed * _Delta;
	}
	if (GameEngineInput::IsPress(VK_UP))
	{
		GetMainCamera()->Transform.GetTransformDataRef().Position += float4::Up * Speed * _Delta;
	}
	else if (GameEngineInput::IsPress(VK_DOWN))
	{
		GetMainCamera()->Transform.GetTransformDataRef().Position += float4::Down * Speed * _Delta;
	}
	if (GameEngineInput::IsPress('Q'))
	{
		GetMainCamera()->Transform.GetTransformDataRef().Rotation.Y += 360.0f * _Delta / 4.0f;
	}
	else if (GameEngineInput::IsPress('E'))
	{
		GetMainCamera()->Transform.GetTransformDataRef().Rotation.Y -= 360.0f * _Delta / 4.0f;
	}

	GetMainCamera()->Transform.TransformUpdate();
}
