#include "PreCompile.h"
#include "GameEngineMath.h"

const int4 int4::Left = { -1, 0 };
const int4 int4::Right = { 1, 0 };
const int4 int4::Up = { 0, -1 };
const int4 int4::Down = { 0, 1 };

const float4 float4::Left = { -1.0f, 0.0f };
const float4 float4::Right = { 1.0f, 0.0f };
const float4 float4::Up = { 0.0f, -1.0f };
const float4 float4::Down = { 0.0f, 1.0f };

int4 float4::ToInt4() const
{
	return { static_cast<int>(X), static_cast<int>(Y) };
}

float4 int4::ToFloat4() const
{
	return { static_cast<float>(X), static_cast<float>(Y) };
}
