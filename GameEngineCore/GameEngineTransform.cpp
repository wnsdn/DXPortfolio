#include "PreCompile.h"
#include "GameEngineTransform.h"

std::function<bool(const CollisionParameter& _Data)> ArrColFunction[static_cast<int>(ColType::MAX)][static_cast<int>(ColType::MAX)];

class InitColFunction
{
public:
	InitColFunction()
	{
		for (size_t Left = 0; Left < static_cast<size_t>(ColType::MAX); Left++)
		{
			for (size_t Right = 0; Right < static_cast<size_t>(ColType::MAX); Right++)
			{
				ArrColFunction[Left][Right] = [](const CollisionParameter& _Data)
					{
						MsgBoxAssert("아직 처리되지 않은 함수입니다.");
						return false;
					};
			}
		}

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.ColData.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingBox Right = _Data.Right.ColData.AABB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.ColData.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.ColData.SPHERE;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::AABBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingBox Left = _Data.Left.ColData.AABB;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.ColData.OBB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.ColData.SPHERE;
				Left.Center.z = 0.0f;
				DirectX::BoundingBox Right = _Data.Right.ColData.AABB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.ColData.SPHERE;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.ColData.SPHERE;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::SPHERE2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingSphere Left = _Data.Left.ColData.SPHERE;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.ColData.OBB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};


		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::AABBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.ColData.OBB;
				Left.Center.z = 0.0f;
				DirectX::BoundingBox Right = _Data.Right.ColData.AABB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::SPHERE2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.ColData.OBB;
				Left.Center.z = 0.0f;
				DirectX::BoundingSphere Right = _Data.Right.ColData.SPHERE;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};

		ArrColFunction[static_cast<int>(ColType::OBBBOX2D)][static_cast<int>(ColType::OBBBOX2D)] = [](const CollisionParameter& _Data)
			{
				DirectX::BoundingOrientedBox Left = _Data.Left.ColData.OBB;
				Left.Center.z = 0.0f;
				DirectX::BoundingOrientedBox Right = _Data.Right.ColData.OBB;
				Right.Center.z = 0.0f;
				return Left.Intersects(Right);
			};
	}
};

InitColFunction Inst;

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

	TransData.WorldMatrix.Decompose(TransData.WorldScale, TransData.WorldQuaternion, TransData.WorldPosition);
	TransData.WorldRotation = TransData.WorldQuaternion.QuaternionToEuler();

	TransData.LocalWorldMatrix.Decompose(TransData.LocalScale, TransData.LocalQuaternion, TransData.LocalPosition);
	TransData.LocalRotation = TransData.WorldQuaternion.QuaternionToEuler();

	ColData.OBB.Extents = TransData.WorldScale.ToAbs().Half().Float3;
	ColData.OBB.Center = TransData.WorldPosition.Float3;
	ColData.OBB.Orientation = TransData.WorldQuaternion.Float4;

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

bool GameEngineTransform::Collision(const CollisionParameter& _Data)
{
	return ArrColFunction[_Data.GetLeftTypeToInt()][_Data.GetRightTypeToInt()](_Data);
}
