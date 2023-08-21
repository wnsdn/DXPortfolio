#include "PreCompile.h"
#include "GameEngineVertex.h"

GameEngineInputLayoutInfo GameEngineVertex2D::VertexInfo;

class GameEngineVertex2DStart
{
public:
	GameEngineVertex2DStart()
	{
		GameEngineVertex2D::VertexInfo.AddInputLayoutDesc(
			"POSITION", DXGI_FORMAT_R32G32B32A32_FLOAT);
		GameEngineVertex2D::VertexInfo.AddInputLayoutDesc(
			"COLOR", DXGI_FORMAT_R32G32B32A32_FLOAT);
	}
};

GameEngineVertex2DStart GameEngineVertex2DInit;