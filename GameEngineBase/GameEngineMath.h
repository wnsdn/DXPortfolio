#pragma once

class GameEngineMath
{
public:
	static const float PI;
	static const float PI2;
	static const float D2R;
	static const float R2D;
};

class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;

	float X = 0.0f;
	float Y = 0.0f;
	float Z = 0.0f;
	float W = 1.0f;
public:
	float4 Half() const
	{
		return { X * 0.5f, Y * 0.5f };
	}
	POINT ToPoint()
	{
		return { static_cast<int>(X), static_cast<int>(Y) };
	}

	void RotateX(const float _Angle)//Rotate 한번 손봐야함
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		Z = Tmp.Z * cosf(Radian) - Tmp.Y * sinf(Radian);
		Y = Tmp.Z * sinf(Radian) + Tmp.Y * cosf(Radian);
	}
	void RotateY(const float _Angle)
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		X = Tmp.X * cosf(Radian) - Tmp.Z * sinf(Radian);
		Z = Tmp.X * sinf(Radian) + Tmp.Z * cosf(Radian);
	}
	void RotateZ(const float _Angle)
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		X = Tmp.X * cosf(Radian) - Tmp.Y * sinf(Radian);
		Y = -(Tmp.X * sinf(Radian) + Tmp.Y * cosf(Radian));
	}

	float4 GetRotateX(const float _Angle) const
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		Tmp.Z = Z * cosf(Radian) - Y * sinf(Radian);
		Tmp.Y = Z * sinf(Radian) + Y * cosf(Radian);

		return Tmp;
	}
	float4 GetRotateY(const float _Angle) const
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		Tmp.X = X * cosf(Radian) - Z * sinf(Radian);
		Tmp.Z = X * sinf(Radian) + Z * cosf(Radian);

		return Tmp;
	}
	float4 GetRotateZ(const float _Angle) const
	{
		float Radian = _Angle * GameEngineMath::D2R;
		float4 Tmp{ *this };

		Tmp.X = X * cosf(Radian) - Y * sinf(Radian);
		Tmp.Y = -(X * sinf(Radian) + Y * cosf(Radian));

		return Tmp;
	}

	void Cross3D(const float4& _Left, const float4& _Right)
	{
		X = _Left.Y * _Right.Z - _Left.Z * _Right.Y;
		Y = _Left.Z * _Right.X - _Left.X * _Right.Z;
		Z = _Left.X * _Right.Y - _Left.Y * _Right.X;
	}
public:
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

	float4 operator+(const float4& _Ref) const
	{
		float4 Tmp{ *this };

		Tmp.X += _Ref.X;
		Tmp.Y += _Ref.Y;
		Tmp.Z += _Ref.Z;

		return Tmp;
	}
	float4 operator-(const float4& _Ref) const
	{
		float4 Tmp{ *this };

		Tmp.X -= _Ref.X;
		Tmp.Y -= _Ref.Y;
		Tmp.Z -= _Ref.Z;

		return Tmp;
	}
	float4 operator*(const float4& _Ref) const
	{
		float4 Tmp{ *this };

		Tmp.X *= _Ref.X;
		Tmp.Y *= _Ref.Y;
		Tmp.Z *= _Ref.Z;

		return Tmp;
	}
public:
	float4()
		: X(0.0f), Y(0.0f), Z(0.0f), W(1.0f)
	{}
	float4(const float _X)
		: X(_X), Y(0.0f), Z(0.0f), W(1.0f)
	{}
	float4(const float _X, const float _Y)
		: X(_X), Y(_Y), Z(0.0f), W(1.0f)
	{}
	float4(const float _X, const float _Y, const float _Z)
		: X(_X), Y(_Y), Z(_Z), W(1.0f)
	{}
	float4(const float _X, const float _Y, const float _Z, const float _W)
		: X(_X), Y(_Y), Z(_Z), W(_W)
	{}
	float4(const float4& _Ref)
		: X(_Ref.X), Y(_Ref.Y), Z(_Ref.Z), W(_Ref.W)
	{}
	float4(float4&& _Rvalue) noexcept
		: X(_Rvalue.X), Y(_Rvalue.Y), Z(_Rvalue.Z), W(_Rvalue.W)
	{
		_Rvalue.X = 0.0f;
		_Rvalue.Y = 0.0f;
		_Rvalue.Z = 0.0f;
		_Rvalue.W = 1.0f;
	}
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
		_Rvalue.X = 0.0f;
		_Rvalue.Y = 0.0f;
		_Rvalue.Z = 0.0f;
		_Rvalue.W = 1.0f;
	}
};