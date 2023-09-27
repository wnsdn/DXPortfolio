#pragma once
#include "GameEngineActor.h"
#include "EngineEnum.h"

class GameEngineRenderer;
class GameEngineCamera : public GameEngineActor
{
	friend class GameEngineRenderer;
	friend class GameEngineLevel;
public:
	GameEngineCamera() {}
	~GameEngineCamera() {}
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;

	void SetCameraOrder(int _Order);
	void SetProjectionType(EPROJECTIONTYPE _ProjectionType)
	{
		ProjectionType = _ProjectionType;
	}

	float4 GetWorldMousePos2D();

	void SetZoomValue(float _Value)
	{
		ZoomValue = _Value;
	}
	void AddZoomValue(float _Value)
	{
		ZoomValue += _Value;
	}
protected:
	void Start() override;
	void Update(float _Delta);
	void Render(float _Delta);
	void AllReleaseCheck() override;
private:
	EPROJECTIONTYPE ProjectionType = EPROJECTIONTYPE::Orthographic;
	const float Far = 1000.0f;
	const float Near = 0.1f;
	const float FOV = 60.0f;
	float ZoomValue = 0.0f;

	int CameraOrder = 0;
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> Renderers;
};