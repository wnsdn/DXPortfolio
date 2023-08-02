#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEnginePlatform/GameEngineText.h>

void ContentsCore::Start()
{
}

void ContentsCore::Update(const float _Delta)
{
	GameEngineCore::GetWindow().ClearBackBuffer();
	HDC MemDc = GameEngineCore::GetWindow().GetMemDc();

	int VecSize = sizeof(float4);
	int MatSize = sizeof(float4x4);

	float4 Vertex[4]
	{
		{-0.5f, 0.5f},
		{0.5f, 0.5f},
		{0.5f, -0.5f},
		{-0.5f, -0.5f}
	};

	int Idx[2][3]{ {0, 1, 2}, {0, 2, 3} };

	float4x4 Scale4x4{};
	Scale4x4.Scale({ 100.0f, 100.0f });
	float4x4 Roll4x4{};
	Roll4x4.Roll(30.0f);
	float4x4 Yaw4x4{};
	Yaw4x4.Yaw(0.0f);
	float4x4 Pitch4x4{};
	Pitch4x4.Pitch(0.0f);
	float4x4 Translation4x4{};
	Translation4x4.Translation({ 100.0f, 100.0f });

	float4 CamDir{ float4::Front };

	for (int i = 0; i < 2; ++i)
	{
		POINT Tri[3]{};
		for (int j = 0; j < 3; ++j)
		{
			float4 Temp = Vertex[Idx[i][j]];

			Temp *= Scale4x4 * Roll4x4 * Yaw4x4 * Pitch4x4 * Translation4x4;

			Tri[j] = Temp.ToPoint();
		}

		Polygon(MemDc, Tri, 3);
	}

	/*float4 Front[4]
	{
		{ -0.5f, 0.5f, -0.5f, 1.0f },
		{ 0.5f, 0.5f, -0.5f, 1.0f },
		{ 0.5f, -0.5f, -0.5f, 1.0f },
		{ -0.5f, -0.5f, -0.5f, 1.0f }
	};

	float4 Vertex[24]
	{
		Front[0],
		Front[1],
		Front[2],
		Front[3],
		Front[0].RotateYReturn(180.0f),
		Front[1].RotateYReturn(180.0f),
		Front[2].RotateYReturn(180.0f),
		Front[3].RotateYReturn(180.0f),

		Front[0].RotateYReturn(90.0f),
		Front[1].RotateYReturn(90.0f),
		Front[2].RotateYReturn(90.0f),
		Front[3].RotateYReturn(90.0f),
		Front[0].RotateYReturn(-90.0f),
		Front[1].RotateYReturn(-90.0f),
		Front[2].RotateYReturn(-90.0f),
		Front[3].RotateYReturn(-90.0f),

		Front[0].RotateXReturn(90.0f),
		Front[1].RotateXReturn(90.0f),
		Front[2].RotateXReturn(90.0f),
		Front[3].RotateXReturn(90.0f),
		Front[0].RotateXReturn(-90.0f),
		Front[1].RotateXReturn(-90.0f),
		Front[2].RotateXReturn(-90.0f),
		Front[3].RotateXReturn(-90.0f),
	};

	int Idx[6]{ 0, 1, 2, 2, 3, 0 };

	static float4 Scale{100.0f, 100.0f, 100.0f};
	static float4 Rotation{};
	static float4 Position{};

	float CamSpeed = 300.0f;
	if (GameEngineInput::IsPress('A'))
	{
		Position += float4::Left * _Delta * CamSpeed;
	}
	else if (GameEngineInput::IsPress('D'))
	{
		Position += float4::Right * _Delta * CamSpeed;
	}
	if (GameEngineInput::IsPress('W'))
	{
		Position += float4::Up * _Delta * CamSpeed;
	}
	else if (GameEngineInput::IsPress('S'))
	{
		Position += float4::Down * _Delta * CamSpeed;
	}
	if (GameEngineInput::IsPress('Q'))
	{
		Rotation.Z += 360.0f * _Delta / 4.0f;
	}
	else if (GameEngineInput::IsPress('E'))
	{
		Rotation.Z -= 360.0f * _Delta / 4.0f;
	}

	float4x4 Scale4x4{};
	float4x4 Rotation4x4{};
	float4x4 Rotation4x4X{};
	float4x4 Rotation4x4Y{};
	float4x4 Rotation4x4Z{};
	float4x4 Position4x4{};
	Scale4x4.Scale(Scale);
	Rotation4x4X.RotateX(Rotation.X);
	Rotation4x4Y.RotateY(Rotation.Y);
	Rotation4x4Z.RotateZ(Rotation.Z);
	Rotation4x4 = Rotation4x4X * Rotation4x4Y * Rotation4x4Z;
	Position4x4.Position(Position);
	float4x4 World4x4{ Scale4x4 * Rotation4x4 * Position4x4 };//월드 행렬

	static float4 EyePos{0.0f, 0.0f, -500.0f};
	static float4 EyeFront{0.0f, 0.0f, 1.0f};
	static float4 EyeUp{0.0f, 1.0f, 0.0f};
	float MoveSpeed = 300.0f;
	if (GameEngineInput::IsPress(VK_LEFT))
	{
		EyePos += float4::Left * _Delta * MoveSpeed;
	}
	else if (GameEngineInput::IsPress(VK_RIGHT))
	{
		EyePos += float4::Right * _Delta * MoveSpeed;
	}
	if (GameEngineInput::IsPress(VK_UP))
	{
		EyePos += float4::Front * _Delta * MoveSpeed;
	}
	else if (GameEngineInput::IsPress(VK_DOWN))
	{
		EyePos += float4::Back * _Delta * MoveSpeed;
	}
	if (GameEngineInput::IsPress('I'))
	{
		EyeFront.RotateY(360.0f * _Delta);
	}
	else if (GameEngineInput::IsPress('O'))
	{
		EyeFront.RotateY(-360.0f * _Delta);
	}

	float4x4 View4x4{};
	View4x4.LookAtLH(EyePos, EyeFront, EyeUp);//뷰 행렬

	float4x4 Projection4x4{};
	static float Zoom = 1.0f;
	//Projection4x4.OrthographicLH(GetWndScalef().X * Zoom, GetWndScalef().Y * Zoom, 1000.0f, 0.1f);
	Projection4x4.PerspectiveFovLH(60.0f, GetWndScalef().X, GetWndScalef().Y, 1000.0f, 0.1f);
	//프로젝션 행렬

	float4x4 ViewPort4x4{};
	ViewPort4x4.ViewPort(GetWndScalef().X, GetWndScalef().Y, 0.0f, 0.0f);//뷰포트 행렬

	for (int i = 0; i < 6; ++i)
	{
		POINT Tri[3]{};
		float4 fTri[3]{};
		for (int j = 0; j < 2; ++j)
		{
			for (int k = 0; k < 3; ++k)
			{
				float4 WorldPoint{ Vertex[4 * i + Idx[j * 3 + k]] };

				WorldPoint *= World4x4 * View4x4 *Projection4x4;

				WorldPoint /= WorldPoint.W;
				WorldPoint.W = 1.0f;

				WorldPoint *= ViewPort4x4;

				fTri[k] = WorldPoint;
				Tri[k] = WorldPoint.ToPoint();
			}

			if (float4::Cross3D(fTri[0] - fTri[1], fTri[2] - fTri[1]).Z >= 0.0f)
			{
				continue;
			}
			Polygon(MemDc, Tri, 3);
		}
	}*/

	GameEngineCore::GetWindow().DoubleBuffering();
}

void ContentsCore::Release()
{
}
