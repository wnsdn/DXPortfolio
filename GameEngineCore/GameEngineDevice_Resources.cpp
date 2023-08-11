#include "PreCompile.h"
#include "GameEngineDevice.h"

void GameEngineDevice::ResourcesInit()
{
	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4 * 6);

		GameEngineVertex2D BaseVertexs[4];

		BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		// 앞면
		Vertex[0] = BaseVertexs[0];
		Vertex[1] = BaseVertexs[1];
		Vertex[2] = BaseVertexs[2];
		Vertex[3] = BaseVertexs[3];

		// 뒷면
		Vertex[4].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 180.0f);
		Vertex[5].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 180.0f);
		Vertex[6].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 180.0f);
		Vertex[7].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 180.0f);

		// 왼쪽이나 오른쪽
		Vertex[8].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, 90.0f);
		Vertex[9].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, 90.0f);
		Vertex[10].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, 90.0f);
		Vertex[11].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, 90.0f);

		// 왼쪽이나 오른쪽
		Vertex[12].POSITION = float4::VectorRotationToDegY(BaseVertexs[0].POSITION, -90.0f);
		Vertex[13].POSITION = float4::VectorRotationToDegY(BaseVertexs[1].POSITION, -90.0f);
		Vertex[14].POSITION = float4::VectorRotationToDegY(BaseVertexs[2].POSITION, -90.0f);
		Vertex[15].POSITION = float4::VectorRotationToDegY(BaseVertexs[3].POSITION, -90.0f);

		// 위거나 아래
		Vertex[16].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, 90.0f);
		Vertex[17].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, 90.0f);
		Vertex[18].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, 90.0f);
		Vertex[19].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, 90.0f);

		Vertex[20].POSITION = float4::VectorRotationToDegX(BaseVertexs[0].POSITION, -90.0f);
		Vertex[21].POSITION = float4::VectorRotationToDegX(BaseVertexs[1].POSITION, -90.0f);
		Vertex[22].POSITION = float4::VectorRotationToDegX(BaseVertexs[2].POSITION, -90.0f);
		Vertex[23].POSITION = float4::VectorRotationToDegX(BaseVertexs[3].POSITION, -90.0f);

		GameEngineVertexBuffer::Create("Box", Vertex);
	}

	{
		std::vector<GameEngineVertex2D> Vertex;
		Vertex.resize(4);

		GameEngineVertex2D BaseVertexs[4];

		BaseVertexs[0] = { { -0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[1] = { { 0.5f, -0.5f, -0.5f, 1.0f } };
		BaseVertexs[2] = { { 0.5f, 0.5f, -0.5f, 1.0f } };
		BaseVertexs[3] = { { -0.5f, 0.5f, -0.5f, 1.0f } };

		GameEngineVertexBuffer::Create("Rect", Vertex);
	}

	float4 Vertex[8]
	{
		{-0.5f, 0.5f, -0.5f, 1.0f},
		{0.5f, 0.5f, -0.5f, 1.0f},
		{0.5f, 0.5f, 0.5f, 1.0f},
		{-0.5f, 0.5f, 0.5f, 1.0f},
		{-0.5f, -0.5f, -0.5f, 1.0f},
		{0.5f, -0.5f, -0.5f, 1.0f},
		{0.5f, -0.5f, 0.5f, 1.0f},
		{-0.5f, -0.5f, 0.5f, 1.0f}
	};
	int Idx[6][6]
	{
		0, 1, 5, 5, 4, 0,
		1, 2, 6, 6, 5, 1,
		2, 3, 7, 7 ,6, 2,
		3, 0, 4, 4, 7, 3,
		3, 2, 1, 1, 0, 3,
		4, 5, 6, 6, 7, 4
	};

	float4x4 ViewPort4x4{};
	ViewPort4x4.ViewPort(1280.0f, 720.0f);
	const TransformData& TransDataRef = Transform.GetConstTransformDataRef();
	for (int i = 0; i < 6; ++i)
	{
		for (int j = 0; j < 2; ++j)
		{
			POINT Tri[3]{};
			float4 fTri[3]{};
			for (int k = 0; k < 3; ++k)
			{
				float4 Temp = Vertex[Idx[i][j * 3 + k]];

				Temp *= TransDataRef.WorldViewProjectionMatrix;
				Temp /= Temp.W;
				Temp.W = 1.0f;
				Temp *= ViewPort4x4;

				Tri[k] = Temp;
				fTri[k] = Temp;
			}

			float4 V1 = fTri[0] - fTri[1];
			float4 V2 = fTri[2] - fTri[1];
			float4 Cross = float4::Cross(V1, V2);
			if (Cross.Z >= 0.0f)
			{
				continue;
			}

			Polygon(GameEngineWindow::GetInst().GetMemDc(), Tri, 3);
		}
	}
}
