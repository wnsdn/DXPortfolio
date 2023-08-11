#pragma once
#include "GameEngineActor.h"

enum class EPROJECTIONTYPE
{
	Perspective,
	Orthographic,
};

class GameEngineRenderer;
class GameEngineCamera : public GameEngineActor
{
	friend class GameEngineRenderer;
private:
	EPROJECTIONTYPE ProjectionType = EPROJECTIONTYPE::Orthographic;
	const float Far = 1000.0f;
	const float Near = 0.1f;
	const float FOV = 60.0f;

	int CameraOrder = 0;
	std::map<int, std::list<std::shared_ptr<GameEngineRenderer>>> Renderers;
public:
	void Start() override;
	void Update(float _Delta);
	void Render(float _Delta);

	void SetCameraOrder(int _Order);
	void SetProjectionType(EPROJECTIONTYPE _ProjectionType)
	{
		ProjectionType = _ProjectionType;
	}

#pragma region Constructor
	GameEngineCamera() {}
	~GameEngineCamera() {}
	GameEngineCamera(const GameEngineCamera& _Other) = delete;
	GameEngineCamera(GameEngineCamera&& _Other) noexcept = delete;
	GameEngineCamera& operator=(const GameEngineCamera& _Other) = delete;
	GameEngineCamera& operator=(GameEngineCamera&& _Other) noexcept = delete;
#pragma endregion
};