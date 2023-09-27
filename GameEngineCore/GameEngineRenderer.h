#pragma once
#include "GameEngineComponent.h"
#include "GameEngineMesh.h"
#include "GameEngineMaterial.h"
#include "GameEngineRenderUnit.h"

class GameEngineCamera;
class GameEngineInputLayout;
class GameEngineRenderer : public GameEngineComponent
{
	friend class GameEngineCamera;
public:
	GameEngineRenderer() = default;
	~GameEngineRenderer() = default;
	GameEngineRenderer(const GameEngineRenderer&) = delete;
	GameEngineRenderer(GameEngineRenderer&&) noexcept = delete;
	void operator=(const GameEngineRenderer&) = delete;
	void operator=(GameEngineRenderer&&) noexcept = delete;

	void SetViewCameraSelect(int _Order);

	void SetRenderOrder(int _Order);
	template <typename EnumType>
	void SetRenderOrder(EnumType _Order)
	{
		SetRenderOrder(static_cast<int>(_Order));
	}

	void SetCameraOrder(int _Order);
	void SetCameraOrder(ECAMERAORDER _Order)
	{
		SetCameraOrder(static_cast<int>(_Order));
	}

	std::shared_ptr<GameEngineRenderUnit> CreateAndFindRenderUnit(int _Index = 0);
	void SetMesh(std::string_view _Name, int _Index = 0);
	void SetMaterial(std::string_view _Name, int _Index = 0);
	GameEngineShaderResHelper& GetShaderResHelper(int _Index = 0);
protected:
	void Start();
	virtual void Render(GameEngineCamera* _Camera, float _Delta);

	std::vector<std::shared_ptr<GameEngineRenderUnit>> Units;
private:
	GameEngineCamera* Camera = nullptr;
};