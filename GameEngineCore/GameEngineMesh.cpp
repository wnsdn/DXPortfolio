#include "PreCompile.h"
#include "GameEngineMesh.h"

GameEngineMesh::GameEngineMesh()
{
}

GameEngineMesh::~GameEngineMesh()
{
}

void GameEngineMesh::InputAssembler1()
{
	if (!VertexBufferPtr)
	{
		assert(false);
		return;
	}

	VertexBufferPtr->Setting();
	GameEngineCore::GetContext()->IASetPrimitiveTopology(TOPOLOGY);
}

void GameEngineMesh::InputAssembler2()
{
	if (!IndexBufferPtr)
	{
		assert(false);
		return;
	}

	IndexBufferPtr->Setting();
}

void GameEngineMesh::Draw()
{
	GameEngineCore::GetContext()->DrawIndexed(IndexBufferPtr->GetIndexCount(), 0, 0);
}
