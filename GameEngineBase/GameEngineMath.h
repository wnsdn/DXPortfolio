#pragma once
#include <Windows.h>

struct float4;
struct float4x4;

struct GameEngineMath
{
	static const float PI;
	static const float D2R;
	static const float R2D;

	static const int Size = 4;
};

struct float4//벡터: 행 벡터
{
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Front;
	static const float4 Back;

	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};
		float Arr1D[GameEngineMath::Size];
	};

#pragma region Function
	POINT ToPoint() const
	{
		return { static_cast<int>(X), static_cast<int>(Y) };
	}
	float Size() const
	{
		float Result = 0.0f;

		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Result += powf(Arr1D[i], 2.0f);
		}

		return Result;
	}
	void Normalize()
	{
		*this /= Size();
	}
	static float Dot(const float4& _V1, const float4& _V2)//내적 선생님 코드 확인
	{
		float Result = 0.0f;

		float4 Norm1 = _V1;
		float4 Norm2 = _V2;
		Norm1.Normalize();
		Norm2.Normalize();

		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Result += Norm1.Arr1D[i] * Norm2.Arr1D[i];
		}

		return Result;
	}
	static float4 Cross(const float4& _V1, const float4& _V2)//외적
	{
		float4 Result{};

		Result.X = _V1.Y * _V2.Z - _V1.Z * _V2.Y;
		Result.Y = _V1.Z * _V2.X - _V1.X * _V2.Z;
		Result.Z = _V1.X * _V2.Y - _V1.Y * _V2.X;

		return Result;
	}
	float operator*(const float4& _Vec) const//벡터 x 벡터
	{
		float Result = 0.0f;

		for (int i = 0; i < GameEngineMath::Size; ++i)
		{
			Result += Arr1D[i] * _Vec.Arr1D[i];
		}

		return Result;
	}
	float4 operator*(const float4x4& _Mat) const;//벡터 x 행렬
	float4 operator*=(const float4x4& _Mat);//벡터 x 행렬

	float4 operator/(float _F) const
	{
		float4 Result{ *this };

		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Result.Arr1D[i] /= _F;
		}

		return Result;
	}
	float4 operator/=(float _F)
	{
		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Arr1D[i] /= _F;
		}

		return *this;
	}
#pragma endregion
#pragma region Constructor
	float4(float _X = 0.0f, float _Y = 0.0f, float _Z = 0.0f, float _W = 1.0f)
		: Arr1D{ _X, _Y, _Z, _W } {}
#pragma endregion
};

