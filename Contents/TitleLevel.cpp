#include "PreCompile.h"
#include "TitleLevel.h"

#include "Background.h"

TitleLevel::TitleLevel()
{
}

TitleLevel::~TitleLevel()
{
}

void TitleLevel::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.SetFilenameToPath("ContentsResources");
		auto AllPath = Dir.GetAllFileInDir("Title");
		for (auto& Path : AllPath)
		{
			GameEngineFile File;
			File.SetPath(Path.GetPath());
			GameEngineTexture::Load(File.GetPath());
		}
	}
	{
		GameEngineDirectory Dir;
		Dir.SetFilenameToPath("ContentsResources");
		auto AllPath = Dir.GetAllDirInDir("FolderTexture");
		for (auto& Path : AllPath)
		{
			GameEngineFile File;
			File.SetPath(Path.GetPath());
			GameEngineSprite::CreateFolder(File.GetPath());
		}
	}

	GameEngineSprite::CreateSingle("Title_BG.png");

	{
		CreateActor<Background>(ContentsObjectType::BackGround);
	}

	float4 HalfWndScale = GameEngineWindow::GetInst().GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWndScale.X, -HalfWndScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);
}

void TitleLevel::Update(float _Delta)
{
	if (GameEngineInput::IsPress('P'))
	{
		GameEngineCore::ChangeLevel("PlayLevel");
	}
}

void TitleLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void TitleLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}
