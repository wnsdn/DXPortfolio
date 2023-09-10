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

	float Inter;
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
};

enum class SamplerOption
{
	LINEAR,
	POINT,
};

enum class PivotType
{
	Center,
	Bottom,
	Left,
};

class GameEngineSampler;
class GameEngineSpriteRenderer : public GameEngineRenderer
{
	friend GameEngineFrameAnimation;
private:
	std::map<std::string, std::shared_ptr<GameEngineFrameAnimation>> FrameAnimations;
	std::shared_ptr<GameEngineFrameAnimation> CurFrameAnimations;

	static std::shared_ptr<GameEngineSampler> DefaultSampler;
	std::shared_ptr<GameEngineSampler> Sampler;

	std::shared_ptr<GameEngineSprite> Sprite;
	SpriteData CurSprite;

	bool IsImageSize = false;
	float4 AutoScaleRatio{ 1.0f, 1.0f, 1.0f };
	bool IsPause = false;

	float4 Pivot{ 0.5f, 0.5f };
	GameEngineTransform ImageTransform;
protected:
	int Index = 0;

	void Start() override;
	void Update(float _Delta) override;
	void Render(GameEngineCamera* _Camera, float _Delta) override;
public:
	GameEngineSpriteRenderer();
	~GameEngineSpriteRenderer();
	GameEngineSpriteRenderer(const GameEngineSpriteRenderer&) = delete;
	GameEngineSpriteRenderer(GameEngineSpriteRenderer&&) noexcept = delete;
	void operator=(const GameEngineSpriteRenderer&) = delete;
	void operator=(GameEngineSpriteRenderer&&) noexcept = delete;

	void SetSprite(std::string_view _Name, unsigned int _Index = 0);

	void CreateAnimation(
		std::string_view _AnimationName,
		std::string_view _SpriteName,
		float _Inter = 0.1f,
		unsigned int _Start = -1,
		unsigned int _End = -1,
		bool _Loop = true);

	void ChangeAnimation(std::string_view _AnimationName, bool _Force = false, unsigned int _FrameIndex = 0);

	void AutoSpriteSizeOn();
	void AutoSpriteSizeOff();

	void SetAutoScaleRatio(const float4& _Ratio)
	{
		AutoScaleRatio = _Ratio;
	}
	void SetSamplerState(SamplerOption _Option);

	bool IsCurAnimationEnd() const
	{
		return CurFrameAnimations->IsEnd;
	}
	bool IsCurAnimation(std::string_view _AnimationName)
	{
		return CurFrameAnimations->AnimationName == _AnimationName;
	}
	unsigned int GetCurIndex() const
	{
		return CurFrameAnimations->CurIndex;
	}

	void AnimationPauseSwitch();
	void AnimationPauseOn();
	void AnimationPauseOff();

	void SetStartEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetEndEvent(std::string_view _AnimationName, std::function<void(GameEngineSpriteRenderer*)> _Function);
	void SetFrameEvent(std::string_view _AnimationName, int _Frame, std::function<void(GameEngineSpriteRenderer*)> _Function);

	void SetPivotType(PivotType _Type);
	void SetImageScale(const float4& _Scale);
	void AddImageScale(const float4& _Scale);
	float4 GetImageScale() const;

	static void SetDefaultSampler(std::string_view _SamplerName);

	std::shared_ptr<GameEngineSprite> GetSprite() const
	{
		return Sprite;
	}
	const SpriteData& GetCurSprite()
	{
		return CurSprite;
	}
};

