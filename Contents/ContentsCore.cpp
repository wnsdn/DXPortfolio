#include "PreCompile.h"
#include "ContentsCore.h"

#include "TitleLevel.h"

void ContentsCore::Start()
{
	GameEngineCore::CreateLevel<TitleLevel>("TitleLevel");
	GameEngineCore::ChangeLevel("TitleLevel");
}

void ContentsCore::Update(float _Delta)
{
}

void ContentsCore::Release()
{
}
