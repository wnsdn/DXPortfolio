#include "PreCompile.h"
#include "GameEngineMaterial.h"

#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRasterizer.h"
#include "GameEngineBlend.h"

GameEngineMaterial::GameEngineMaterial()
{
	RasterizerPtr = GameEngineRasterizer::Find("Rasterizer");
	BlendStatePtr = GameEngineBlend::Find("AlphaBlend");
}

GameEngineMaterial::~GameEngineMaterial()
{
}

void GameEngineMaterial::VertexShader()
{
	if (!VertexShaderPtr)
	{
		assert(false);
		return;
	}

	VertexShaderPtr->Setting();
}

void GameEngineMaterial::Rasterizer()
{
	if (!RasterizerPtr)
	{
		assert(false);
		return;
	}

	RasterizerPtr->Setting();
}

void GameEngineMaterial::PixelShader()
{
	if (!PixelShaderPtr)
	{
		assert(false);
		return;
	}

	PixelShaderPtr->Setting();
}

void GameEngineMaterial::Blend()
{
	if (!BlendStatePtr)
	{
		assert(false);
		return;
	}

	BlendStatePtr->Setting();
}

void GameEngineMaterial::SetVertexShader(std::string_view _Value)
{
	VertexShaderPtr = GameEngineVertexShader::Find(_Value);

	if (!VertexShaderPtr)
	{
		assert(false);
		return;
	}
}

void GameEngineMaterial::SetRasterizer(std::string_view _Value)
{
	RasterizerPtr = GameEngineRasterizer::Find(_Value);

	if (!RasterizerPtr)
	{
		assert(false);
		return;
	}
}

void GameEngineMaterial::SetPixelShader(std::string_view _Value)
{
	PixelShaderPtr = GameEnginePixelShader::Find(_Value);

	if (!PixelShaderPtr)
	{
		assert(false);
		return;
	}
}

void GameEngineMaterial::SetBlendState(std::string_view _Value)
{
	BlendStatePtr = GameEngineBlend::Find(_Value);

	if (!BlendStatePtr)
	{
		assert(false);
		return;
	}
}
