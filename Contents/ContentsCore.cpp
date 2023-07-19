#include "PreCompile.h"
#include "ContentsCore.h"

void ContentsCore::Start()
{
}

void ContentsCore::Update(const float _Delta)
{
	GameEngineCore::GetWindow().ClearBackBuffer();
	HDC MemDc = GameEngineCore::GetWindow().GetMemDc();

	static const int Num = 8;
	static float4 Scale{100, 100, 100};
	static float4 Rotation{0, 0, 0};
	static float4 Position{100, 100, 100};

	if (GameEngineInput::IsPress('Q'))
	{
		Rotation.X += 360.0f * _Delta / 4.0f;
	}
	if (GameEngineInput::IsPress('W'))
	{
		Rotation.Y += 360.0f * _Delta / 4.0f;
	}
	if (GameEngineInput::IsPress('E'))
	{
		Rotation.Z += 360.0f * _Delta / 4.0f;
	}
	if (GameEngineInput::IsPress(VK_RIGHT))
	{
		Position.X += 50.0f * _Delta;
	}

	std::vector<float4> Vertex;
	Vertex.resize(Num);
	Vertex[0] = { -0.5f, -0.5f, -0.5f };
	Vertex[1] = { 0.5f, -0.5f, -0.5f };
	Vertex[2] = { 0.5f, 0.5f, -0.5f };
	Vertex[3] = { -0.5f, 0.5f, -0.5f };

	Vertex[4] = { -0.5f, -0.5f, 0.5f };
	Vertex[5] = { 0.5f, -0.5f, 0.5f };
	Vertex[6] = { 0.5f, 0.5f, 0.5f };
	Vertex[7] = { -0.5f, 0.5f, 0.5f };

	std::vector<POINT> WinPoint;
	WinPoint.resize(Num);
	for (size_t i = 0; i < Num; ++i)
	{
		float4 WorldPoint = Vertex[i];

		WorldPoint *= Scale;
		WorldPoint.RotateX(Rotation.X);
		WorldPoint.RotateY(Rotation.Y);
		WorldPoint.RotateZ(Rotation.Z);
		WorldPoint += Position;
		WinPoint[i] = WorldPoint.ToPoint();
	}

	POINT Tmp[4][3] = {
		{WinPoint[0], WinPoint[1], WinPoint[2]},
	{ WinPoint[0], WinPoint[2], WinPoint[3] },
	{ WinPoint[4], WinPoint[5], WinPoint[6] },
	{ WinPoint[4], WinPoint[6], WinPoint[7] }
	};

	for (int i = 0; i < 4; ++i)
	{
		Polygon(MemDc, &Tmp[i][0], 3);
	}

	GameEngineCore::GetWindow().DoubleBuffering();
}

void ContentsCore::Release()
{
}
