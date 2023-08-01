#include "PreCompile.h"
#include "float4.h"

#include "GameEngineMath.h"
#include "float4x4.h"

const float4 float4::Left{ -1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Right{ 1.0f, 0.0f, 0.0f, 1.0f };
const float4 float4::Up{ 0.0f, 1.0f, 0.0f, 1.0f };
const float4 float4::Down{ 0.0f, -1.0f, 0.0f, 1.0f };
const float4 float4::Front{ 0.0f, 0.0f, 1.0f, 1.0f };
const float4 float4::Back{ 0.0f, 0.0f, -1.0f, 1.0f };

void float4::RotateX(float _Angle)
{
	float Radian = _Angle * GameEngineMath::D2R;
	float4 Tmp{ *this };

	Z = Tmp.Z * cosf(Radian) - Tmp.Y * sinf(Radian);
	Y = Tmp.Z * sinf(Radian) + Tmp.Y * cosf(Radian);
}

void float4::RotateY(float _Angle)
{
	float Radian = _Angle * GameEngineMath::D2R;
	float4 Tmp{ *this };

	X = Tmp.X * cosf(Radian) - Tmp.Z * sinf(Radian);
	Z = Tmp.X * sinf(Radian) + Tmp.Z * cosf(Radian);
}

void float4::RotateZ(float _Angle)
{
	float Radian = _Angle * GameEngineMath::D2R;
	float4 Tmp{ *this };

	X = Tmp.X * cosf(Radian) - Tmp.Y * sinf(Radian);
	Y = -(Tmp.X * sinf(Radian) + Tmp.Y * cosf(Radian));
}

float4 float4::RotateXReturn(float _Angle) const
{
	float Radian = _Angle * GameEngineMath::D2R;
	float4 Tmp{ *this };

	Tmp.Z = Z * cosf(Radian) - Y * sinf(Radian);
	Tmp.Y = Z * sinf(Radian) + Y * cosf(Radian);

	return Tmp;
}

float4 float4::RotateYReturn(float _Angle) const
{
	float Radian = _Angle * GameEngineMath::D2R;
	float4 Tmp{ *this };

	Tmp.X = X * cosf(Radian) - Z * sinf(Radian);
	Tmp.Z = X * sinf(Radian) + Z * cosf(Radian);

	return Tmp;
}

float4 float4::RotateZReturn(float _Angle) const
{
	float Radian = _Angle * GameEngineMath::D2R;
	float4 Tmp{ *this };

	Tmp.X = X * cosf(Radian) - Y * sinf(Radian);
	Tmp.Y = -(X * sinf(Radian) + Y * cosf(Radian));

	return Tmp;
}

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