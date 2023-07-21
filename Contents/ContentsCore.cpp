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

	std::vector<float4> Vertex(4 * 6);

	float4 BaseVertex[4]{};
	BaseVertex[0] = { -0.5f, -0.5f, -0.5f };
	BaseVertex[1] = { 0.5f, -0.5f, -0.5f };
	BaseVertex[2] = { 0.5f, 0.5f, -0.5f };
	BaseVertex[3] = { -0.5f, 0.5f, -0.5f };

	//Front
	Vertex[0] = BaseVertex[0];
	Vertex[1] = BaseVertex[1];
	Vertex[2] = BaseVertex[2];
	Vertex[3] = BaseVertex[3];
	//Back
	Vertex[0 + 4] = BaseVertex[0].GetRotateX(180.0f);
	Vertex[1 + 4] = BaseVertex[1].GetRotateX(180.0f);
	Vertex[2 + 4] = BaseVertex[2].GetRotateX(180.0f);
	Vertex[3 + 4] = BaseVertex[3].GetRotateX(180.0f);
	//Left Right
	Vertex[0 + 8] = BaseVertex[0].GetRotateY(-90.0f);
	Vertex[1 + 8] = BaseVertex[1].GetRotateY(-90.0f);
	Vertex[2 + 8] = BaseVertex[2].GetRotateY(-90.0f);
	Vertex[3 + 8] = BaseVertex[3].GetRotateY(-90.0f);
	Vertex[0 + 12] = BaseVertex[0].GetRotateY(90.0f);
	Vertex[1 + 12] = BaseVertex[1].GetRotateY(90.0f);
	Vertex[2 + 12] = BaseVertex[2].GetRotateY(90.0f);
	Vertex[3 + 12] = BaseVertex[3].GetRotateY(90.0f);
	//Top Bottom
	Vertex[0 + 16] = BaseVertex[0].GetRotateX(90.0f);
	Vertex[1 + 16] = BaseVertex[1].GetRotateX(90.0f);
	Vertex[2 + 16] = BaseVertex[2].GetRotateX(90.0f);
	Vertex[3 + 16] = BaseVertex[3].GetRotateX(90.0f);
	Vertex[0 + 20] = BaseVertex[0].GetRotateX(-90.0f);
	Vertex[1 + 20] = BaseVertex[1].GetRotateX(-90.0f);
	Vertex[2 + 20] = BaseVertex[2].GetRotateX(-90.0f);
	Vertex[3 + 20] = BaseVertex[3].GetRotateX(-90.0f);

	std::vector<int> Idx =
	{
		0, 1, 2,
		0, 2, 3,
		0 + 4, 1 + 4, 2 + 4,
		0 + 4, 2 + 4, 3 + 4,
		0 + 8, 1 + 8, 2 + 8,
		0 + 8, 2 + 8, 3 + 8,
		0 + 12, 1 + 12, 2 + 12,
		0 + 12, 2 + 12, 3 + 12,
		0 + 16, 1 + 16, 2 + 16,
		0 + 16, 2 + 16, 3 + 16,
		0 + 20, 1 + 20, 2 + 20,
		0 + 20, 2 + 20, 3 + 20
	};

	for (size_t IdxCnt = 0; IdxCnt < Idx.size() / 3; ++IdxCnt)
	{
		float4 fTri[3]{};
		POINT iTri[3]{};

		for (int i = 0; i < 3; ++i)
		{
			float4 WorldPoint = Vertex[Idx[IdxCnt * 3 + i]];

			WorldPoint *= Scale;
			WorldPoint.RotateX(Rotation.X);
			WorldPoint.RotateY(Rotation.Y);
			WorldPoint.RotateZ(Rotation.Z);
			WorldPoint += Position;

			fTri[i] = WorldPoint;
			iTri[i] = WorldPoint.ToPoint();
		}

		float4 Dir0 = fTri[0] - fTri[1];
		float4 Dir1 = fTri[1] - fTri[2];
		float4 Check{};
		Check.Cross3D(Dir0, Dir1);

		if (Check.Z > -1.0f)
		{
			continue;
		}

		Polygon(MemDc, &iTri[0], 3);
	}

	GameEngineCore::GetWindow().DoubleBuffering();
}

void ContentsCore::Release()
{
}
