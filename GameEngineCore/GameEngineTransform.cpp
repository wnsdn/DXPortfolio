#include "PreCompile.h"
#include "GameEngineTransform.h"

void GameEngineTransform::TransformUpdate()
{
	TransData.LocalCalculation();
	TransData.WorldMatrix = TransData.LocalWorldMatrix;

	if (Parent)
	{
		TransData.ParentMatrix = Parent->TransData.WorldMatrix;
		TransData.WorldMatrix = TransData.LocalWorldMatrix * TransData.ParentMatrix;
	}
}
