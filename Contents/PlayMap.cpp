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
	Renderer = CreateComponent<GameEngineSpriteRenderer>(-100);
	Renderer->SetSprite("TestMap.png");

	auto Texture = GameEngineTexture::Find("TestMap.png");

	float4 HScale = Texture->GetScale().Half();
	HScale.Y *= -1.0f;

	Renderer->Transform.SetLocalPosition(HScale);
}

void PlayMap::Update(float _Delta)
{
	static float Time = 5.0f;
	Time -= _Delta;

	if (Renderer && Time <= 0.0f)
	{
		Renderer->Death();
		Renderer = nullptr;
	}
}

GameEngineColor PlayMap::GetColor(float4 _Pos, GameEngineColor _DefaultColor)
{
	_Pos.Y *= -1.0f;

	auto Texture = GameEngineTexture::Find("TestMap.png");

	return Texture->GetColor(_Pos, _DefaultColor);
}
