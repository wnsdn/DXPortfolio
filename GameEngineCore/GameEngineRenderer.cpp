#include "PreCompile.h"
#include "GameEngineRenderer.h"

#include "GameEngineCamera.h"
#include "GameEngineLevel.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineConstantBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"

void GameEngineRenderer::Start()
{
	SetViewCameraSelect(0);
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	ResSetting();
	Draw();
}

void GameEngineRenderer::ResSetting()
{
	auto VB = GameEngineVertexBuffer::Find("Rect");
	auto VS = GameEngineVertexShader::Find("ColorShader_VS");
	auto IB = GameEngineIndexBuffer::Find("Rect");
	auto CB = GameEngineConstantBuffer::CreateAndFind(sizeof(TransformData), "TransformData");
	auto RS = GameEngineRasterizer::Find("RasterizerState");
	auto PS = GameEnginePixelShader::Find("TextureShader_PS");
	auto RTV = GameEngineCore::GetBackBufferRenderTarget();

	VB->Setting();
	GameEngineInputLayout IL;
	IL.ResCreate(VB, VS);
	IL.Setting();
	IB->Setting();
	GameEngineCore::GetContext()->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

	VS->Setting();

	auto& TD = Transform.GetConstTransformDataRef();
	CB->ChangeData(TD);
	CB->Setting();

	D3D11_VIEWPORT Viewport{};
	Viewport.TopLeftX = 0;
	Viewport.TopLeftY = 0;
	Viewport.Width = GameEngineWindow::GetInst().GetScale().X;
	Viewport.Height = GameEngineWindow::GetInst().GetScale().Y;
	Viewport.MaxDepth = 1;
	Viewport.MinDepth = 0;
	GameEngineCore::GetContext()->RSSetViewports(1, &Viewport);
	RS->Setting();

	PS->Setting();

	RTV->Setting();
}

void GameEngineRenderer::Draw()
{
	auto IB = GameEngineIndexBuffer::Find("Rect");

	GameEngineCore::GetContext()->DrawIndexed(IB->GetIndexCount(), 0, 0);
}

void GameEngineRenderer::SetViewCameraSelect(int _Order)
{
	GameEngineLevel* Level = GetLevel();
	std::shared_ptr<GameEngineCamera> Camera = Level->GetCamera(_Order);

	if (!Camera)
	{
		MsgBoxAssert(__FUNCTION__);
		return;
	}

	Camera->Renderers[_Order].push_back(GetDynamic_Cast_This<GameEngineRenderer>());
	ViewInfo[Camera.get()] = _Order;
}
