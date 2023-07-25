#include "PreCompile.h"
#include "GameEngineMath.h"

void float4::operator*=(const float4x4& _Ref)
{
	float4 Tmp{ *this };

	for (int i = 0; i < 4; ++i)
	{
		Arr1D[i] = 0;
		for (int j = 0; j < 4; ++j)
		{
			Arr1D[i] += Tmp.Arr1D[j] * _Ref.Arr2D[j][i];
		}
	}
}