#include "PreCompile.h"
#include "GameEngineRenderer.h"

#include "GameEngineCamera.h"
#include "GameEngineLevel.h"

#include "GameEngineVertexBuffer.h"
#include "GameEngineVertexShader.h"
#include "GameEngineInputLayOut.h"
#include "GameEngineIndexBuffer.h"
#include "GameEngineRasterizer.h"
#include "GameEnginePixelShader.h"
#include "GameEngineRenderTarget.h"

void GameEngineRenderer::Start()
{
	SetViewCameraSelect(0);
}

void GameEngineRenderer::Render(GameEngineCamera* _Camera, float _Delta)
{
	{
		auto VB = GameEngineVertexBuffer::Find("Rect");
		if (VB)
		{
			VB->Setting();
		}

		auto VS = GameEngineVertexShader::Find("ColorShader_VS");
		if (VS)
		{
			VS->Setting();
		}

		if (VS && VB && !Layout)
		{
			Layout = std::make_shared<GameEngineInputLayout>();
			Layout->ResCreate(VB, VS);
		}

		if (Layout)
		{
			Layout->Setting();
		}

		auto IB = GameEngineIndexBuffer::Find("Rect");
		if (IB)
		{
			IB->Setting();
		}

		GameEngineCore::MainDevice.GetContext()->IASetPrimitiveTopology(
			D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

		D3D11_VIEWPORT ViewPort{};
		ViewPort.Width = GameEngineWindow::GetInst().GetScale().X;
		ViewPort.Width = GameEngineWindow::GetInst().GetScale().Y;
		ViewPort.MinDepth = 0.0f;
		ViewPort.MaxDepth = 1.0f;
		ViewPort.TopLeftX = 0.0f;
		ViewPort.TopLeftY = 0.0f;
		GameEngineCore::MainDevice.GetContext()->RSSetViewports(1, &ViewPort);

		auto Rasterizer = GameEngineRasterizer::Find("EngineRasterizer");
		if (Rasterizer)
		{
			Rasterizer->Setting();
		}

		auto PixelShader = GameEnginePixelShader::Find("ColorShader_PS");
		if (PixelShader)
		{
			PixelShader->Setting();
		}

		auto BackBufferRenderTarget = GameEngineCore::MainDevice.GetBackBufferRenderTarget();
		if (BackBufferRenderTarget)
		{
			BackBufferRenderTarget->Setting();
		}
	}
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
