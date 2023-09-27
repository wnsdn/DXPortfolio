#pragma once
#include "GameEngineShaderResHelper.h"
#include "GameEngineObject.h"

class GameEngineRenderUnit final : public GameEngineObjectBase, std::enable_shared_from_this<GameEngineRenderUnit>
{
public:
	GameEngineRenderUnit();
	~GameEngineRenderUnit();

	void SetMesh(std::string_view _Name);
	void SetMaterial(std::string_view _Name);
	void ResSetting();
	void Draw();

	void SetParentRenderer(class GameEngineRenderer* _Renderer)
	{
		ParentRenderer = _Renderer;
	}

	GameEngineShaderResHelper ShaderResHelper;
private:
	class GameEngineRenderer* ParentRenderer = nullptr;

	std::shared_ptr<class GameEngineInputLayout> Layout = nullptr;
	std::shared_ptr<class GameEngineMesh> Mesh = nullptr;
	std::shared_ptr<class GameEngineMaterial> Material = nullptr;
};
