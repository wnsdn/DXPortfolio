#pragma once

class int4;
class float4
{
public:
	static const float4 Left;
	static const float4 Right;
	static const float4 Up;
	static const float4 Down;

	float X = 0.0f;
	float Y = 0.0f;
public:
	float4 Half() const
	{
		return { X / 2.0f, Y / 2.0f };
	}
	int4 ToInt4() const;
public:
	float4()
		: X(0.0f), Y(0.0f)
	{
	}
	float4(const float _X, const float _Y)
		: X(_X), Y(_Y)
	{
	}
	float4(const float4& _Ref)
		: X(_Ref.X), Y(_Ref.Y)
	{
	}
	void operator=(const float4& _Ref)
	{
		X = _Ref.X;
		Y = _Ref.Y;
	}
	float4(float4&& _Rvalue) noexcept = delete;
	void operator=(float4&& _Rvalue) noexcept = delete;
};

class int4
{
public:
	static const int4 Left;
	static const int4 Right;
	static const int4 Up;
	static const int4 Down;

	int X = 0;
	int Y = 0;
public:
	int4 Half() const
	{
		return { X / 2, Y / 2 };
	}
	float4 ToFloat4() const;
public:
	int4()
		: X(0), Y(0)
	{
	}
	int4(const int _X, const int _Y)
		: X(_X), Y(_Y)
	{
	}
	int4(const int4& _Ref)
		: X(_Ref.X), Y(_Ref.Y)
	{
	}
	void operator=(const int4& _Ref)
	{
		X = _Ref.X;
		Y = _Ref.Y;
	}
	int4(int4&& _Rvalue) noexcept = delete;
	void operator=(int4&& _Rvalue) noexcept = delete;
};