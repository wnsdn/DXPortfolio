#pragma once
#include <DirectXMath.h>
#include <DirectXCollision.h>

struct float4x4;

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

	static const float4 WHITE;
	static const float4 RED;
	static const float4 GREEN;
	static const float4 BLUE;

	union
	{
		struct
		{
			float X;
			float Y;
			float Z;
			float W;
		};

		struct
		{
			float R;
			float G;
			float B;
			float A;
		};

		struct
		{
			float Pos2DX;
			float Pos2DY;
			float Scale2DX;
			float Scale2DY;
		};

		DirectX::XMVECTOR Vector;
		DirectX::XMFLOAT3 Float3;
		DirectX::XMFLOAT4 Float4;
	};

#pragma region Function
	int iX() const
	{
		return static_cast<int>(X);
	}
	int iY() const
	{
		return static_cast<int>(Y);
	}
	UINT uiX() const
	{
		return static_cast<UINT>(X);
	}
	UINT uiY() const
	{
		return static_cast<UINT>(Y);
	}
	float hX() const
	{
		return X * 0.5f;
	}
	float hY() const
	{
		return Y * 0.5f;
	}
	int ihX() const
	{
		return static_cast<int>(X * 0.5f);
	}
	int ihY() const
	{
		return static_cast<int>(Y * 0.5f);
	}
	float4 Half() const
	{
		return { X * 0.5f, Y * 0.5f, Z, W };
	}

	float4 ToAbs() const
	{
		return DirectX::XMVectorAbs(Vector);
	}

	std::string ToString(std::string_view _Next = "")
	{
		return "X : " + std::to_string(X) + " Y : " + std::to_string(Y) + " Z : " + std::to_string(Z) + _Next.data();
	}

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

	float4 QuaternionToEuler()
	{
		float4 Result{};

		float SinRCosP = 2.0f * (W * Z + X * Y);
		float CosRCosP = 1.0f - 2.0f * (Z * Z + X * X);

		Result.Z = atan2f(SinRCosP, CosRCosP);

		float PitchTest = W * X - Y * Z;
		float ASinThreshold = 0.4999995f;
		float SinP = 2.0f * PitchTest;

		if (PitchTest < -ASinThreshold)
		{
			Result.X = -(0.5f * DirectX::XM_PI);
		}
		else if (PitchTest > ASinThreshold)
		{
			Result.X = (0.5f * DirectX::XM_PI);
		}
		else
		{
			Result.X = asinf(SinP);
		}

		float SinYCosP = 2.0f * (W * Y + X * Z);
		float CosYCosP = 1.0f - 2.0f * (X * X + Y * Y);

		Result.Y = atan2f(SinYCosP, CosYCosP);

		Result.X = DirectX::XMConvertToDegrees(Result.X);
		Result.Y = DirectX::XMConvertToDegrees(Result.Y);
		Result.Z = DirectX::XMConvertToDegrees(Result.Z);

		return Result;
	}

	float4 EulerToQuaternion()
	{
		float4 Result = Vector;
		Result.X = DirectX::XMConvertToRadians(Result.X);
		Result.Y = DirectX::XMConvertToRadians(Result.Y);
		Result.Z = DirectX::XMConvertToRadians(Result.Z);
		return DirectX::XMQuaternionRotationRollPitchYawFromVector(Result.Vector);
	}

	static float Dot(const float4& _V1, const float4& _V2)//Dot Product
	{
		return DirectX::XMVector3Dot(_V1.Vector, _V2.Vector).m128_f32[0];
	}
	static float4 Cross(const float4& _V1, const float4& _V2)//Cross Product
	{
		return DirectX::XMVector3Cross(_V1.Vector, _V2.Vector);
	}
	static float Length2D(const float4& _Left, const float4& _Right)
	{
		float4 Diff = _Left - _Right;
		return DirectX::XMVector2Length(Diff).m128_f32[0];
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
	operator const FLOAT* () const
	{
		return Vector.m128_f32;
	}
#pragma endregion

#pragma region Constructor
	float4(float _X = 0.0f, float _Y = 0.0f, float _Z = 0.0f, float _W = 0.0f)
		: Vector{ _X, _Y, _Z, _W } {}
	float4(DirectX::FXMVECTOR _Vector)
		: Vector(_Vector) {}
	float4(const POINT& _Point)
		: Vector{ static_cast<float>(_Point.x), static_cast<float>(_Point.y), 0.0f, 0.0f } {}
#pragma endregion
};

