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

	static float4 Scale{100.0f, 100.0f, 100.0f};
	static float4 Rotation{0.0f, 0.0f, 0.0f};
	static float4 Position{200.0f, 200.0f, 200.0f};

	float4x4 Scale4x4{};
	float4x4 Rotation4x4{};
	float4x4 Rotation4x4X{};
	float4x4 Rotation4x4Y{};
	float4x4 Rotation4x4Z{};
	float4x4 Position4x4{};

	Scale4x4.Scale(Scale);

	if (GameEngineInput::IsPress('Q'))
	{
		Rotation.X += 360.0f * _Delta / 4.0f;
	}
	else if (GameEngineInput::IsPress('W'))
	{
		Rotation.X -= 360.0f * _Delta / 4.0f;
	}
	if (GameEngineInput::IsPress('A'))
	{
		Rotation.Y += 360.0f * _Delta / 4.0f;
	}
	else if (GameEngineInput::IsPress('S'))
	{
		Rotation.Y -= 360.0f * _Delta / 4.0f;
	}
	if (GameEngineInput::IsPress('Z'))
	{
		Rotation.Z += 360.0f * _Delta / 4.0f;
	}
	else if (GameEngineInput::IsPress('X'))
	{
		Rotation.Z -= 360.0f * _Delta / 4.0f;
	}
	Rotation4x4X.RotateX(Rotation.X);
	Rotation4x4Y.RotateY(Rotation.Y);
	Rotation4x4Z.RotateZ(Rotation.Z);
	Rotation4x4 = Rotation4x4X * Rotation4x4Y * Rotation4x4Z;

	Position4x4.Position(Position);

	float4x4 World4x4 = Scale4x4 * Rotation4x4 * Position4x4;

	float4 Vertex[4]
	{
		{-0.5f, -0.5f, -0.5f},
		{0.5f, -0.5f, -0.5f},
		{0.5f, 0.5f, -0.5f},
		{-0.5f, 0.5f, -0.5f},
	};

	int Idx[2][3] = { {0, 1, 2}, {2, 3, 0} };

	POINT Tri[3]{};
	float4 fTri[3]{};
	for (int i = 0; i < 2; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			float4 WorldPoint = Vertex[Idx[i][j]];

			WorldPoint *= World4x4;

			Tri[j] = WorldPoint.ToPoint();
			fTri[j] = WorldPoint;
		}

		float4 Cross{};
		Cross.Cross3D(fTri[0] - fTri[1], fTri[2] - fTri[1]);
		GameEngineText::FormatTextOut(MemDc, "z: ", 5, i * 20 + 5, Cross.Z);

		if (Cross.Z > 0)
		{
			continue;
		}
		Polygon(MemDc, Tri, 3);
	}

	GameEngineCore::GetWindow().DoubleBuffering();
}

void ContentsCore::Release()
{
}
