#include "PreCompile.h"
#include "GameEngineMath.h"

const float4 float4::One		{1.0f, 1.0f, 1.0f, 1.0f};
const float4 float4::OneNull	{1.0f, 1.0f, 1.0f, 0.0f};
const float4 float4::Zero		{0.0f, 0.0f, 0.0f, 1.0f};
const float4 float4::ZeroNull	{0.0f, 0.0f, 0.0f, 0.0f};

const float4 float4::Left	{-1.0f, 0.0f, 0.0f, 1.0f};
const float4 float4::Right	{1.0f, 0.0f, 0.0f, 1.0f};
const float4 float4::Up		{0.0f, 1.0f, 0.0f, 1.0f};
const float4 float4::Down	{0.0f, -1.0f, 0.0f, 1.0f};
const float4 float4::Front	{0.0f, 0.0f, 1.0f, 1.0f};
const float4 float4::Back	{0.0f, 0.0f, -1.0f, 1.0f};

float4 float4::operator*(const float4x4& _Matrix) const
{
	float4 Result = DirectX::XMVector3Transform(Vector, _Matrix.Matrix);
	return Result;
}

void float4::operator*=(const float4x4& _Matrix)
{
	*this = DirectX::XMVector3Transform(Vector, _Matrix.Matrix);
}
