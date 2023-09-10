#include "PreCompile.h"
#include "GameEngineSpriteRenderer.h"

#include "GameEngineTexture.h"
#include "GameEngineSampler.h"
#include "GameEngineConstantBuffer.h"

std::shared_ptr<GameEngineSampler> GameEngineSpriteRenderer::DefaultSampler;

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

	if (CurTime >= Inter)
	{
		++CurIndex;
		EventCheck = true;
		CurTime -= Inter;

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
	if (!DefaultSampler)
	{
		assert(false);
	}

	Sampler = DefaultSampler;
}

GameEngineSpriteRenderer::~GameEngineSpriteRenderer()
{
}

void GameEngineSpriteRenderer::Start()
{
	GameEngineRenderer::Start();

	DataTransform = &ImageTransform;
	ImageTransform.SetParent(Transform);
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

	GameEngineRenderer::ResSetting();

	auto Buffer = GameEngineConstantBuffer::CreateAndFind(sizeof(float4), "SpriteData", ShaderType::Vertex);
	Buffer->ChangeData(CurSprite.Pivot);
	Buffer->Setting(1);
	CurSprite.Texture->PSSetting(0);

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
		MsgBoxAssert("존재하지 않는 스프라이트로 애니메이션을 만들려고 했습니다.");
		return;
	}

	std::string Name{ _AnimationName };
	if (FrameAnimations.contains(Name))
	{
		MsgBoxAssert("이미 존재하는 애니메이션을 또 만들려고 했습니다.");
		return;
	}

	auto NewAnimation = std::make_shared<GameEngineFrameAnimation>();
	FrameAnimations[Name] = NewAnimation;
	NewAnimation->AnimationName = _AnimationName;
	NewAnimation->SpriteName = _SpriteName;
	NewAnimation->Sprite = Sprite;
	NewAnimation->Loop = _Loop;
	NewAnimation->Inter = _Inter;
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

	NewAnimation->CurIndex = 0;
}

void GameEngineSpriteRenderer::ChangeAnimation(std::string_view _AnimationName, bool _Force, unsigned int _FrameIndex)
{
	std::string Name{ _AnimationName };

	auto FindIter = FrameAnimations.find(Name);
	if (FindIter == FrameAnimations.end())
	{
		MsgBoxAssert("존재하지 않는 애니메이션으로 체인지하려고 했습니다.");
		return;
	}

	if (!_Force && FindIter->second == CurFrameAnimations)
	{
		return;
	}

	CurFrameAnimations = FrameAnimations[Name];
	CurFrameAnimations->Reset();
	CurFrameAnimations->CurIndex = _FrameIndex;
}

void GameEngineSpriteRenderer::AutoSpriteSizeOn()
{
	IsImageSize = true;
}

void GameEngineSpriteRenderer::AutoSpriteSizeOff()
{
	IsImageSize = false;
}

void GameEngineSpriteRenderer::SetSamplerState(SamplerOption _Option)
{
	switch (_Option)
	{
	case SamplerOption::LINEAR:
		Sampler = GameEngineSampler::Find("LINEAR");
		break;
	case SamplerOption::POINT:
		Sampler = GameEngineSampler::Find("POINT");
		break;
	default:
		break;
	}
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
	case PivotType::Bottom:
		Pivot = { 0.5f, 1.0f };
		break;
	case PivotType::Left:
		Pivot = { 1.0f, 0.5f };
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

void GameEngineSpriteRenderer::SetDefaultSampler(std::string_view _SamplerName)
{
	DefaultSampler = GameEngineSampler::Find(_SamplerName);
}
