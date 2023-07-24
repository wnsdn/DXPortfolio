#include "PreCompile.h"
#include "ContentsCore.h"

void ContentsCore::Start()
{
}

void ContentsCore::Update(const float _Delta)
{
	GameEngineCore::GetWindow().ClearBackBuffer();
	HDC MemDc = GameEngineCore::GetWindow().GetMemDc();

	static float4 Scale{50, 50, 50};
	static float4 Rotation{0, 0, 0};
	static float4 Position{100, 100, 100};

	float4 Vertex[4]
	{
		{-1, -1},
		{1, -1},
		{1, 1},
		{-1 , 1}
	};

	POINT WndVer[4]{};

	for (int i = 0; i < 4; ++i)
	{
		Vertex[i] *= Scale;
		Vertex[i] += Position;

		WndVer[i] = Vertex[i].ToPoint();
	}

	Polygon(MemDc, WndVer, 4);

	GameEngineCore::GetWindow().DoubleBuffering();
}

void ContentsCore::Release()
{
}
