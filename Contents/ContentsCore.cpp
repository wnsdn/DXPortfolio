#include "PreCompile.h"
#include "ContentsCore.h"

#include <GameEnginePlatform/GameEngineText.h>

void ContentsCore::Start()
{
}

void ContentsCore::Update(float _Delta)
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

	float4x4 Model4x4{}, Scale4x4{}, Rotation4x4{}, Translation4x4{};
	Scale4x4.Scale({ 100.0f, 100.0f });
	//Rotation4x4.Rotate({ 30.0f, 60.0f, 30.0f });
	Translation4x4.Translation({ 100.0f, 100.0f });
	Model4x4 *= Scale4x4 * Rotation4x4 * Translation4x4;

	float4x4 View4x4{};
	static float4 CamDeg{};
	static float4 CamPos{};
	View4x4.View(CamDeg, CamPos);

	if (GameEngineInput::IsPress('A'))
	{
		CamPos += float4::Left * _Delta * 100.0f;
	}
	else if (GameEngineInput::IsPress('D'))
	{
		CamPos += float4::Right * _Delta * 100.0f;
	}
	if (GameEngineInput::IsPress('W'))
	{
		CamPos += float4::Up * _Delta * 100.0f;
	}
	else if (GameEngineInput::IsPress('S'))
	{
		CamPos += float4::Down * _Delta * 100.0f;
	}
	if (GameEngineInput::IsPress('Q'))
	{
		CamDeg.Y += 360.0f * _Delta;
	}
	else if (GameEngineInput::IsPress('E'))
	{
		CamDeg.Y -= 360.0f * _Delta;
	}

	float4x4 Projection4x4{};
	Projection4x4.Perspective(60.0f, GetWndScalef().X, GetWndScalef().Y, 1000.0f, 0.1f);

	float4x4 MVP4x4 = Model4x4 * View4x4 * Projection4x4;

	for (int i = 0; i < 2; ++i)
	{
		POINT Tri[3]{};
		for (int j = 0; j < 3; ++j)
		{
			float4 Temp = Vertex[Idx[i][j]];

			Temp *= MVP4x4;
			Temp /= Temp.W;
			Temp.W = 1.0f;

			Tri[j] = Temp.ToPoint();
		}

		Polygon(MemDc, Tri, 3);
	}

	GameEngineCore::GetWindow().DoubleBuffering();
}

void ContentsCore::Release()
{
}
