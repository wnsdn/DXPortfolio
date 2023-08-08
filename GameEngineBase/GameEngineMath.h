#pragma once
#include <Windows.h>

#include <DirectXMath.h>

struct float4;
struct float4x4;

struct GameEngineMath
{
};

struct float4//Vector
{
	static const float4 One;
	static const float4 OneNull;
	static const float4 Zero;
	static const float4 ZeroNull;

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
		DirectX::XMVECTOR Vector;
	};

#pragma region Function
	float Length() const
	{
		return DirectX::XMVector3Length(Vector).m128_f32[0];
	}
	void Normalize()
	{
		Vector = DirectX::XMVector3Normalize(Vector);
	}
	float4 NormalizeReturn() const
	{
		return DirectX::XMVector3Normalize(Vector);
	}
	void Rotate(const float4& _Rotation)
	{
		float4 Rotation
		{
			DirectX::XMConvertToRadians(_Rotation.X),
			DirectX::XMConvertToRadians(_Rotation.Y),
			DirectX::XMConvertToRadians(_Rotation.Z)
		};

		Vector = DirectX::XMVector3Rotate
		(
			Vector,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(Rotation.Vector)
		);
	}
	float4 RotateReturn(const float4& _Rotation)
	{
		float4 Rotation
		{
			DirectX::XMConvertToRadians(_Rotation.X),
			DirectX::XMConvertToRadians(_Rotation.Y),
			DirectX::XMConvertToRadians(_Rotation.Z)
		};

		float4 Result = DirectX::XMVector3Rotate
		(
			Vector,
			DirectX::XMQuaternionRotationRollPitchYawFromVector(Rotation.Vector)
		);

		return Result;
	}
	static float Dot(const float4& _V1, const float4& _V2)//Dot Product
	{
		return DirectX::XMVector3Dot(_V1.Vector, _V2.Vector).m128_f32[0];
	}
	static float4 Cross(const float4& _V1, const float4& _V2)//Cross Product
	{
		return DirectX::XMVector3Cross(_V1.Vector, _V2.Vector);
	}
#pragma endregion
#pragma region Operator
	//산술연산 float
	float4 operator+(float _F) const
	{
		float4 Other{ _F, _F, _F };
		float4 Result{ DirectX::XMVectorAdd(Vector, Other) };
		return Result;
	}
	float4 operator-(float _F) const
	{
		float4 Other{ _F, _F, _F };
		float4 Result{ DirectX::XMVectorSubtract(Vector, Other) };
		return Result;
	}
	float4 operator*(float _F) const
	{
		float4 Other{ _F, _F, _F, 1.0f };
		float4 Result{ DirectX::XMVectorMultiply(Vector, Other) };
		return Result;
	}
	float4 operator/(float _F) const
	{
		float4 Other{ _F, _F, _F, 1.0f };
		float4 Result{ DirectX::XMVectorDivide(Vector, Other) };
		return Result;
	}
	void operator+=(float _F)
	{
		float4 Other{ _F, _F, _F };
		Vector = DirectX::XMVectorAdd(Vector, Other);
	}
	void operator-=(float _F)
	{
		float4 Other{ _F, _F, _F };
		Vector = DirectX::XMVectorSubtract(Vector, Other);
	}
	void operator*=(float _F)
	{
		float4 Other{ _F, _F, _F, 1.0f };
		Vector = DirectX::XMVectorMultiply(Vector, Other);
	}
	void operator/=(float _F)
	{
		float4 Other{ _F, _F, _F, 1.0f };
		Vector = DirectX::XMVectorDivide(Vector, Other);
	}
	//산술연산 float4
	float4 operator+(const float4& _Other) const
	{
		float4 Result{ DirectX::XMVectorAdd(Vector, _Other) };
		Result.W = 1.0f;
		return Result;
	}
	float4 operator-(const float4& _Other) const
	{
		float4 Result{ DirectX::XMVectorSubtract(Vector, _Other) };
		Result.W = 1.0f;
		return Result;
	}
	float4 operator*(const float4& _Other) const
	{
		float4 Result{ DirectX::XMVectorMultiply(Vector, _Other) };
		Result.W = 1.0f;
		return Result;
	}
	float4 operator/(const float4& _Other) const
	{
		float4 Result{ DirectX::XMVectorDivide(Vector, _Other) };
		Result.W = 1.0f;
		return Result;
	}
	void operator+=(const float4& _Other)
	{
		Vector = DirectX::XMVectorAdd(Vector, _Other);
		W = 1.0f;
	}
	void operator-=(const float4& _Other)
	{
		Vector = DirectX::XMVectorSubtract(Vector, _Other);
		W = 1.0f;
	}
	void operator*=(const float4& _Other)
	{
		Vector = DirectX::XMVectorMultiply(Vector, _Other);
		W = 1.0f;
	}
	void operator/=(const float4& _Other)
	{
		Vector = DirectX::XMVectorDivide(Vector, _Other);
		W = 1.0f;
	}
	//산술연산 float4x4
	float4 operator*(const float4x4& _Matrix) const;
	void operator*=(const float4x4& _Matrix);
	//Negate
	float4 operator-() const
	{
		float4 Result{ DirectX::XMVectorNegate(Vector) };
		Result.W = 1.0f;
		return Result;
	}
	//형변환 연산
	operator POINT() const
	{
		return { static_cast<int>(X), static_cast<int>(Y) };
	}
	operator DirectX::FXMVECTOR() const
	{
		return Vector;
	}
