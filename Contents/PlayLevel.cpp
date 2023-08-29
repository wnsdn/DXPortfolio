#include "PreCompile.h"
#include "PlayLevel.h"

#include "Player.h"
#include <GameEngineCore\GameEngineTexture.h>
#include <GameEngineCore\GameEngineSprite.h>

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
