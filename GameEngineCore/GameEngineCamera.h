#pragma once
#include "GameEngineActor.h"

class GameEngineRenderer;
class GameEngineCamera : public GameEngineActor
{
	friend class GameEngineRenderer;
private:
	int CameraOrder = 0;
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> Renderers;
public:
	void Start() override;
	void Update(float _Delta);
	void Render(float _Delta);

	void SetCameraOrder(int _Order);

	GameEngineCamera() {}
	~GameEngineCamera() {}
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;
};