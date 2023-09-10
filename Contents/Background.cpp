#include "PreCompile.h"
#include "Background.h"

Background::Background()
{
}

Background::~Background()
{
}

void Background::Start()
{
	auto WndScale = GameEngineWindow::GetInst().GetScale();
	auto HalfWndScale = WndScale.Half();
	HalfWndScale.Y *= -1.0f;

	auto Renderer = CreateComponent<GameEngineSpriteRenderer>(0);
	Renderer->SetSprite("Title_BG.png");
	Renderer->SetImageScale(WndScale);
	Renderer->Transform.SetLocalPosition(HalfWndScale);
}

void Background::Update(float _Delta)
{
}