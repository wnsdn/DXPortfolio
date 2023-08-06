#pragma once
#include <GameEngineBase/GameEngineMath.h>

struct TransformData
{
	float4 Scale;
	float4 Rotation;
	float4 Position;

	float4 LocalScale;
	float4 LocalRotation;
	float4 LocalPosition;

	float4 WorldScale;
	float4 WorldRotation;
	float4 WorldPosition;

	float4x4 ScaleMatrix;
	float4x4 RotationMatrix;
	float4x4 PositionMatrix;
	float4x4 RevolutionMatrix;
	float4x4 ParentMatrix;

	float4x4 LocalWorldMatrix;
	float4x4 WorldMatrix;

	float4x4 View;
	float4x4 Projection;
	float4x4 ViewPort;

	float4x4 WorldViewProjectionMatrix;

	void LocalCalculation()
	{
		ScaleMatrix.Scale(Scale);
		RotationMatrix.Rotate(Rotation);
		PositionMatrix.Translation(Position);

		LocalWorldMatrix = ScaleMatrix * RotationMatrix * PositionMatrix * RevolutionMatrix;
	}
};

class GameEngineTransform
{
private:
	GameEngineTransform* Parent = nullptr;
	TransformData TransData;
public:
	void LookToLH(const float4& _Deg, const float4& _Pos)
	{
		TransData.View.View(_Deg, _Pos);
	}

	void TransformUpdate();

	TransformData& GetTransformDataRef()
	{
		return TransData;
	}
	void SetLocalPosition(const float4& _Value)
	{
		TransData.Position = _Value;
		TransformUpdate();
	}
	float4 GetWorldPosition()
	{
		return TransData.WorldMatrix.RowVec[3];
	}
	float4 GetWorldFrontVector()
	{
		return TransData.WorldMatrix.RowVec[2].NormalizeReturn();
	}
	float4 GetWorldBackVector()
	{
		return -TransData.WorldMatrix.RowVec[2].NormalizeReturn();
	}
	float4 GetWorldRightVector()
	{
		return TransData.WorldMatrix.RowVec[0].NormalizeReturn();
	}
	float4 GetWorldLeftVector()
	{
		return -TransData.WorldMatrix.RowVec[0].NormalizeReturn();
	}
	float4 GetWorldUpVector()
	{
		return TransData.WorldMatrix.RowVec[1].NormalizeReturn();
	}
	float4 GetWorldDownVector()
	{
		return -TransData.WorldMatrix.RowVec[1].NormalizeReturn();
	}
	void SetParent(GameEngineTransform& _Parent)
	{
		Parent = &_Parent;
	}

	GameEngineTransform() {}
	~GameEngineTransform() {}
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;
};