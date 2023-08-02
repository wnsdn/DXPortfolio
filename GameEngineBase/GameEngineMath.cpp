#include "PreCompile.h"
#include "GameEngineMath.h"

const float GameEngineMath::PI = 3.14159265359f;
const float GameEngineMath::D2R = PI / 180.0f;
const float GameEngineMath::R2D = 180.0f / PI;

const float4 float4::Left{-1.0f};
const float4 float4::Right{1.0f};
const float4 float4::Up{0.0f, 1.0f};
const float4 float4::Down{0.0f, -1.0f};
const float4 float4::Front{0.0f, 0.0f, 1.0f};
const float4 float4::Back{0.0f, 0.0f, -1.0f};

float4 float4::operator*(const float4x4& _Mat) const
{
	float4 Result{};

	for (int i = 0; i < GameEngineMath::Size; ++i)
	{
		Result.Arr1D[i] = *this * _Mat.GetColVec(i);
	}

	return Result;
}

float4 float4::operator*=(const float4x4& _Mat)
{
	float4 Result{ *this };

	for (int i = 0; i < GameEngineMath::Size; ++i)
	{
		Arr1D[i] = Result * _Mat.GetColVec(i);
	}

	return Result;
}

/*const float GameEngineMath::PI = 3.1415926f;
const float GameEngineMath::PI2 = PI * 2.0f;
const float GameEngineMath::D2R = GameEngineMath::PI / 180.0f;
const float GameEngineMath::R2D = 180.0f / GameEngineMath::PI;*/