#pragma endregion
#pragma region Constructor
	float4(float _X = 0.0f, float _Y = 0.0f, float _Z = 0.0f, float _W = 0.0f)
		: Vector{ _X, _Y, _Z, _W } {}
	float4(DirectX::FXMVECTOR _Vector)
		: Vector(_Vector) {}
#pragma endregion
};

struct float4x4//Matrix
{
	DirectX::XMMATRIX Matrix;

#pragma region Function
	void Zero()
	{
		//std::fill_n(Matrix, GameEngineMath::Size * GameEngineMath::Size, 0.0f);
	}
	void Identity()
	{
		Matrix = DirectX::XMMatrixIdentity();
	}
	//void Transpose()
	//{
	//	for (int Row = 0; Row < GameEngineMath::Size; ++Row)
	//	{
	//		for (int Col = Row + 1; Col < GameEngineMath::Size; ++Col)
	//		{
	//			std::swap(Arr2D[Row][Col], Arr2D[Col][Row]);
	//		}
	//	}
	//}
	//void Scale(const float4& _Scale)
	//{
	//	Zero();
	//	for (int i = 0; i < GameEngineMath::Size; ++i)
	//	{
	//		//Arr2D[i][i] = _Scale.Arr1D[i];
	//	}
	//}
	//void Rotate(const float4& _Degree)
	//{
	//	Identity();
	//	float4x4 Pitch{}, Yaw{}, Roll{};

	//	Pitch.RotateX(_Degree.X);
	//	Yaw.RotateY(_Degree.Y);
	//	Roll.RotateZ(_Degree.Z);

	//	*this *= Pitch * Yaw * Roll;
	//}
	//void Translation(const float4& _Pos)
	//{
	//	Identity();
	//	RowVec[GameEngineMath::Size - 1] = _Pos;
	//}
	//void ViewDeg(const float4& _CamPos, const float4& _CamDeg)
	//{
	//	Identity();
	//	float4x4 Translation4x4{}, Rotation4x4{};

	//	//Translation4x4.Translation(-_CamPos);
	//	Rotation4x4.Rotate(_CamDeg);
	//	Rotation4x4.Transpose();

