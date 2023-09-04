#include "PreCompile.h"
#include "PlayMap.h"

PlayMap* PlayMap::MainMap;

PlayMap::PlayMap()
{
	MainMap = this;
}

PlayMap::~PlayMap()
{
}

void PlayMap::Start()
{
	auto Renderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	Renderer->SetSprite("TestMap.png");

	auto Texture = GameEngineTexture::Find("TestMap.png");

	float4 HScale = Texture->GetScale().Half();
	HScale.Y *= -1.0f;

	Renderer->Transform.SetLocalPosition(HScale);
}

GameEngineColor PlayMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	_Pos.Y *= -1.0f;

	auto Texture = GameEngineTexture::Find("TestMap.png");

	return Texture->GetColor(_Pos, _DefaultColor);
}
