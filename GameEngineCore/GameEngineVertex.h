#pragma once
#include <GameEngineBase/GameEngineMath.h>
#include "GameEngineInputLayout.h"

struct GameEngineVertex2D
{
	static GameEngineInputLayoutInfo VertexInfo;

	float4 POSITION;
	float4 TEXCOORD;
};

struct GameEngine3DRain
{
	static GameEngineInputLayoutInfo VertexInfo;

	float4 pos;
	float4 seed;
	float4 speed;
	float  random;
	unsigned int Type;
};

struct GameEngineVertex3D
{
	static GameEngineInputLayoutInfo VertexInfo;

	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
	float4 NORMAL;
	float4 BINORMAL;
	float4 TANGENT;
	float4 WEIGHT;
	int BLENDINDICES[4];
};