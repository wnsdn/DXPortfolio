#include "PreCompile.h"
#include "PlayLevel.h"

#include "Player.h"
#include "PlayMap.h"
#include "Monster.h"

void PlayLevel::Start()
{
	{
		GameEngineDirectory Dir;
		Dir.SetFilenameToPath("ContentsResources");
		auto AllPath = Dir.GetAllFileInDir("Texture");
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

	GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);
	GameEngineSprite::CreateSingle("TestMap.png");

	auto HalfWindowScale = GameEngineWindow::GetInst().GetScale().Half();
	GetMainCamera()->Transform.SetLocalPosition({ HalfWindowScale.X, -HalfWindowScale.Y, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Orthographic);

	{
		CreateActor<Player>(ContentsObjectType::Player);
	}

	{
		for (int i = 0; i < 10; ++i)
		{
			CreateActor<Monster>(ContentsObjectType::Monster)->Transform.SetLocalPosition(GameEngineRandom::RandomVectorBox2D(0, 1280, 0, -720));
		}

		for (int i = 0; i < 4; ++i)
		{
			//CreateActor<PlayMap>(ContentsObjectType::Monster);
		}
	}

	{
		Map = CreateActor<PlayMap>(ContentsObjectType::BackGround);
	}
}

void PlayLevel::Update(float _Delta)
{

}

void PlayLevel::LevelStart(GameEngineLevel* _PrevLevel)
{
	int a = 0;
}

void PlayLevel::LevelEnd(GameEngineLevel* _NextLevel)
{
	int a = 0;
}
