#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"

#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineConstantBuffer.h"

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	GameEngineRenderer::ResSetting();

	//CurSprite.Texture->PSSetting(0);
	auto Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex);
	Buffer->ChangeData(CurSprite.SpritePivot);
	Buffer->Setting(1);
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
		MsgBoxAssert("�������� �ʴ� ��������Ʈ�� ����Ϸ��� �߽��ϴ�.");
	}

	CurSprite = Sprite->GetSpriteData(_Index);
	Transform.SetLocalScale(CurSprite.GetScale());
}
