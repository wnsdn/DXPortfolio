#pragma once
#include <GameEngineBase/GameEngineMath.h>

struct TransformData
{
	float4 Scale{ float4::OneNull };
	float4 Rotation{ float4::ZeroNull };
	float4 Position{ float4::Zero };

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

	float4x4 ViewMatrix;
	float4x4 ProjectionMatrix;
	float4x4 Viewport;

	float4x4 WorldViewProjectionMatrix;

	void LocalCalculation()
	{
		ScaleMatrix.Scaling(Scale);
		RotationMatrix.Rotation(Rotation);
		PositionMatrix.Translation(Position);

		LocalWorldMatrix = ScaleMatrix * RotationMatrix * PositionMatrix * RevolutionMatrix;
	}

	void WorldViewProjectionCalculation()
	{
		WorldViewProjectionMatrix = WorldMatrix * ViewMatrix * ProjectionMatrix;
	}
};

class GameEngineTransform
{
private:
	GameEngineTransform* Parent = nullptr;
	std::list<GameEngineTransform*> Childs;
	TransformData TransData;
public:
	void Orthographic(float _Width, float _Height, float _Far, float _Near)
	{
		TransData.ProjectionMatrix.Orthograhpic(_Width, _Height, _Far, _Near);
	}
	void Perspective(float _Fov, float _Width, float _Height, float _Far, float _Near)
	{
		TransData.ProjectionMatrix.Perspective(_Fov, _Width, _Height, _Far, _Near);
	}
	void View(const float4& _EyePos, const float4& _EyeDir, const float4& _UpDir)
	{
		TransData.ViewMatrix.View(_EyePos, _EyeDir, _UpDir);
	}

	void SetLocalScale(const float4& _Value)
	{
		TransData.Scale = _Value;
		TransformUpdate();
	}
	void SetLocalRotation(const float4& _Value)
	{
		TransData.Rotation = _Value;
		TransformUpdate();
	}
	void AddLocalRotation(const float4& _Value)
	{
		TransData.Rotation += _Value;
		TransformUpdate();
	}
	void SetLocalPosition(const float4& _Value)
	{
		TransData.Position = _Value;
		TransformUpdate();
	}
	void AddLocalPosition(const float4& _Value)
	{
		TransData.Position += _Value;
		TransformUpdate();
	}

	const TransformData& GetConstTransformDataRef()
	{
		return TransData;
	}
	float4 GetLocalScale() const
	{
		return TransData.LocalScale;
	}
	float4 GetWorldPosition() const
	{
		return TransData.WorldMatrix.RowVec[3];
	}
	float4x4 GetWorldViewProjectionMatrix() const
	{
		return TransData.WorldViewProjectionMatrix;
	}
	float4 GetWorldFrontVector() const
	{
		return TransData.WorldMatrix.RowVec[2].NormalizeReturn();
	}
	float4 GetWorldBackVector() const
	{
		return -TransData.WorldMatrix.RowVec[2].NormalizeReturn();
	}
	float4 GetWorldRightVector() const
	{
		return TransData.WorldMatrix.RowVec[0].NormalizeReturn();
	}
	float4 GetWorldLeftVector() const
	{
		return -TransData.WorldMatrix.RowVec[0].NormalizeReturn();
	}
	float4 GetWorldUpVector() const
	{
		return TransData.WorldMatrix.RowVec[1].NormalizeReturn();
	}
	float4 GetWorldDownVector() const
	{
		return -TransData.WorldMatrix.RowVec[1].NormalizeReturn();
	}

	void CalculationViewAndProjection(const TransformData& _Transform);
	void CalculationViewAndProjection(const float4x4& _View, const float4x4& _Projection);
	void TransformUpdate();
	void SetParent(GameEngineTransform& _Parent)
	{
		Parent = &_Parent;
		Parent->Childs.push_back(this);
	}
	void CalChilds();

	GameEngineTransform() = default;
	~GameEngineTransform() = default;
	GameEngineTransform(const GameEngineTransform&) = delete;
	GameEngineTransform(GameEngineTransform&&) noexcept = delete;
	void operator=(const GameEngineTransform&) = delete;
	void operator=(GameEngineTransform&&) noexcept = delete;
};