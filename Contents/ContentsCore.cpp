#include "PreCompile.h"
#include "ContentsCore.h"

void ContentsCore::Start()
{
}

void ContentsCore::Update(const float _Delta)
{
	GameEngineCore::GetWindow().ClearBackBuffer();
	HDC MemDc = GameEngineCore::GetWindow().GetMemDc();

	static const int Num = 4;
	static float4 Scale{100, 100};
	static float4 Rotation{0, 0, 0};
	static float4 Position{100, 100};

	if (GameEngineInput::IsPress(VK_SPACE))
	{
		Rotation.Z += 360.0f * _Delta;
	}
	if (GameEngineInput::IsPress(VK_RIGHT))
	{
		Position.X += 50.0f * _Delta;
	}

	std::vector<float4> Vertex;
	Vertex.resize(Num);
	Vertex[0] = { -0.5f, -0.5f };
	Vertex[1] = { 0.5f, -0.5f };
	Vertex[2] = { 0.5f, 0.5f };
	Vertex[3] = { -0.5f, 0.5f };

	std::vector<POINT> WinPoint;
	WinPoint.resize(Num);
	for (size_t i = 0; i < Num; ++i)
	{
		float4 WorldPoint = Vertex[i];

		WorldPoint *= Scale;
		WorldPoint.Rotate(Rotation.Z);
		WorldPoint += Position;
		WinPoint[i] = WorldPoint.ToPoint();
	}
	Polygon(MemDc, &WinPoint[0], Num);

	GameEngineCore::GetWindow().DoubleBuffering();
}

void ContentsCore::Release()
{
}
