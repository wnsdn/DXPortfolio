#include "PreCompile.h"
#include "Monster.h"

Monster::Monster()
{
}

Monster::~Monster()
{
}

void Monster::Start()
{
	float4 WndScale = GameEngineWindow::GetInst().GetScale();
	float4 Scale = GameEngineRandom::RandomVectorBox2D(10, 100, 10, 100);
	float4 Pos = GameEngineRandom::RandomVectorBox2D(Scale.X, WndScale.X - Scale.X, -Scale.Y, -WndScale.Y + Scale.Y);

	auto Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
	Renderer->SetSprite("TestRect");
	Renderer->SetImageScale(Scale);

	auto Collision = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
	Collision->SetCollisionType(ColType::AABBBOX2D);
	Collision->Transform.SetLocalScale(Renderer->GetImageScale());

	Transform.SetLocalPosition(Pos);
}

void Monster::Update(float _Delta)
{
}
