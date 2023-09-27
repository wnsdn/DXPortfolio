#include "PreCompile.h"
#include "GameEngineRenderUnit.h"
#include "GameEngineMesh.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineMaterial.h"
#include "GameEngineRenderTarget.h"
#include "GameEngineShader.h"
#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderer.H"

GameEngineRenderUnit::GameEngineRenderUnit()
{
}

GameEngineRenderUnit::~GameEngineRenderUnit()
{
}

void GameEngineRenderUnit::ResSetting()
{
	Mesh->InputAssembler1();
	Material->VertexShader();
	Layout->Setting();
	Mesh->InputAssembler2();
	Material->Rasterizer();
	Material->PixelShader();
	Material->Blend();

	ShaderResHelper.AllShaderResourcesSetting();

	D3D11_VIEWPORT Viewport{};
	Viewport.Width = GameEngineWindow::GetInst().GetScale().X;
	Viewport.Height = GameEngineWindow::GetInst().GetScale().Y;
	Viewport.MaxDepth = 1.0f;

	GameEngineCore::GetContext()->RSSetViewports(1, &Viewport);
}

void GameEngineRenderUnit::Draw()
{
	Mesh->Draw();
}

void GameEngineRenderUnit::SetMesh(std::string_view _Name)
{
	Mesh = GameEngineMesh::Find(_Name);

	if (!Mesh)
	{
		assert(false);
		return;
	}

	if (!Layout && Material)
	{
		Layout = std::make_shared<GameEngineInputLayout>();
		Layout->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
	}
}

void GameEngineRenderUnit::SetMaterial(std::string_view _Name)
{
	Material = GameEngineMaterial::Find(_Name);

	ShaderResHelper.ResClear();

	if (!Material)
	{
		assert(false);
		return;
	}

	if (!Layout && Mesh)
	{
		Layout = std::make_shared<GameEngineInputLayout>();
		Layout->ResCreate(Mesh->GetVertexBuffer(), Material->GetVertexShader());
	}

	ShaderResHelper.ShaderResCopy(Material->GetVertexShader().get());
	ShaderResHelper.ShaderResCopy(Material->GetPixelShader().get());

	if (ParentRenderer && ShaderResHelper.IsConstantBuffer("TransformData"))
	{
		auto& Data = ParentRenderer->Transform.GetConstTransformDataRef();
		ShaderResHelper.SetConstantBufferLink("TransformData", Data);
	}
}
