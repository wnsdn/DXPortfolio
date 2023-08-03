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

#pragma region Operator
	float4 operator*(float _F) const
	{
		float4 Result{ *this };

		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Result.Arr1D[i] *= _F;
		}

		return Result;
	}
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
	float4 operator+=(const float4& _Vec)
	{
		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Arr1D[i] += _Vec.Arr1D[i];
		}

		return *this;
	}
	float4 operator-() const
	{
		float4 Result{};

		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Result.Arr1D[i] = -Arr1D[i];
		}

		return Result;
	}
#pragma endregion
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
	void Rotate(const float4& _Degree)
	{
		Identity();
		float4x4 Pitch{}, Yaw{}, Roll{};

		Pitch.RotateX(_Degree.X);
		Yaw.RotateY(_Degree.Y);
		Roll.RotateZ(_Degree.Z);

		*this *= Pitch * Yaw * Roll;
	}
	void Translation(const float4& _Pos)
	{
		Identity();
		RowVec[GameEngineMath::Size - 1] = _Pos;
	}
	void View(const float4& _CamDeg, const float4& _CamPos)
	{
		Identity();
		float4x4 Rotation4x4{}, Translation4x4{};

		Rotation4x4.Rotate(_CamDeg);
		Rotation4x4.Transpose();
		Translation4x4.Translation(-_CamPos);

		*this *= Rotation4x4 * Translation4x4;
	}
	void Normalize(float _Width, float _Height, float _Far, float _Near)
	{
		Identity();
		float Depth = _Far - _Near;

		Arr2D[0][0] = 2.0f / _Width;
		Arr2D[1][1] = 2.0f / _Height;
		Arr2D[2][2] = 1.0f / Depth;
		Arr2D[3][2] = -_Near / Depth;
	}
	void Perspective(float _Degree, float _Width, float _Height, float _Far, float _Near)
	{
		Identity();

		float FOV = _Degree * GameEngineMath::D2R;
		float Distance = 1.0f / tanf(FOV / 2.0f);
		float AspectRatio = _Width / _Height;

		Arr2D[0][0] *= Distance / AspectRatio;
		Arr2D[1][1] *= Distance;
		Arr2D[2][2] = _Far / (_Far - _Near);
		Arr2D[2][3] = 1.0f;
		Arr2D[3][2] = -_Near * _Far / (_Far - _Near);
		Arr2D[3][3] = 0.0f;
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
	float4x4()
	{
		Identity();
	}
	float4x4(const float4& _Row1, const float4& _Row2 = {},
		const float4& _Row3 = {}, const float4& _Row4 = {})
		: RowVec{ _Row1, _Row2, _Row3, _Row4 } {}
#pragma endregion
#pragma region Private
private:
	void RotateX(float _Degree)//Pitch
	{
		Identity();
		float Radian = _Degree * GameEngineMath::D2R;
		float CR = cosf(Radian);
		float SR = sinf(Radian);

		Arr2D[1][1] = CR;
		Arr2D[1][2] = SR;
		Arr2D[2][1] = -SR;
		Arr2D[2][2] = CR;
	}
	void RotateY(float _Degree)//Yaw
	{
		Identity();
		float Radian = _Degree * GameEngineMath::D2R;
		float CR = cosf(Radian);
		float SR = sinf(Radian);

		Arr2D[0][0] = CR;
		Arr2D[0][2] = -SR;
		Arr2D[2][0] = SR;
		Arr2D[2][2] = CR;
	}
	void RotateZ(float _Degree)//Roll
	{
		Identity();
		float Radian = _Degree * GameEngineMath::D2R;
		float CR = cosf(Radian);
		float SR = sinf(Radian);

		Arr2D[0][0] = CR;
		Arr2D[0][1] = SR;
		Arr2D[1][0] = -SR;
		Arr2D[1][1] = CR;
	}
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