	//	*this *= Translation4x4 * Rotation4x4;
	//}
	//void ViewDir(const float4& _CamPos, const float4& _CamDir)
	//{
	//	Identity();
	//	float4 Front{ _CamDir };
	//	float4 Right{ float4::Cross(float4::Up, Front) };
	//	float4 Up{ float4::Cross(Front, Right) };

	//	float4x4 Translation4x4{}, Rotation4x4{};

	//	//Translation4x4.Translation(-_CamPos);
	//	Rotation4x4.RowVec[0] = Right;
	//	Rotation4x4.RowVec[1] = Up;
	//	Rotation4x4.RowVec[2] = Front;
	//	Rotation4x4.RowVec[3] = { 0.0f, 0.0f, 0.0f, 1.0f };
	//	Rotation4x4.Transpose();

	//	*this *= Translation4x4 * Rotation4x4;
	//}
	//void Orthograhpic(float _Width, float _Height, float _Far, float _Near)
	//{
	//	Identity();
	//	float Depth = _Far - _Near;

	//	Arr2D[0][0] = 2.0f / _Width;
	//	Arr2D[1][1] = 2.0f / _Height;
	//	Arr2D[2][2] = 1.0f / Depth;
	//	Arr2D[3][2] = -_Near / Depth;
	//}
	//void Perspective(float _Degree, float _Width, float _Height, float _Far, float _Near)
	//{
	//	Identity();

	//	float FovY = _Degree * GameEngineMath::D2R;
	//	float AspectRatio = _Width / _Height;
	//	float Distance = 1.0f / tanf(FovY * 0.5f);
	//	float Depth = _Far - _Near;

	//	Arr2D[0][0] = Distance / AspectRatio;
	//	Arr2D[1][1] = Distance;
	//	Arr2D[2][2] = 1.0f / Depth;
	//	Arr2D[3][2] = -_Near / Depth;
	//	Arr2D[2][3] = 1.0f;
	//	Arr2D[3][3] = 0.0f;

	//	/*
	//	// y : y' = z : D
	//	// y'z = yD
	//	// y' = y * (D / z)
	//	// Y = D / z

	//	// x : x' = z : D
	//	// x'z = xD
	//	// x' = x * (D / (z * AR))
	//	// X = D / (z * AR)

	//	// N <= z <= F
	//	// 0 <= z - N <= F - N
	//	// 0 <= (z - N) / (F - N) <= 1
	//	// 0 <= z / (F - N) - N / (F - N) <= 1

	//	// X = D / AR
	//	// Y = D
	//	// Z = 1.0f / (F - N)
	//	// Z = -N / (F - N)

	//	// X 0 0 0
	//	// 0 Y 0 0
	//	// 0 0 Z 1
	//	// 0 0 Z 0
	//	*/
	//}
	//void ViewPort(float _Width, float _Height)
	//{
	//	Identity();

	//	float HalfWidth = _Width * 0.5f;
	//	float HalfHeight = _Height * 0.5f;

	//	Arr2D[0][0] = HalfWidth;
	//	Arr2D[1][1] = -HalfHeight;
	//	Arr2D[3][0] = HalfWidth;
	//	Arr2D[3][1] = HalfHeight;
	//}

	//float4 GetColVec(int _Idx) const
	//{
	//	float4 ColVec{};

	//	for (int i = 0; i < GameEngineMath::Size; ++i)
	//	{
	//		//ColVec.Arr1D[i] = Arr2D[i][_Idx];
	//	}

	//	return ColVec;
	//}
	//산술연산 float4x4
	//형변환 연산
	operator DirectX::XMMATRIX() const
	{
		return Matrix;
	}
#pragma endregion
#pragma region Constructor
	float4x4(const float4& _Row1 = {}, const float4& _Row2 = {},
		const float4& _Row3 = {}, const float4& _Row4 = {})
		: Matrix{ _Row1.Vector, _Row2.Vector, _Row3.Vector, _Row4.Vector } {}
	float4x4(DirectX::FXMMATRIX _Matrix)
		: Matrix(_Matrix) {}
#pragma endregion
};
