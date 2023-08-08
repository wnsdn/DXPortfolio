#include "PreCompile.h"
#include "GameEngineRenderer.h"

#include "GameEngineCamera.h"
#include "GameEngineLevel.h"

void GameEngineRenderer::Start()
{
	SetViewCameraSelect(0);
}

void GameEngineRenderer::Render(float _Delta)
{
	//HDC MemDc = GameEngineWindow::GetInst().GetMemDc();

	//float4 Vertex[]
	//{
	//	{ -0.5f, 0.5f, -0.5f },
	//	{ 0.5f, 0.5f, -0.5f },
	//	{ 0.5f, 0.5f, 0.5f },
	//	{ -0.5f, 0.5f, 0.5f },
	//	{ -0.5f, -0.5f, -0.5f },
	//	{ 0.5f, -0.5f, -0.5f },
	//	{ 0.5f, -0.5f, 0.5f },
	//	{ -0.5f, -0.5f, 0.5f }
	//};
	//int Idx[12][3]
	//{
	//	0, 1, 5, 5, 4, 0,
	//	1, 2, 6, 6, 5, 1,
	//	2, 3, 7, 7, 6, 2,
	//	3, 0, 4, 4, 7, 3,
	//	3, 2, 1, 1, 0, 3,
	//	4, 5, 6, 6, 7, 4
	//};

	//TransformData& Temp = Transform.GetTransformDataRef();
	//Temp.ScaleMatrix.Scale({ 100.0f, 100.0f, 100.0f, 1.0f });
	//Temp.RotationMatrix.Rotate({ 0.0f, 0.0f, 0.0f, 1.0f });
	//Temp.PositionMatrix.Translation({ 0.0f, 0.0f, 0.0f, 1.0f });
	//Temp.WorldMatrix = Temp.ScaleMatrix * Temp.RotationMatrix * Temp.PositionMatrix;

	//float X = static_cast<float>(GameEngineWindow::GetInst().GetScale().x);
	//float Y = static_cast<float>(GameEngineWindow::GetInst().GetScale().y);
	//Temp.Projection.Perspective(60.0f, X, Y, 1000.0f, 0.1f);
	//Temp.ViewPort.ViewPort(X, Y);

	//for (int i = 0; i < 12; ++i)
	//{
	//	POINT Tri[3]{};
	//	float4 fTri[3]{};
	//	for (int j = 0; j < 3; ++j)
	//	{
	//		float4 MVP = Vertex[Idx[i][j]];
	//		MVP *= Temp.WorldMatrix;
	//		MVP *= GetLevel()->GetMainCamera()->Transform.GetTransformDataRef().View;
	//		MVP *= Temp.Projection;
	//		//MVP /= MVP.W;
	//		MVP.W = 1.0f;
	//		MVP *= Temp.ViewPort;

	//		Tri[j] = MVP;
	//		fTri[j] = MVP;
	//	}

	//	//float4 V1 = fTri[0] - fTri[1];
	//	//float4 V2 = fTri[2] - fTri[1];
	//	//float4 Cross = float4::Cross(V1, V2);

	//	//if (Cross.Z >= 0.0f)
	//	{
	//		continue;
	//	}

	//	Polygon(MemDc, Tri, 3);
	//}

	//GameEngineText::FormatTextOut(MemDc, "x:", 10, 10, GetLevel()->GetMainCamera()->Transform.GetTransformDataRef().Position.X);
	//GameEngineText::FormatTextOut(MemDc, "y:", 10, 30, GetLevel()->GetMainCamera()->Transform.GetTransformDataRef().Position.Y);
	//GameEngineText::FormatTextOut(MemDc, "z:", 10, 50, GetLevel()->GetMainCamera()->Transform.GetTransformDataRef().Position.Z);


	HDC MemDc = GameEngineWindow::GetInst().GetMemDc();

	float4 Vertex[4]
	{
		{-0.5f, -0.5f, 0.0f, 1.0f},
		{0.5f, -0.5f, 0.0f, 1.0f},
		{0.5f, 0.5f, 0.0f, 1.0f},
		{-0.5f, 0.5f, 0.0f, 1.0f}
	};

	static float Degree = 0.0f;
	Degree += 360.0f * _Delta;
	for (int i = 0; i < 4; ++i)
	{
		Vertex[i] *= 100.0f;

		Vertex[i].RotateZ(Degree);

		Vertex[i].X += 100.0f;
		Vertex[i].Y += 100.0f;
	}

	POINT Tri[4]{Vertex[0], Vertex[1], Vertex[2], Vertex[3]};

	Polygon(MemDc, Tri, 4);
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();
	std::shared_ptr<GameEngineCamera> Camera = Level->GetCamera(_Order);

	if (!Camera)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	Camera->Renderers[_Order].emplace_back(GetDynamic_Cast_This<GameEngineRenderer>());
	ViewInfo[Camera.get()] = _Order;
}
