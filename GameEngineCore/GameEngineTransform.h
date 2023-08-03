#pragma once
#include <GameEngineBase/GameEngineMath.h>

class TransformData
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

	float4 ScaleMatrix;
	float4 RotationMatrix;
	float4 PositionMatrix;
	float4 LocalMatrix;
	float4 WorldMatrix;
	float4 View;
	float4 Projection;
	float4 ViewPort;
	float4 WorldViewProjectionMatrix;
};

class GameEngineTransform
{
private:
	TransformData TransData;
public:
	GameEngineTransform() {}
	~GameEngineTransform() {}
	GameEngineTransform(const GameEngineTransform& _Other) = delete;
	GameEngineTransform(GameEngineTransform&& _Other) noexcept = delete;
	GameEngineTransform& operator=(const GameEngineTransform& _Other) = delete;
	GameEngineTransform& operator=(GameEngineTransform&& _Other) noexcept = delete;
};