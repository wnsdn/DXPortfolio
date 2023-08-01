#pragma once

class float4;
class float4x4
{
public:
	union
	{
		float Arr1D[16]{};
		float Arr2D[4][4];
	};
public:
	void Reset();
	void Identity();
	void Scale(const float4& _Value);
	void Position(const float4& _Value);

	void RotateX(float _Angle);
	void RotateY(float _Angle);
	void RotateZ(float _Angle);
	float4x4 RotateXReturn(float _Angle);
	float4x4 RotateYReturn(float _Angle);
	float4x4 RotateZReturn(float _Angle);

	void InsertVector(int _Idx, int _size, const float4& _Ref);
	void Transpose();
	void LookAtLH(const float4& _EyePos, const float4& _EyeFront, const float4& _EyeUp);
	void OrthographicLH(float _Width, float _Height, float _Far, float _Near);
	void PerspectiveFovLH(float _FovAngle, float _Width, float _Height, float _Far, float _Near);
	void ViewPort(float _Width, float _Height, float _Left, float _Right,
		float _ZMin = 0.0f, float _ZMax = 1.0f);
public:
	void operator*=(const float4x4& _Ref);
	float4x4 operator*(const float4x4& _Ref) const;
public:
	float4x4();
	float4x4(const float4x4& _Ref);
	float4x4(float4x4&& _Rvalue) noexcept;
	void operator=(const float4x4& _Ref) = delete;
	void operator=(float4x4&& _Rvalue) noexcept;
};