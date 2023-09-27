#include "PreCompile.h"
#include "GameEngineRenderer.h"

#include "GameEngineCamera.h"
#include "GameEngineLevel.h"

#include "GameEngineInputLayOut.h"
#include "GameEngineRenderTarget.h"

#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"

void GameEngineRenderer::SetRenderOrder(int _Order)
{
	if (!Camera)
	{
		assert(false);
		return;
	}

	Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	SetOrder(_Order);
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
}

void GameEngineRenderer::SetCameraOrder(int _Order)
{
	SetViewCameraSelect(_Order);
}

void GameEngineRenderer::Start()
{
	SetCameraOrder(ECAMERAORDER::Main);
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	auto FindCamera = GetLevel()->GetCamera(_Order);
	if (!FindCamera)
	{
		assert(false);
		return;
	}

	if (Camera)
	{
		Camera->Renderers[GetOrder()].remove(GetDynamic_Cast_This<GameEngineRenderer>());
	}

	Camera = FindCamera.get();
	Camera->Renderers[GetOrder()].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	for (auto& Unit : Units)
	{
		Unit->ResSetting();
		Unit->Draw();
	}
}

std::shared_ptr<GameEngineRenderUnit> GameEngineRenderer::CreateAndFindRenderUnit(int _Index)
{
	Units.resize(_Index + 1);

	if (Units[_Index])
	{
		return Units[_Index];
	}

	Units[_Index] = std::make_shared<GameEngineRenderUnit>();
	Units[_Index]->SetParentRenderer(this);
	return Units[_Index];
}

void GameEngineRenderer::SetMesh(std::string_view _Name, int _Index)
{
	auto Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMesh(_Name);
}

void GameEngineRenderer::SetMaterial(std::string_view _Name, int _Index)
{
	auto Unit = CreateAndFindRenderUnit(_Index);
	Unit->SetMaterial(_Name);
}

GameEngineShaderResHelper& GameEngineRenderer::GetShaderResHelper(int _Index)
{
	auto Unit = CreateAndFindRenderUnit(_Index);
	return Unit->ShaderResHelper;
}
