#include "PreCompile.h"
#include "GameEngineTransform.h"

void GameEngineTransform::CalculationViewAndProjection(const TransformData& _TransData)
{
	CalculationViewAndProjection(_TransData.ViewMatrix, _TransData.ProjectionMatrix);
}

void GameEngineTransform::CalculationViewAndProjection(const float4x4& _View,
	const float4x4& _Projection)
{
	TransData.ViewMatrix = _View;
	TransData.ProjectionMatrix = _Projection;
	TransData.WorldViewProjectionCalculation();
}

void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();
	TransData.WorldMatrix = TransData.LocalWorldMatrix;

	if (Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.LocalWorldMatrix * TransData.ParentMatrix;
	}

	CalChilds();
}

void GameEngineTransform::CalChilds()
{
	if (Childs.empty())
	{
		return;
	}

	for (auto Trans : Childs)
	{
		Trans->TransformUpdate();
	}
}
