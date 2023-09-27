#pragma once
#include "GameEngineResources.h"

class GameEngineMaterial : public GameEngineResources<GameEngineMaterial>
{
public:
	GameEngineMaterial();
	~GameEngineMaterial();
	GameEngineMaterial(const GameEngineMaterial&) = delete;
	GameEngineMaterial(GameEngineMaterial&&) noexcept = delete;
	void operator=(const GameEngineMaterial&) = delete;
	void operator=(GameEngineMaterial&&) noexcept = delete;

	static std::shared_ptr<class GameEngineMaterial> Create(std::string_view _Name)
	{
		auto NewRes = CreateRes(_Name);
		return NewRes;
	}

	void VertexShader();
	void Rasterizer();
	void PixelShader();
	void Blend();

	void SetVertexShader(std::string_view _Value);
	void SetRasterizer(std::string_view _Value);
	void SetPixelShader(std::string_view _Value);
	void SetBlendState(std::string_view _Value);

	std::shared_ptr<class GameEngineVertexShader> GetVertexShader() const
	{
		return VertexShaderPtr;
	}
	std::shared_ptr<class GameEnginePixelShader> GetPixelShader() const
	{
		return PixelShaderPtr;
	}
private:
	std::shared_ptr<class GameEngineVertexShader> VertexShaderPtr;
	std::shared_ptr<class GameEngineRasterizer> RasterizerPtr;
	std::shared_ptr<class GameEnginePixelShader> PixelShaderPtr;
	std::shared_ptr<class GameEngineBlend> BlendStatePtr;
};
