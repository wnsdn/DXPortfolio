#pragma once
#include "GameEngineComponent.h"

class GameEngineCamera;
class GameEngineInputLayout;
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;
private:
	std::map<GameEngineCamera*, int> ViewInfo;
	std::shared_ptr<GameEngineInputLayout> Layout = nullptr;
	GameEngineCamera* Camera = nullptr;
protected:
	void Start();
	virtual void Render(GameEngineCamera* _Camera, float _Delta);
	void ResSetting();
	void Draw();
public:
	void SetViewCameraSelect(int _Order);

	void SetRenderOrder(int _Order);
	template <typename EnumType>
	void SetRenderOrder(EnumType _Order)
	{
		SetRenderOrder(static_cast<int>(_Order));
	}
	void SetCameraOrder(int _Order);

	GameEngineRenderer() = default;
	~GameEngineRenderer() = default;
	GameEngineRenderer(const GameEngineRenderer&) = delete;
	GameEngineRenderer(GameEngineRenderer&&) noexcept = delete;
	void operator=(const GameEngineRenderer&) = delete;
	void operator=(GameEngineRenderer&&) noexcept = delete;
};