struct float4x4//Matrix
{
	union
	{
		float4 RowVec[4];
		DirectX::XMMATRIX Matrix;
	};

#pragma region Function
	void Zero()
	{
		//std::fill_n(Matrix, GameEngineMath::Size * GameEngineMath::Size, 0.0f);
	}
	void Identity()
	{
		Matrix = DirectX::XMMatrixIdentity();
	}
	void Transpose()
	{
		Matrix = DirectX::XMMatrixTranspose(Matrix);
	}
	void Scaling(const float4& _Scale)
	{
		Matrix = DirectX::XMMatrixScalingFromVector(_Scale.Vector);
	}
	void Rotation(const float4& _Angles)
	{
		float4 Rotation
		{
			DirectX::XMConvertToRadians(_Angles.X),
			DirectX::XMConvertToRadians(_Angles.Y),
			DirectX::XMConvertToRadians(_Angles.Z)
		};

		Matrix = DirectX::XMMatrixRotationRollPitchYawFromVector(Rotation.Vector);
	}
	void Translation(const float4& _Offset)
	{
		Matrix = DirectX::XMMatrixTranslationFromVector(_Offset.Vector);
	}
	void View(const float4& _EyePos, const float4& _EyeDir, const float4& _UpDir)
	{
		Matrix = DirectX::XMMatrixLookToLH(_EyePos, _EyeDir, _UpDir);
	}
	void Orthograhpic(float _Width, float _Height, float _Far, float _Near)
	{
		Matrix = DirectX::XMMatrixOrthographicLH(_Width, _Height, _Near, _Far);
	}
	void Perspective(float _Degree, float _Width, float _Height, float _Far, float _Near)
	{
		Matrix = DirectX::XMMatrixPerspectiveFovLH(
			DirectX::XMConvertToRadians(_Degree), _Width / _Height, _Near, _Far);
	}
	void ViewPort(float _Width, float _Height)
	{
		Identity();

		float HalfWidth = _Width * 0.5f;
		float HalfHeight = _Height * 0.5f;

		Matrix.r[0].m128_f32[0] = HalfWidth;
		Matrix.r[1].m128_f32[1] = -HalfHeight;
		Matrix.r[3].m128_f32[0] = HalfWidth;
		Matrix.r[3].m128_f32[1] = HalfHeight;
	}

	void Compose(float4& _Scale, float4& _RotQuaternion, float4& _Pos)
	{
		Matrix = DirectX::XMMatrixAffineTransformation(_Scale.Vector, _RotQuaternion.Vector, _RotQuaternion.Vector, _Pos.Vector);
	}
	void Decompose(float4& _Scale, float4& _RotQuaternion, float4& _Pos) const
	{
		DirectX::XMMatrixDecompose(&_Scale.Vector, &_RotQuaternion.Vector, &_Pos.Vector, Matrix);
	}

	float4x4 InverseReturn() const
	{
		return DirectX::XMMatrixInverse(nullptr, Matrix);
	}
#pragma endregion

#pragma region Operator
	//산술연산 float4x4
	float4x4 operator*(const float4x4& _Other)
	{
		return Matrix * _Other.Matrix;
	}
	void operator*=(const float4x4& _Other)
	{
		Matrix *= _Other.Matrix;
	}
	//형변환 연산
	operator DirectX::XMMATRIX() const
	{
		return Matrix;
	}
#pragma endregion

#pragma region Constructor
	float4x4()
	{
		Identity();
	}
	float4x4(DirectX::FXMMATRIX _Matrix)
		: Matrix(_Matrix) {}
#pragma endregion
};