struct float4x4//행렬: 행 벡터 x Size
{
	union
	{
		float Arr1D[GameEngineMath::Size * GameEngineMath::Size];
		float Arr2D[GameEngineMath::Size][GameEngineMath::Size];
		float4 RowVec[GameEngineMath::Size];
	};

#pragma region Function
	void Zero()
	{
		std::fill_n(Arr1D, GameEngineMath::Size * GameEngineMath::Size, 0.0f);
	}
	void Identity()
	{
		Zero();
		for (int i = 0; i < GameEngineMath::Size; ++i)
		{
			Arr2D[i][i] = 1.0f;
		}
	}
	void Transpose()
	{
		for (int Row = 0; Row < GameEngineMath::Size; ++Row)
		{
			for (int Col = Row + 1; Col < GameEngineMath::Size; ++Col)
			{
				std::swap(Arr2D[Row][Col], Arr2D[Col][Row]);
			}
		}
	}
	void Scale(const float4& _Scale)
	{
		Zero();
		for (int i = 0; i < GameEngineMath::Size; ++i)
		{
			Arr2D[i][i] = _Scale.Arr1D[i];
		}
	}
	void Roll(float _Degree)//Z축 회전
	{
		Identity();
		float Radian = _Degree * GameEngineMath::D2R;

		Arr2D[0][0] = cosf(Radian);
		Arr2D[0][1] = sinf(Radian);
		Arr2D[1][0] = -sinf(Radian);
		Arr2D[1][1] = cosf(Radian);
	}
	void Yaw(float _Degree)//Y축 회전
	{
		Identity();
		float Radian = _Degree * GameEngineMath::D2R;

		Arr2D[0][0] = cosf(Radian);
		Arr2D[0][2] = -sinf(Radian);
		Arr2D[2][0] = sinf(Radian);
		Arr2D[2][2] = cosf(Radian);
	}
	void Pitch(float _Degree)//X축 회전
	{
		Identity();
		float Radian = _Degree * GameEngineMath::D2R;

		Arr2D[1][1] = cosf(Radian);
		Arr2D[1][2] = sinf(Radian);
		Arr2D[2][1] = -sinf(Radian);
		Arr2D[2][2] = cosf(Radian);
	}
	void Quaternion(const float4& _Degree)//아직 이상함
	{
		Identity();
		float X = _Degree.X * GameEngineMath::D2R;
		float Y = _Degree.Y * GameEngineMath::D2R;
		float Z = _Degree.Z * GameEngineMath::D2R;
		float W = _Degree.W;

		Arr2D[0][0] = 1 - 2 * Y * Y - 2 * Z * Z;
		Arr2D[0][1] = 2 * X * Y - 2 * W * Z;
		Arr2D[0][2] = 2 * X * Z + 2 * W * Z;

		Arr2D[1][0] = 2 * X * Y + 2 * W * Z;
		Arr2D[1][1] = 1 - 2 * X * X - 2 * Z * Z;
		Arr2D[1][2] = 2 * Y * Z - 2 * W * X;

		Arr2D[2][0] = 2 * X * Z - 2 * W * Y;
		Arr2D[2][1] = 2 * Y * Z + 2 * W * X;
		Arr2D[2][2] = 1 - 2 * X * X - 2 * Y * Y;
	}
	void Translation(const float4& _Pos)
	{
		Identity();
		RowVec[GameEngineMath::Size - 1] = _Pos;
	}

	float4 GetColVec(int _Idx) const
	{
		float4 ColVec{};

		for (int i = 0; i < GameEngineMath::Size; ++i)
		{
			ColVec.Arr1D[i] = Arr2D[i][_Idx];
		}

		return ColVec;
	}

	float4x4 operator*(const float4x4& _Mat) const
	{
		float4x4 Result{};
		for (int i = 0; i < GameEngineMath::Size; ++i)
		{
			for (int j = 0; j < GameEngineMath::Size; ++j)
			{
				Result.Arr2D[i][j] = RowVec[i] * _Mat.GetColVec(j);
			}
		}

		return Result;
	}
	float4x4 operator*=(const float4x4& _Mat)
	{
		float4x4 Result{ *this };
		for (int i = 0; i < GameEngineMath::Size; ++i)
		{
			for (int j = 0; j < GameEngineMath::Size; ++j)
			{
				Arr2D[i][j] = Result.RowVec[i] * _Mat.GetColVec(j);
			}
		}

		return *this;
	}
#pragma endregion
#pragma region Constructor
	float4x4(const float4& _Row1 = {}, const float4& _Row2 = {},
		const float4& _Row3 = {}, const float4& _Row4 = {})
		: RowVec{ _Row1, _Row2, _Row3, _Row4 } {}
#pragma endregion
};

//직교행렬의 역행렬은 그것의 전치행렬이다.
//회전(Rotation)과 관련
// 
//대각행렬의 역행렬은 대각의 역수행렬이다.
//크기(Scale)과 관련
// 
//밀기행렬의 역행렬은 대각을 제외한 나머지의 음수행렬이다.
//이동(Translation)과 관련

//벡터 + 벡터 = 벡터
//점 + 벡터 = 점
//점 - 점 = 벡터

