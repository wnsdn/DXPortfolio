#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"

#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineConstantBuffer.h"

void GameEngineFrameAnimation::Reset()
{
	CurTime = 0.0f;
	CurIndex = 0;
	IsEnd = false;
	EventCheck = true;
}

SpriteData GameEngineFrameAnimation::Update(float _Delta)
{
	if (Parent->IsPause)
	{
		return Sprite->GetSpriteData(Index[CurIndex]);
	}

	if (Loop)
	{
		IsEnd = false;
	}

	if (EventCheck && !IsEnd)
	{
		EventCall(CurIndex);
		EventCheck = false;
	}

	CurTime += _Delta;

	if (CurTime >= Inter[CurIndex])
	{
		++CurIndex;
		EventCheck = true;
		CurTime -= Inter[CurIndex];

		if (CurIndex > End - Start)
		{
			if (EndEvent && !IsEnd)
			{
				EndEvent(Parent);
			}

			IsEnd = true;

			if (Loop)
			{
				CurIndex = 0;
			}
			else
			{
				--CurIndex;
			}
		}
	}

	return Sprite->GetSpriteData(Index[CurIndex]);
}

void GameEngineFrameAnimation::EventCall(int _Frame)
{
	if (FrameEventFunction.contains(Index[_Frame]))
	{
		FrameEventFunction[Index[_Frame]](Parent);
	}
}

GameEngineSpriteRenderer::GameEngineSpriteRenderer()
{
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}

void GameEngineSpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	ImageTransform.SetParent(Transform);

	SetMesh("Rect");
	SetMaterial("2DTexture");

	auto& Data = ImageTransform.GetConstTransformDataRef();
	GetShaderResHelper().SetConstantBufferLink("TransformData", Data);
	GetShaderResHelper().SetConstantBufferLink("SpriteData", CurSprite.Pivot);
	GetShaderResHelper().SetConstantBufferLink("AlphaData", Alpha);
	GetShaderResHelper().SetConstantBufferLink("SpriteRendererInfo", SpriteRendererInfoValue);

	SetSprite("NSet.png");
}

void GameEngineSpriteRenderer::Update(float _Delta)
{
	if (CurFrameAnimations)
	{
		CurSprite = CurFrameAnimations->Update(_Delta);
	}

	if (IsImageSize)
	{
		float4 Scale = float4(CurSprite.GetScale());
		Scale.Z = 1.0f;
		Scale.W = 0.0f;
		SetImageScale(Scale * AutoScaleRatio);
	}
}

void GameEngineSpriteRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	float4 ParentScale = Transform.GetLocalScale();
	float4 Scale = ImageTransform.GetLocalScale();

	float4 CalPivot = Pivot;
	CalPivot.X -= 0.5f;
	CalPivot.Y -= 0.5f;

	float4 PivotPos;
	PivotPos.X = Scale.X * CalPivot.X;
	PivotPos.Y = Scale.Y * CalPivot.Y;

	ImageTransform.SetLocalPosition(PivotPos);

	ImageTransform.TransformUpdate();
	ImageTransform.CalculationViewAndProjection(Transform.GetConstTransformDataRef());

	GetShaderResHelper().SetTexture("DiffuseTex", CurSprite.Texture);

	GameEngineRenderer::Render(_Camera, _Delta);
}

void GameEngineSpriteRenderer::SetSprite(std::string_view _Name, unsigned int _Index)
{
	Sprite = GameEngineSprite::Find(_Name);

	if (!Sprite)
	{
		assert(false);
		return;
	}

	CurSprite = Sprite->GetSpriteData(_Index);
	SetImageScale(CurSprite.GetScale() * AutoScaleRatio);
}

