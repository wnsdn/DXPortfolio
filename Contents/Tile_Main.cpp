#include "PreCompile.h"
#include "Tile_Main.h"

void Tile_Main::Init(const float4& _Pos)
{
	auto Pos = _Pos;
	Pos.Y *= -1.0f;

	Transform.SetLocalPosition(Pos);
}

void Tile_Main::SpriteChange()
{
	if (Effect->IsCurSprite("bottomglow_E.png"))
	{
		Effect->SetSprite("bottomglow_F.png");
		Effect->SetImageScale({ 60.0f, 60.0f });
	}
	else
	{
		Effect->SetSprite("bottomglow_E.png");
		Effect->SetImageScale({ 60.0f, 60.0f });
	}
}

void Tile_Main::SpriteReset(UINT _Repeat)
{
	static UINT Repeat = _Repeat;

	if (Repeat != _Repeat)
	{
		Repeat = _Repeat;
		SpriteChange();
	}
}

void Tile_Main::Start()
{
	Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
	Renderer->SetSprite("tile_unlit.png");
	Renderer->SetImageScale({ 52.0f, 52.0f });

	Effect = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::Play);
	Effect->SetSprite("bottomglow_F.png");
	Effect->SetImageScale({ 60.0f, 60.0f });
	Effect->SetAlpha(0.0f);

	Col = CreateComponent<GameEngineCollision>(ContentsCollisionType::Tile);
	Col->Transform.SetLocalScale({ 52.0f, 52.0f });
}

void Tile_Main::Update(float _Delta)
{
}

void Tile_Main::Release()
{
	for (auto& Other : Others)
	{
		Other = nullptr;
	}
}
