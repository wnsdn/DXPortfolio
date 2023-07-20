#include "PreCompile.h"
#include "ContentsCore.h"

void ContentsCore::Start()
{
}

void ContentsCore::Update(const float _Delta)
{
	GameEngineCore::GetWindow().ClearBackBuffer();
	HDC MemDc = GameEngineCore::GetWindow().GetMemDc();

	static float4 Scale{100, 100, 100};
	static float4 Rotation{0, 0, 0};
	static float4 Position{100, 100, 100};

	if (GameEngineInput::IsPress('Q'))
	{
		Rotation.X += 360.0f * _Delta / 4.0f;
	}
	//else if (GameEngineInput::IsPress('W'))
	{
		Rotation.X += -360.0f * _Delta / 4.0f;
	}

	if (GameEngineInput::IsPress('A'))
	{
		Rotation.Y += 360.0f * _Delta / 4.0f;
	}
	//else if (GameEngineInput::IsPress('S'))
	{
		Rotation.Y += -360.0f * _Delta / 4.0f;
	}

	if (GameEngineInput::IsPress('Z'))
	{
		Rotation.Z += -360.0f * _Delta / 4.0f;
	}
	//else if (GameEngineInput::IsPress('X'))
	{
		Rotation.Z += 360.0f * _Delta / 4.0f;
	}

	std::vector<float4> Vertex;
	Vertex.resize(8);
	Vertex[0] = { -0.5f, -0.5f, -0.5f };
	Vertex[1] = { 0.5f, -0.5f, -0.5f };
	Vertex[2] = { 0.5f, 0.5f, -0.5f };
	Vertex[3] = { -0.5f, 0.5f, -0.5f };

	Vertex[4] = { -0.5f, -0.5f, 0.5f };
	Vertex[5] = { 0.5f, -0.5f, 0.5f };
	Vertex[6] = { 0.5f, 0.5f, 0.5f };
	Vertex[7] = { -0.5f, 0.5f, 0.5f };

	const int TriNum = 12;
	int Idx[TriNum][3] =
	{
		{0, 1, 2},
		{0, 2, 3},
		{4, 5, 7},
		{5, 6, 7},
		{4, 0, 3},
		{4, 3, 7},
		{1, 5, 6},
		{1, 6, 2},
		{0, 1, 4},
		{1, 4, 5},
		{2, 3, 6},
		{3, 6, 7}
	};

	std::vector<POINT> Tri;
	Tri.resize(3);
	for (int i = 0; i < TriNum; ++i)
	{
		for (int j = 0; j < 3; ++j)
		{
			float4 WorldPoint = Vertex[Idx[i][j]];

			WorldPoint *= Scale;
			WorldPoint.RotateX(Rotation.X);
			WorldPoint.RotateY(Rotation.Y);
			WorldPoint.RotateZ(Rotation.Z);
			WorldPoint += Position;

			Tri[j] = WorldPoint.ToPoint();
		}

		HBRUSH Hbr = static_cast<HBRUSH>(GetStockObject(NULL_BRUSH));
		HBRUSH Obr = static_cast<HBRUSH>(SelectObject(MemDc, Hbr));

		Polygon(MemDc, &Tri[0], 3);

		SelectObject(MemDc, Obr);

		if (Hbr)
		{
			DeleteObject(Hbr);
			Hbr = nullptr;
		}
		if (Obr)
		{
			DeleteObject(Obr);
			Obr = nullptr;
		}
	}

	static float4 Pos{ 200, 200 };

	if (GameEngineInput::IsDown(VK_RIGHT))
	{
		Pos.X += 10.0f;
	}
	if (GameEngineInput::IsUp(VK_UP))
	{
		Pos.Y += 10.0f;
	}
	if (GameEngineInput::IsPress(VK_LEFT))
	{
		Pos.X -= 100.0f * _Delta;
	}

	float4 A[3]{};
	A[0] = { 0, -0.5 };
	A[1] = { -0.25, 0.25 };
	A[2] = { 0.25, 0.25 };

	for (int i = 0; i < 3; ++i)
	{
		float4 WorldPoint{ std::move(A[i]) };

		WorldPoint *= Scale;
		WorldPoint += Pos;
		Tri[i] = WorldPoint.ToPoint();
	}

	Polygon(MemDc, &Tri[0], 3);

	GameEngineCore::GetWindow().DoubleBuffering();
}

void ContentsCore::Release()
{
}
