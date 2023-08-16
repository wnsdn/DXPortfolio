#include "PreCompile.h"
#include "GameEngineDevice.h"

#include "GameEngineVertex.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"

void GameEngineDevice::ResourcesInit()
{
	{
		std::vector<GameEnginePath> Files =
			GameEngineDirectory::GetAllFile("GameEngineCoreShader", ".fx");

		for (auto& File : Files)//fix
		{
			GameEngineVertexShader::Load(File.GetFilename(), "ColorShader_VS");
		}
	}

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
		Vertex[4].POSITION = BaseVertexs[0].POSITION.RotateReturn({ 180.0f });
		Vertex[5].POSITION = BaseVertexs[1].POSITION.RotateReturn({ 180.0f });
		Vertex[6].POSITION = BaseVertexs[2].POSITION.RotateReturn({ 180.0f });
		Vertex[7].POSITION = BaseVertexs[3].POSITION.RotateReturn({ 180.0f });

		// 왼쪽이나 오른쪽
		Vertex[8].POSITION = BaseVertexs[0].POSITION.RotateReturn({ 0.0f, 90.0f });
		Vertex[9].POSITION = BaseVertexs[1].POSITION.RotateReturn({ 0.0f, 90.0f });
		Vertex[10].POSITION = BaseVertexs[2].POSITION.RotateReturn({ 0.0f, 90.0f });
		Vertex[11].POSITION = BaseVertexs[3].POSITION.RotateReturn({ 0.0f, 90.0f });

		// 왼쪽이나 오른쪽
		Vertex[12].POSITION = BaseVertexs[0].POSITION.RotateReturn({ 0.0f, 90.0f });
		Vertex[13].POSITION = BaseVertexs[1].POSITION.RotateReturn({ 0.0f, 90.0f });
		Vertex[14].POSITION = BaseVertexs[2].POSITION.RotateReturn({ 0.0f, 90.0f });
		Vertex[15].POSITION = BaseVertexs[3].POSITION.RotateReturn({ 0.0f, 90.0f });

		// 위거나 아래
		Vertex[16].POSITION = BaseVertexs[0].POSITION.RotateReturn({ 90.0f });
		Vertex[17].POSITION = BaseVertexs[1].POSITION.RotateReturn({ 90.0f });
		Vertex[18].POSITION = BaseVertexs[2].POSITION.RotateReturn({ 90.0f });
		Vertex[19].POSITION = BaseVertexs[3].POSITION.RotateReturn({ 90.0f });

		Vertex[20].POSITION = BaseVertexs[0].POSITION.RotateReturn({ -90.0f });
		Vertex[21].POSITION = BaseVertexs[1].POSITION.RotateReturn({ -90.0f });
		Vertex[22].POSITION = BaseVertexs[2].POSITION.RotateReturn({ -90.0f });
		Vertex[23].POSITION = BaseVertexs[3].POSITION.RotateReturn({ -90.0f });

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
}
