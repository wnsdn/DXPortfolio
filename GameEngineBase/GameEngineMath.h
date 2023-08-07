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

struct float4//Vector : RowVec
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
		W = 1.0f;
	}
	float4 NormalizeReturn()
	{
		float Length = Size();
		return { X / Length, Y / Length, Z / Length, 1.0f };
	}
	void RotateX(float _Deg)
	{
		float Radian = _Deg * GameEngineMath::D2R;
		float CR = cosf(Radian);
		float SR = sinf(Radian);

		Y = Y * CR - Z * SR;
		Z = Y * SR + Z * CR;
	}
	void RotateY(float _Deg)
	{
		float Radian = _Deg * GameEngineMath::D2R;
		float CR = cosf(Radian);
		float SR = sinf(Radian);

		X = X * CR + Z * SR;
		Z = -X * SR + Z * CR;
	}
	void RotateZ(float _Deg)
	{
		float Radian = _Deg * GameEngineMath::D2R;
		float CR = cosf(Radian);
		float SR = sinf(Radian);

		X = X * CR - Y * SR;
		Y = X * SR + Y * CR;
	}
	static float Dot(const float4& _V1, const float4& _V2)//Dot Product
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
	static float4 Cross(const float4& _V1, const float4& _V2)//Cross Product
	{
		float4 Result{};
		//float4 V1 = _V1;
		//float4 V2 = _V2;
		//V1.Normalize();
		//V2.Normalize();

		Result.X = _V1.Y * _V2.Z - _V1.Z * _V2.Y;
		Result.Y = _V1.Z * _V2.X - _V1.X * _V2.Z;
		Result.Z = _V1.X * _V2.Y - _V1.Y * _V2.X;

		return Result;
	}

	float operator*(const float4& _Vec) const//Vector x Vector
	{
		float Result = 0.0f;

		for (int i = 0; i < GameEngineMath::Size; ++i)
		{
			Result += Arr1D[i] * _Vec.Arr1D[i];
		}

		return Result;
	}
	float4 operator*(const float4x4& _Mat) const;//Vector x Matrix
	float4 operator*=(const float4x4& _Mat);//Vector x Matrix

#pragma region Operator
	float4 operator-(const float4& _Vec) const
	{
		float4 Result{ *this };

		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Result.Arr1D[i] -= _Vec.Arr1D[i];
		}

		return Result;
	}
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
	void operator/=(float _F)
	{
		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Arr1D[i] /= _F;
		}
	}
	void operator+=(const float4& _Vec)
	{
		for (int i = 0; i < GameEngineMath::Size - 1; ++i)
		{
			Arr1D[i] += _Vec.Arr1D[i];
		}
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
	operator POINT() const
	{
		return { static_cast<int>(X), static_cast<int>(Y) };
	}
#pragma endregion
#pragma endregion
#pragma region Constructor
	float4(float _X = 0.0f, float _Y = 0.0f, float _Z = 0.0f, float _W = 1.0f)
		: Arr1D{ _X, _Y, _Z, _W } {}
#pragma endregion
};

struct float4x4//Matrix: RowVec x Size
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
	void ViewDeg(const float4& _CamPos, const float4& _CamDeg)
	{
		Identity();
		float4x4 Translation4x4{}, Rotation4x4{};

		Translation4x4.Translation(-_CamPos);
		Rotation4x4.Rotate(_CamDeg);
		Rotation4x4.Transpose();

		*this *= Translation4x4 * Rotation4x4;
	}
	void ViewDir(const float4& _CamPos, const float4& _CamDir)
	{
		Identity();
		float4 Front{ _CamDir };
		float4 Right{ float4::Cross(float4::Up, Front) };
		float4 Up{ float4::Cross(Front, Right) };

		float4x4 Translation4x4{}, Rotation4x4{};

		Translation4x4.Translation(-_CamPos);
		Rotation4x4.RowVec[0] = Right;
		Rotation4x4.RowVec[1] = Up;
		Rotation4x4.RowVec[2] = Front;
		Rotation4x4.RowVec[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
		Rotation4x4.Transpose();

		*this *= Translation4x4 * Rotation4x4;
	}
	void Orthograhpic(float _Width, float _Height, float _Far, float _Near)
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

		float FovY = _Degree * GameEngineMath::D2R;
		float AspectRatio = _Width / _Height;
		float Distance = 1.0f / tanf(FovY * 0.5f);
		float Depth = _Far - _Near;

		Arr2D[0][0] = Distance / AspectRatio;
		Arr2D[1][1] = Distance;
		Arr2D[2][2] = 1.0f / Depth;
		Arr2D[3][2] = -_Near / Depth;
		Arr2D[2][3] = 1.0f;
		Arr2D[3][3] = 0.0f;

		/*
		// y : y' = z : D
		// y'z = yD
		// y' = y * (D / z)
		// Y = D / z

		// x : x' = z : D
		// x'z = xD
		// x' = x * (D / (z * AR))
		// X = D / (z * AR)

		// N <= z <= F
		// 0 <= z - N <= F - N
		// 0 <= (z - N) / (F - N) <= 1
		// 0 <= z / (F - N) - N / (F - N) <= 1

		// X = D / AR
		// Y = D
		// Z = 1.0f / (F - N)
		// Z = -N / (F - N)

		// X 0 0 0
		// 0 Y 0 0
		// 0 0 Z 1
		// 0 0 Z 0
		*/
	}
	void ViewPort(float _Width, float _Height)
	{
		Identity();

		float HalfWidth = _Width * 0.5f;
		float HalfHeight = _Height * 0.5f;

		Arr2D[0][0] = HalfWidth;
		Arr2D[1][1] = -HalfHeight;
		Arr2D[3][0] = HalfWidth;
		Arr2D[3][1] = HalfHeight;
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

	float4x4 operator*(const float4x4& _Mat) const//Matrix x Matrix
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
	float4x4 operator*=(const float4x4& _Mat)//Matrix x Matrix
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
