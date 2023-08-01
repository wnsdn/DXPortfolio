#include "PreCompile.h"
#include "float4x4.h"

#include "GameEngineMath.h"
#include "float4.h"

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

void float4x4::Scale(const float4& _Value)
{
	Identity();
	Arr2D[0][0] = _Value.X;
	Arr2D[1][1] = _Value.Y;
	Arr2D[2][2] = _Value.Z;
}

void float4x4::Position(const float4& _Value)
{
	Identity();
	Arr2D[3][0] = _Value.X;
	Arr2D[3][1] = _Value.Y;
	Arr2D[3][2] = _Value.Z;
}

void float4x4::RotateX(float _Angle)
{
	Identity();

	float Radian = _Angle * GameEngineMath::D2R;
	float CosValue = cosf(Radian);
	float SinValue = sinf(Radian);
	Arr2D[1][1] = CosValue;
	Arr2D[1][2] = SinValue;
	Arr2D[2][1] = -SinValue;
	Arr2D[2][2] = CosValue;
}

void float4x4::RotateY(float _Angle)
{
	Identity();

	float Radian = _Angle * GameEngineMath::D2R;
	float CosValue = cosf(Radian);
	float SinValue = sinf(Radian);
	Arr2D[0][0] = CosValue;
	Arr2D[0][2] = SinValue;
	Arr2D[2][0] = -SinValue;
	Arr2D[2][2] = CosValue;
}

void float4x4::RotateZ(float _Angle)
{
	Identity();

	float Radian = _Angle * GameEngineMath::D2R;
	float CosValue = cosf(Radian);
	float SinValue = sinf(Radian);
	Arr2D[0][0] = CosValue;
	Arr2D[0][1] = SinValue;
	Arr2D[1][0] = -SinValue;
	Arr2D[1][1] = CosValue;
	//시계방향?
}

float4x4 float4x4::RotateXReturn(float _Angle)
{
	float4x4 Tmp{ *this };
	Tmp.Identity();

	float Radian = _Angle * GameEngineMath::D2R;
	float CosValue = cosf(Radian);
	float SinValue = sinf(Radian);
	Tmp.Arr2D[1][1] = CosValue;
	Tmp.Arr2D[1][2] = SinValue;
	Tmp.Arr2D[2][1] = -SinValue;
	Tmp.Arr2D[2][2] = CosValue;

	return Tmp;
}

float4x4 float4x4::RotateYReturn(float _Angle)
{
	float4x4 Tmp{ *this };
	Tmp.Identity();

	float Radian = _Angle * GameEngineMath::D2R;
	float CosValue = cosf(Radian);
	float SinValue = sinf(Radian);
	Arr2D[0][0] = CosValue;
	Arr2D[0][2] = SinValue;
	Arr2D[2][0] = -SinValue;
	Arr2D[2][2] = CosValue;

	return Tmp;
}

float4x4 float4x4::RotateZReturn(float _Angle)
{
	float4x4 Tmp{ *this };
	Tmp.Identity();

	float Radian = _Angle * GameEngineMath::D2R;
	float CosValue = cosf(Radian);
	float SinValue = sinf(Radian);
	Arr2D[0][0] = CosValue;
	Arr2D[0][1] = SinValue;
	Arr2D[1][0] = -SinValue;
	Arr2D[1][1] = CosValue;
	//시계방향?

	return Tmp;
}

void float4x4::InsertVector(int _Idx, int _size, const float4& _Ref)
{
	for (int i = 0; i < _size; ++i)
	{
		Arr2D[_Idx][i] = _Ref.Arr1D[i];
	}
}

void float4x4::Transpose()
{
	float4x4 Tmp = *this;

	for (int y = 0; y < 4; ++y)
	{
		for (int x = 0; x < 4; ++x)
		{
			Arr2D[x][y] = Tmp.Arr2D[y][x];
		}
	}
}

void float4x4::LookAtLH(const float4& _EyePos, const float4& _EyeFront, const float4& _EyeUp)
{
	Identity();

	float4 EyePos{ _EyePos };
	float4 EyeFront{ _EyeFront };
	float4 EyeUp{ _EyeUp };

	EyeFront.Normalize();
	EyeUp.Normalize();
	float4 EyeRight{ float4::Cross3D(-EyeFront, EyeUp) };

	InsertVector(0, 4, EyeRight);
	InsertVector(1, 4, EyeUp);
	InsertVector(2, 4, EyeFront);

	Transpose();

	float4 NegEyePos{ -EyePos };
	InsertVector(3, 3,
		{
			float4::Dot3D(EyeRight, NegEyePos),
			float4::Dot3D(EyeUp, NegEyePos),
			float4::Dot3D(EyeFront, NegEyePos)
		});
}

void float4x4::OrthographicLH(float _Width, float _Height, float _Far, float _Near)
{
	Identity();
	Arr2D[0][0] = 2.0f / _Width;
	Arr2D[1][1] = 2.0f / _Height;

	//-1 ~ 1 사이 값으로 바꿔줌?
	Arr2D[2][2] = 1.0f / (_Far - _Near);
	Arr2D[3][2] = -(1.0f / (_Far - _Near)) * _Near;
}

void float4x4::PerspectiveFovLH(float _FovAngle, float _Width, float _Height,
	float _Far, float _Near)
{
	Identity();
	float AspectRatio{ _Width / _Height };
	float YFOV{ _FovAngle * GameEngineMath::D2R };

	Arr2D[2][3] = 1.0f;
	Arr2D[3][3] = 0.0f;

	Arr2D[0][0] = 1.0f / (tanf(YFOV / 2.0f) * AspectRatio);
	Arr2D[1][1] = 1.0f / tanf(YFOV / 2.0f);

	Arr2D[2][2] = _Far / (_Far - _Near);
	Arr2D[3][2] = -(_Near * _Far) / (_Far - _Near);
}

void float4x4::ViewPort(float _Width, float _Height, float _Left, float _Right,
	float _ZMin, float _ZMax)
{
	Identity();
	Arr2D[0][0] = _Width * 0.5f;
	Arr2D[1][1] = -_Height * 0.5f;
	//Arr2D[2][2] = _ZMax != 0.0f ? 1.0f : _ZMin / _ZMax;

	Arr2D[3][0] = Arr2D[0][0] + _Left;
	Arr2D[3][1] = -Arr2D[1][1] + _Right;
	//Arr2D[3][2] = _ZMax != 0.0f ? 0.0f : _ZMin / _ZMax;
	//Arr2D[3][3] = 1.0f;
}

void float4x4::operator*=(const float4x4& _Ref)
{
	float4x4 Tmp{ *this };
	Reset();

	for (int i = 0; i < 4; ++i)
	{
		for (int j = 0; j < 4; ++j)
		{
			for (int k = 0; k < 4; ++k)
			{
				Arr2D[i][j] += Tmp.Arr2D[i][k] * _Ref.Arr2D[k][j];
			}
		}
	}
}

float4x4 float4x4::operator*(const float4x4& _Ref) const
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

float4x4::float4x4(const float4x4& _Ref)
{
	for (int i = 0; i < 16; ++i)
	{
		Arr1D[i] = _Ref.Arr1D[i];
	}
}

float4x4::float4x4(float4x4&& _Rvalue) noexcept
{
	for (int i = 0; i < 16; ++i)
	{
		Arr1D[i] = _Rvalue.Arr1D[i];
	}
}

void float4x4::operator=(float4x4&& _Rvalue) noexcept
{
	for (int i = 0; i < 16; ++i)
	{
		Arr1D[i] = _Rvalue.Arr1D[i];
	}
}
