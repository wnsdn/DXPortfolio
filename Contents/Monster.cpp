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
	{
		Renderer = CreateComponent<GameEngineSpriteRenderer>(30);

		Renderer->SetSprite("HoHoYee_AttackABC2");
		Renderer->Transform.SetLocalScale(GameEngineRandom::RandomVectorBox2D(10, 100, 10, 100));
	}
}
