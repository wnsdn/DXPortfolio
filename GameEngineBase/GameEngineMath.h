#pragma once

template <typename DataType>
class Point4
{
public:
	static const Point4<DataType> Left;
	static const Point4<DataType> Right;
	static const Point4<DataType> Up;
	static const Point4<DataType> Down;

	DataType X = 0;
	DataType Y = 0;
public:
	Point4<DataType> Half() const
	{
		return Point4<DataType>(X / 2, Y / 2);
	}
	template <typename ToType>
	Point4<ToType> To() const
	{
		return Point4<ToType>(static_cast<ToType>(X), static_cast<ToType>(Y));
	}
public:
	Point4()
		: X(0), Y(0)
	{}
	Point4(const DataType _X, const DataType _Y)
		: X(_X), Y(_Y)
	{}
	Point4(const Point4<DataType>& _Ref)
		: X(_Ref.X), Y(_Ref.Y)
	{}
	Point4(Point4<DataType>&& _Ref) noexcept
		: X(_Ref.X), Y(_Ref.Y)
	{}
	void operator=(const Point4<DataType>& _Ref)
	{
		X = _Ref.X;
		Y = _Ref.Y;
	}
	void operator=(Point4<DataType>&& _Ref) noexcept
	{
		X = _Ref.X;
		Y = _Ref.Y;
	}
};
