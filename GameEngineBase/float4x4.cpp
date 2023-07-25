#include "PreCompile.h"
#include "GameEngineMath.h"

void float4x4::Reset()
{
	std::fill_n(Arr1D, 16, 0.0f);
}

void float4x4::Identity()
{
	Reset();

	for (int i = 0; i < 4; ++i)
	{
		Arr2D[i][i] = 1.0f;
	}
}

float4x4 float4x4::operator*(const float4x4& _Ref)
{
	float4x4 Result{};
	Result.Reset();

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
	Identity();
}

float4x4::float4x4(float4x4&& _Rvalue) noexcept
{
	for (int i = 0; i < 16; ++i)
	{
		Arr1D[i] = _Rvalue.Arr1D[i];
	}
	_Rvalue.Identity();
}

void float4x4::operator=(float4x4&& _Rvalue) noexcept
{
	for (int i = 0; i < 16; ++i)
	{
		Arr1D[i] = _Rvalue.Arr1D[i];
	}
	_Rvalue.Identity();
}
