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
protected:
	void Start();
	virtual void Render(GameEngineCamera* _Camera, float _Delta);
public:
	void SetViewCameraSelect(int _Order);

	GameEngineRenderer() = default;
	~GameEngineRenderer() = default;
	GameEngineRenderer(const GameEngineRenderer&) = delete;
	GameEngineRenderer(GameEngineRenderer&&) noexcept = delete;
	void operator=(const GameEngineRenderer&) = delete;
	void operator=(GameEngineRenderer&&) noexcept = delete;
};