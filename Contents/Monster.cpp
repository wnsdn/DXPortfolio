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
	float4 Scale = GameEngineRandom::RandomVectorBox2D(10, 100, 10, 100);

	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(30);

		Renderer->SetSprite("HoHoYee_AttackABC2");
		Renderer->Transform.SetLocalScale(Scale);
	}

	{
		auto Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Monster);
		Col->Transform.SetLocalScale(Scale);
	}
}
