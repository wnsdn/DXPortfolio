#include "PreCompile.h"
#include "PlayLevel.h"

#include "Player.h"

void PlayLevel::Start()
{
	GameEngineDirectory Dir;
	Dir.SetPath("ContentsResources");
	auto TFiles = Dir.GetAllTextureFile();
	for (auto& File : TFiles)
	{
		GameEngineTexture::Load(File.ToString(), File.GetFilename());
	}

	GameEngineSprite::CreateCut("TestPlayer.png", 6, 6);

	GetMainCamera()->Transform.SetLocalPosition({ 0.0f, 0.0f, -500.0f });
	GetMainCamera()->SetProjectionType(EPROJECTIONTYPE::Perspective);

	std::shared_ptr<Player> NewPlayer = CreateActor<Player>();
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
