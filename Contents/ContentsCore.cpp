#include "PreCompile.h"
#include "ContentsCore.h"

#include "PlayLevel.h"
#include "TitleLevel.h"

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<PlayLevel>("PlayLevel");
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("PlayLevel");
}

void ContentsCore::Update(float _Delta)
{
}

void ContentsCore::Release()
{
}