void GameEngineSpriteRenderer::CreateAnimation(
	std::string_view _AnimationName,
	std::string_view _SpriteName,
	float _Inter /*= 0.1f*/,
	unsigned int _Start /*= -1*/,
	unsigned int _End /*= -1*/,
	bool _Loop /*= true*/
)
{
	auto Sprite = GameEngineSprite::Find(_SpriteName);
	if (!Sprite)
	{
		assert(false);
		return;
	}

	std::string Name{ _AnimationName };
	if (FrameAnimations.contains(Name))
	{
		assert(false);
		return;
	}

	auto NewAnimation = std::make_shared<GameEngineFrameAnimation>();
	FrameAnimations[Name] = NewAnimation;
	NewAnimation->AnimationName = _AnimationName;
	NewAnimation->SpriteName = _SpriteName;
	NewAnimation->Sprite = Sprite;
	NewAnimation->Loop = _Loop;
	NewAnimation->Parent = this;

	if (_Start != -1)
	{
		NewAnimation->Start = _Start;
	}
	else
	{
		NewAnimation->Start = 0;
	}

	if (_End != -1)
	{
		NewAnimation->End = _End;
	}
	else
	{
		NewAnimation->End = Sprite->GetSpriteCount() - 1;
	}

	for (auto i = NewAnimation->Start; i <= NewAnimation->End; i++)
	{
		NewAnimation->Index.push_back(i);
	}

	NewAnimation->Inter.resize(NewAnimation->Index.size());
	for (int i = 0; i < NewAnimation->Index.size(); ++i)
	{
		NewAnimation->Inter[i] = _Inter;
	}

	NewAnimation->CurIndex = 0;
}

void GameEngineSpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force, unsigned int _FrameIndex)
{
	std::string Name{ _AnimationName };

	auto FindIter = FrameAnimations.find(Name);
	if (FindIter == FrameAnimations.end())
	{
		assert(false);
		return;
	}

	if (!_Force && FindIter->second == CurFrameAnimations)
	{
		return;
	}

	CurFrameAnimations = FrameAnimations[Name];
	CurFrameAnimations->Reset();
	CurFrameAnimations->CurIndex = _FrameIndex;
	CurSprite = CurFrameAnimations->Sprite->GetSpriteData(CurFrameAnimations->CurIndex);
}

void GameEngineSpriteRenderer::AutoSpriteSizeOn()
{
	IsImageSize = true;
}

void GameEngineSpriteRenderer::AutoSpriteSizeOff()
{
	IsImageSize = false;
}

void GameEngineSpriteRenderer::AnimationPauseSwitch()
{
	IsPause = !IsPause;
}

void GameEngineSpriteRenderer::AnimationPauseOn()
{
	IsPause = true;
}

void GameEngineSpriteRenderer::AnimationPauseOff()
{
	IsPause = false;
}

void GameEngineSpriteRenderer::SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function)
{
	std::string Name{ _AnimationName };

	auto FindIter = FrameAnimations.find(Name);
	auto Animation = FindIter->second;

	assert(Animation);

	Animation->FrameEventFunction[0] = _Function;
}

void GameEngineSpriteRenderer::SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function)
{
	std::string Name{ _AnimationName };

	auto FindIter = FrameAnimations.find(Name);
	auto Animation = FindIter->second;

	assert(Animation);

	Animation->EndEvent = _Function;
}

void GameEngineSpriteRenderer::SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function)
{
	std::string Name{ _AnimationName };

	auto FindIter = FrameAnimations.find(Name);
	auto Animation = FindIter->second;

	assert(Animation);

	Animation->FrameEventFunction[_Frame] = _Function;
}

void GameEngineSpriteRenderer::SetPivotType(PivotType _Type)
{
	switch (_Type)
	{
	case PivotType::Center:
		Pivot = { 0.5f, 0.5f };
		break;
	case PivotType::Top:
		Pivot = { 0.5f, 0.0f };
		break;
	case PivotType::Bottom:
		Pivot = { 0.5f, 1.0f };
		break;
	case PivotType::Left:
		Pivot = { 1.0f, 0.5f };
		break;
	case PivotType::LeftTop:
		Pivot = { 1.0f, 0.0f };
		break;
	}
}

void GameEngineSpriteRenderer::SetImageScale(const float4& _Scale)
{
	ImageTransform.SetLocalScale(_Scale);
}

void GameEngineSpriteRenderer::AddImageScale(const float4& _Scale)
{
	ImageTransform.AddLocalScale(_Scale);
}

float4 GameEngineSpriteRenderer::GetImageScale() const
{
	return ImageTransform.GetLocalScale();
}
