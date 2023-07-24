#include "PreCompile.h"
#include "GameEngineMath.h"

#include <algorithm>

const float4 float4::Left = { -1.0f, 0.0f };
const float4 float4::Right = { 1.0f, 0.0f };
const float4 float4::Up = { 0.0f, -1.0f };
const float4 float4::Down = { 0.0f, 1.0f };

const float GameEngineMath::PI = 3.1415926f;
const float GameEngineMath::PI2 = PI * 2.0f;
const float GameEngineMath::D2R = GameEngineMath::PI / 180.0f;
const float GameEngineMath::R2D = 180.0f / GameEngineMath::PI;

void float4x4::Identity()
{
	std::fill_n(Arr1D, 16, 0.0f);
	//memset(&Arr1D, 0, sizeof(Arr1D));

	for (int i = 0; i < 4; ++i)
	{
		Arr2D[i][i] = 1.0f;
	}
}

float4x4 float4x4::operator*(const float4x4& _Ref)
{
	float4x4 Result{};

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				Result.Arr2D[i][j] += Arr2D[i][k] * _Ref.Arr2D[k][j];
			}
		}
	}

	return Result;
}

float4x4::float4x4()
{
	std::fill_n(Arr1D, 16, 0.0f);
	//memset(&Arr1D, 0, sizeof(Arr1D));
}

float4x4::float4x4(float4x4&& _Rvalue) noexcept
{
	for (int i = 0; i < 16; ++i)
	{
		Arr1D[i] = _Rvalue.Arr1D[i];
	}
	_Rvalue.Identity();
}