/*#include <Windows.h>
#include <cmath>

#include <d3d11_4.h>
#include <d3dcompiler.h>
#include <DirectXPackedVector.h>
#include <DirectXCollision.h>

struct float4;
struct float4x4;
struct GameEngineMath
{
	static const float PI;
	static const float PI2;
	static const float D2R;
	static const float R2D;
};

struct float4
{
public:
#pragma region Static Var
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;
	static const float4 Front;
	static const float4 Back;
#pragma endregion Static Var

#pragma region Member Var
	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};
		float Arr1D[4];
	};
#pragma endregion Member Var

#pragma region Function
	POINT ToPoint() const
	{
		return { static_cast<int>(X), static_cast<int>(Y) };
	}

	void RotateX(float _Angle)
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		Z = Tmp.Z * cosf(Radian) - Tmp.Y * sinf(Radian);
		Y = Tmp.Z * sinf(Radian) + Tmp.Y * cosf(Radian);
	}
	void RotateY(float _Angle)
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		X = Tmp.X * cosf(Radian) - Tmp.Z * sinf(Radian);
		Z = Tmp.X * sinf(Radian) + Tmp.Z * cosf(Radian);
	}
	void RotateZ(float _Angle)
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		X = Tmp.X * cosf(Radian) - Tmp.Y * sinf(Radian);
		Y = -(Tmp.X * sinf(Radian) + Tmp.Y * cosf(Radian));
	}
	float4 RotateXReturn(float _Angle) const
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		Tmp.Z = Z * cosf(Radian) - Y * sinf(Radian);
		Tmp.Y = Z * sinf(Radian) + Y * cosf(Radian);

		return Tmp;
	}
	float4 RotateYReturn(float _Angle) const
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		Tmp.X = X * cosf(Radian) - Z * sinf(Radian);
		Tmp.Z = X * sinf(Radian) + Z * cosf(Radian);

		return Tmp;
	}
	float4 RotateZReturn(float _Angle) const
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		Tmp.X = X * cosf(Radian) - Y * sinf(Radian);
		Tmp.Y = -(X * sinf(Radian) + Y * cosf(Radian));

		return Tmp;
	}

	float Distance() const
	{
		return sqrtf(X * X + Y * Y + Z * Z);
	}
	void Normalize()
	{
		float Length = Distance();
		if (Length == 0.0f)
		{
			return;
		}

		X /= Length;
		Y /= Length;
		Z /= Length;
	}

	static float4 Cross3D(const float4& _Left, const float4& _Right)
	{
		float4 Result
		{
			_Left.Y * _Right.Z - _Left.Z * _Right.Y,
			_Left.Z * _Right.X - _Left.X * _Right.Z,
			_Left.X * _Right.Y - _Left.Y * _Right.X
		};

		return Result;
	}
	static float Dot3D(const float4& _Left, const float4& _Right)
	{
		return _Left.X * _Right.X + _Left.Y * _Right.Y + _Left.Z * _Right.Z;
	}
#pragma endregion Function

#pragma region Operator
	void operator/=(float _f)
	{
		X /= _f;
		Y /= _f;
		Z /= _f;
	}
	void operator+=(const float4& _Ref)
	{
		X += _Ref.X;
		Y += _Ref.Y;
		Z += _Ref.Z;
	}
	void operator-=(const float4& _Ref)
	{
		X -= _Ref.X;
		Y -= _Ref.Y;
		Z -= _Ref.Z;
	}
	void operator*=(const float4& _Ref)
	{
		X *= _Ref.X;
		Y *= _Ref.Y;
		Z *= _Ref.Z;
	}
	void operator/=(const float4& _Ref)
	{
		X /= _Ref.X;
		Y /= _Ref.Y;
		Z /= _Ref.Z;
	}
	void operator*=(const float4x4& _Ref);

	float4 operator*(float _f) const
	{
		return { X * _f, Y * _f, Z * _f, W };
	}
	float4 operator+(const float4& _Ref) const
	{
		return { X + _Ref.X, Y + _Ref.Y, Z + _Ref.Z, W };
	}
	float4 operator-(const float4& _Ref) const
	{
		return { X - _Ref.X, Y - _Ref.Y, Z - _Ref.Z, W };
	}
	float4 operator*(const float4& _Ref) const
	{
		return { X * _Ref.X, Y * _Ref.Y, Z * _Ref.Z, W };
	}

	float4 operator-() const
	{
		return { -X, -Y, -Z, W };
	}
#pragma endregion Operator

#pragma region Constructor
	float4(float _X = 0.0f, float _Y = 0.0f, float _Z = 0.0f, float _W = 1.0f)
		: X(_X), Y(_Y), Z(_Z), W(_W)
	{}
	float4(const float4& _Ref)
		: X(_Ref.X), Y(_Ref.Y), Z(_Ref.Z), W(_Ref.W)
	{}
	float4(float4&& _Rvalue) noexcept
		: X(_Rvalue.X), Y(_Rvalue.Y), Z(_Rvalue.Z), W(_Rvalue.W)
	{}
	void operator=(const float4& _Ref)
	{
		X = _Ref.X;
		Y = _Ref.Y;
		Z = _Ref.Z;
		W = _Ref.W;
	}
	void operator=(float4&& _Rvalue) noexcept
	{
		X = _Rvalue.X;
		Y = _Rvalue.Y;
		Z = _Rvalue.Z;
		W = _Rvalue.W;
	}
#pragma endregion Constructor
};

struct float4x4
{
#pragma region Member Var
	union
	{
		float Arr1D[16]{};
		float Arr2D[4][4];
	};
#pragma endregion Member Var

#pragma region Function
	void Reset();
	void Identity();
	void Scale(const float4& _Value)
	{
		Identity();
		Arr2D[0][0] = _Value.X;
		Arr2D[1][1] = _Value.Y;
		Arr2D[2][2] = _Value.Z;
	}
	void Position(const float4& _Value)
	{
		Identity();
		Arr2D[3][0] = _Value.X;
		Arr2D[3][1] = _Value.Y;
		Arr2D[3][2] = _Value.Z;
	}

	void RotateX(float _Angle)
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
	void RotateY(float _Angle)
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
	void RotateZ(float _Angle)
	{
		Identity();

		float Radian = _Angle * GameEngineMath::D2R;
		float CosValue = cosf(Radian);
		float SinValue = sinf(Radian);
		Arr2D[0][0] = CosValue;
		Arr2D[0][1] = SinValue;
		Arr2D[1][0] = -SinValue;
		Arr2D[1][1] = CosValue;
	}
	float4x4 RotateXReturn(float _Angle)
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
	float4x4 RotateYReturn(float _Angle)
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
	float4x4 RotateZReturn(float _Angle)
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

		return Tmp;
	}

	void InsertVector(int _Idx, int _size, const float4& _Ref);
	void Transpose();
	void LookAtLH(const float4& _EyePos, const float4& _EyeFront, const float4& _EyeUp);
	void OrthographicLH(float _Width, float _Height, float _Far, float _Near)
	{
		Identity();
		Arr2D[0][0] = 2.0f / _Width;
		Arr2D[1][1] = 2.0f / _Height;

		Arr2D[2][2] = 1.0f / (_Far - _Near);
		Arr2D[3][2] = -(1.0f / (_Far - _Near)) * _Near;
	}
	void PerspectiveFovLH(float _FovAngle, float _Width, float _Height, float _Far, float _Near);
	void ViewPort(float _Width, float _Height, float _Left, float _Right,
		float _ZMin = 0.0f, float _ZMax = 1.0f);
#pragma endregion Function

#pragma region Operator
	void operator*=(const float4x4& _Ref);
	float4x4 operator*(const float4x4& _Ref) const;
#pragma endregion Operator

#pragma region Constructor
	float4x4();
	float4x4(const float4x4& _Ref);
	float4x4(float4x4&& _Rvalue) noexcept;
	void operator=(const float4x4& _Ref) = delete;
	void operator=(float4x4&& _Rvalue) noexcept;
#pragma endregion Constructor
};*/