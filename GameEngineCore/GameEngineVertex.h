#pragma once
#include <GameEngineBase/GameEngineMath.h>

struct GameEngineVertex2D
{
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
};

struct GameEngineVertex3D
{
	float4 POSITION;
	float4 TEXCOORD;
	float4 COLOR;
	float4 NORMAL;
	float4 BINORMAL;
	float4 TANGENT;
	float4 WEIGHT;
	int BLENDINDICES[4];
};