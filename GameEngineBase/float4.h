#pragma once
#include <Windows.h>
#include <cmath>

class float4x4;
class float4
{
public:
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
		float Arr1D[4];
	};
public:
	/*float4 Half() const
	{
		return { X * 0.5f, Y * 0.5f, Z * 0.5f, 1.0f };
	}*/
	POINT ToPoint()
	{
		return { static_cast<int>(X), static_cast<int>(Y) };
	}

	void RotateX(float _Angle);
	void RotateY(float _Angle);
	void RotateZ(float _Angle);
	float4 RotateXReturn(float _Angle) const;
	float4 RotateYReturn(float _Angle) const;
	float4 RotateZReturn(float _Angle) const;

	float Distance()
	{
		return sqrtf(X * X + Y * Y + Z * Z);// z * z°¡ ¾øÀ½
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
public:
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
public:
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
};