#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"

#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	GameEngineRenderer::ResSetting();

	CurSprite.Texture->PSSetting(0);

	auto Sampler = GameEngineSampler::Find("Sampler");
	Sampler->PSSetting(0);

	GameEngineRenderer::Draw();
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name, unsigned int _Index)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (!Sprite)
	{
		MsgBoxAssert("존재하지 않는 스프라이트를 사용하려고 했습니다.");
	}

	CurSprite = Sprite->GetSpriteData(_Index);
	Transform.SetLocalScale(CurSprite.GetScale());
}
