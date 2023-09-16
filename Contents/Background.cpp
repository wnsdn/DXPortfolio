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
	auto Pos = WndScale.Half();
	Pos.Y *= -1.0f;

	auto Renderer = CreateComponent<GameEngineSpriteRenderer>(ContentsRenderType::BackGround);
	Renderer->SetSprite("title_bg.png");
	Renderer->SetImageScale(WndScale);

	Transform.SetLocalPosition(Pos);
}

void Background::Update(float _Delta)
{
	auto CamPos = GetLevel()->GetMainCamera()->Transform.GetLocalPosition();

	Transform.SetLocalPosition(CamPos);
}