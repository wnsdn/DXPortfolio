//#pragma once
//#include "GameEngineMath.h"
//
//class GameEngineForm
//{
//private:
//	Point4<float> Pos{};
//	Point4<float> Size{};
//	bool PosIsCenter = true;
//public:
//	Point4<float> GetPos() const
//	{
//		return Pos;
//	}
//	template <typename ToType>
//	Point4<ToType> GetPos() const
//	{
//		return Pos.To<ToType>();
//	}
//	void SetPos(const Point4<float>& _Pos)
//	{
//		Pos = _Pos;
//	}
//	Point4<float> GetSize() const
//	{
//		return Size;
//	}
//	template <typename ToType>
//	Point4<ToType> GetSize() const
//	{
//		return Size.To<ToType>();
//	}
//	void SetSize(const Point4<float>& _Size)
//	{
//		Size = _Size;
//	}
//
//	template <typename ToType>
//	ToType Left() const
//	{
//		float Tmp = 0.0f;
//
//		if (PosIsCenter)
//		{
//			Tmp = Pos.X - Size.Half().X;
//		}
//		else
//		{
//			Tmp = Pos.X;
//		}
//
//		return static_cast<ToType>(Tmp);
//	}
//	template <typename ToType>
//	ToType  Right() const
//	{
//		float Tmp = 0.0f;
//
//		if (PosIsCenter)
//		{
//			Tmp = Pos.X + Size.Half().X;
//		}
//		else
//		{
//			Tmp = Pos.X + Size.X;
//		}
//
//		return static_cast<ToType>(Tmp);
//	}
//	template <typename ToType>
//	ToType  Top() const
//	{
//		float Tmp = 0.0f;
//
//		if (PosIsCenter)
//		{
//			Tmp = Pos.Y - Size.Half().Y;
//		}
//		else
//		{
//			Tmp = Pos.Y;
//		}
//
//		return static_cast<ToType>(Tmp);
//	}
//	template <typename ToType>
//	ToType  Bottom() const
//	{
//		float Tmp = 0.0f;
//
//		if (PosIsCenter)
//		{
//			Tmp = Pos.Y + Size.Half().Y;
//		}
//		else
//		{
//			Tmp = Pos.Y + Size.Y;
//		}
//
//		return static_cast<ToType>(Tmp);
//	}
//public:
//	GameEngineForm()
//		: Pos(), Size(), PosIsCenter(true)
//	{}
//	GameEngineForm(const Point4<float>& _Pos, const Point4<float>& _Size, const bool _PosIsCenter)
//		: Pos(_Pos), Size(_Size), PosIsCenter(_PosIsCenter)
//	{}
//	~GameEngineForm() {}
//	GameEngineForm(const GameEngineForm& _Other) = delete;
//	GameEngineForm(GameEngineForm&& _Other) noexcept = delete;
//	void operator=(const GameEngineForm& _Other)
//	{
//		Pos = _Other.Pos;
//		Size = _Other.Size;
//		PosIsCenter = _Other.PosIsCenter;
//	}
//	void operator=(GameEngineForm&& _Other) noexcept = delete;
//};