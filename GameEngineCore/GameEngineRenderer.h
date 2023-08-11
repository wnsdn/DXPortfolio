#pragma once
#include "GameEngineComponent.h"

class GameEngineCamera;
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;
private:
	std::map<GameEngineCamera*, int> ViewInfo;
protected:
	void Start();
	void Render(float _Delta);
public:
	void SetViewCameraSelect(int _Order);

#pragma region Constructor
	GameEngineRenderer() {}
	~GameEngineRenderer() {}
	GameEngineRenderer(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer(GameEngineRenderer&& _Other) noexcept = delete;
	GameEngineRenderer& operator=(const GameEngineRenderer& _Other) = delete;
	GameEngineRenderer& operator=(GameEngineRenderer&& _Other) noexcept = delete;
#pragma endregion
};