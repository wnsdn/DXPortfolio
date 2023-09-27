#include "PreCompile.h"
#include "MainUIActor.h"

void MainUIActor::Start()
{
	HpBar = CreateComponent<GameEngineUIRenderer>(30);
	HpBar->Transform.SetLocalPosition({ 400, 300 });
	HpBar->SetImageScale({ 300.0f, 30.0f });
}
