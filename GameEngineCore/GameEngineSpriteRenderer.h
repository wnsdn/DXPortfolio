#pragma once
#include "GameEngineRenderer.h"
#include "GameEngineSprite.h"

class GameEngineFrameAnimation
{
	friend class GameEngineSpriteRenderer;

	GameEngineSpriteRenderer* Parent = nullptr;

	std::string AnimationName;
	std::string SpriteName;

	std::shared_ptr<GameEngineSprite> Sprite = nullptr;

	bool Loop;
	bool IsEnd;

	bool EventCheck = false;

	unsigned int Start;
	unsigned int End;
	unsigned int CurIndex;
	float CurTime = 0.0f;
	std::vector<int> Index;

	void Reset();

	std::map<int, std::function<void(GameEngineSpriteRenderer*)>> FrameEventFunction;

	std::function<void(GameEngineSpriteRenderer*)> EndEvent;

	SpriteData Update(float _Delta);

	void EventCall(int _Frame);
public:
	std::vector<float> Inter;
};

enum class PivotType
{
	Center,
	Top,
	Bottom,
	Left,
	LeftTop,
};

struct SpriteRendererInfo
{
	int FlipLeft = 0;
	int FlipUp = 0;
	float Temp1;
	float Temp2;
};

class GameEngineSampler;
class GameEngineSpriteRenderer : public GameEngineRenderer
{
	friend GameEngineFrameAnimation;
public:
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer&) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&&) noexcept = delete;
	void operator=(const GameEngineSpriteRenderer&) = delete;
	void operator=(GameEngineSpriteRenderer&&) noexcept = delete;

	void SetSprite(std::string_view _Name, unsigned int _Index = 0);

	void CreateAnimation(std::string_view _AnimationName, std::string_view _SpriteName, float _Inter = 0.1f, unsigned int _Start = -1, unsigned int _End = -1, bool _Loop = true);
	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false, unsigned int _FrameIndex = 0);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	void SetAutoScaleRatio(float _Ratio)
	{
		AutoScaleRatio.X = _Ratio;
		AutoScaleRatio.Y = _Ratio;
	}
	void SetAutoScaleRatio(const float4& _Ratio)
	{
		AutoScaleRatio = _Ratio;
	}

	bool IsRight() const
	{
		return AutoScaleRatio.X > 0;
	}
	void RightFlip()
	{
		SpriteRendererInfoValue.FlipLeft = 0;
	}
	void LeftFlip()
	{
		SpriteRendererInfoValue.FlipLeft = 1;
	}
	void UpFlip()
	{
		SpriteRendererInfoValue.FlipUp = 1;
	}
	void DownFlip()
	{
		SpriteRendererInfoValue.FlipUp = 0;
	}

	bool IsCurAnimationEnd() const
	{
		return CurFrameAnimations->IsEnd;
	}
	bool IsCurSprite(std::string_view _SpriteName)
	{
		return Sprite == GameEngineSprite::Find(_SpriteName);
	}
	bool IsCurAnimation(std::string_view _AnimationName)
	{
		return CurFrameAnimations->AnimationName == _AnimationName;
	}
	unsigned int GetCurIndex() const
	{
		return CurFrameAnimations->CurIndex;
	}

	std::shared_ptr<GameEngineFrameAnimation> FindAnimation(std::string_view _AnimationName)
	{
		std::string Name{ _AnimationName };
		if (!FrameAnimations.contains(Name))
		{
			return nullptr;
		}

		return FrameAnimations[Name];
	}

	void AnimationPauseSwitch();
	void AnimationPauseOn();
	void AnimationPauseOff();

	void SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function);

	void SetPivotType(PivotType _Type);
	void SetPivotValue(const float4& _Value)
	{
		Pivot = _Value;
	}
	void SetImageScale(const float4& _Scale);
	void AddImageScale(const float4& _Scale);
	float4 GetImageScale() const;

	std::shared_ptr<GameEngineSprite> GetSprite() const
	{
		return Sprite;
	}
	const SpriteData& GetCurSprite()
	{
		return CurSprite;
	}

	GameEngineTransform& GetImageTransform()
	{
		return ImageTransform;
	}

	void SetAlpha(float _Value)
	{
		if (Alpha.A == _Value)
		{
			return;
		}

		if (_Value > 1.0f)
		{
			_Value = 1.0f;
		}
		else if (_Value < 0.0f)
		{
			_Value = 0.0f;
		}
		Alpha.A = _Value;
	}
	void AddAlpha(float _Value)
	{
		Alpha.A += _Value;

		if (Alpha.A > 1.0f)
		{
			Alpha.A = 1.0f;
		}
		else if (Alpha.A < 0.0f)
		{
			Alpha.A = 0.0f;
		}
	}
	float GetAlpha() const
	{
		return Alpha.A;
	}
protected:
	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;

	int Index = 0;
private:
	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>> FrameAnimations;
	std::shared_ptr<GameEngineFrameAnimation> CurFrameAnimations;

	std::shared_ptr<GameEngineSampler> Sampler;

	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;
	SpriteRendererInfo SpriteRendererInfoValue;

	bool IsImageSize = false;
	float4 AutoScaleRatio{ 1.0f, 1.0f, 1.0f };
	bool IsPause = false;

	float4 Pivot{ 0.5f, 0.5f };
	float4 Alpha{ 0.0f, 0.0f, 0.0f, 1.0f };
	GameEngineTransform ImageTransform;
};

