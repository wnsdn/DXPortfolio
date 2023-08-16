#include "PreCompile.h"
#include "GameEngineDevice.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"
#include <d3d11.h>
#include <dxgi.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")

GameEngineDevice::GameEngineDevice()
{
}

GameEngineDevice::~GameEngineDevice()
{
	if (Device)
	{
		Device->Release();
		Device = nullptr;
	}
	if (Context)
	{
		Context->Release();
		Context = nullptr;
	}
	if (SwapChain)
	{
		SwapChain->Release();
		SwapChain = nullptr;
	}

	CoUninitialize();
}

void GameEngineDevice::Initialize(const GameEngineWindow& _Window)
{
	HRESULT Hresult = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (Hresult == E_FAIL)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	if (!_Window.GetHwnd())
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

#ifdef _DEBUG
	UINT iFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT iFlag = 0;
#endif

	float4 WindowScale = _Window.GetInst().GetScale();

	DXGI_SWAP_CHAIN_DESC SwapChainDesc{};
	SwapChainDesc.BufferDesc.Width = static_cast<UINT>(WindowScale.X);
	SwapChainDesc.BufferDesc.Height = static_cast<UINT>(WindowScale.Y);
	SwapChainDesc.BufferDesc.RefreshRate.Numerator = 60;
	SwapChainDesc.BufferDesc.RefreshRate.Denominator = 1;
	SwapChainDesc.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	SwapChainDesc.SampleDesc.Count = 1;
	SwapChainDesc.SampleDesc.Quality = 0;
	SwapChainDesc.BufferCount = 2;
	SwapChainDesc.OutputWindow = _Window.GetHwnd();
	SwapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	SwapChainDesc.Windowed = true;
	SwapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	SwapChainDesc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	Hresult = D3D11CreateDeviceAndSwapChain(
		nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, iFlag,
		nullptr, 0, D3D11_SDK_VERSION, &SwapChainDesc,
		&SwapChain, &Device, nullptr, &Context);
	if (Hresult == E_FAIL)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}
	if (Device->GetFeatureLevel() != D3D_FEATURE_LEVEL_11_0)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	Hresult = SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(&DXBackBufferTexture));
	if (Hresult == E_FAIL)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	BackBufferTexture = GameEngineTexture::Create(DXBackBufferTexture);
	BackBufferRenderTarget = GameEngineRenderTarget::Create(BackBufferTexture);
	ResourcesInit();
}

void GameEngineDevice::RenderStart()
{
	if (!Device)
	{
		return;
	}

	BackBufferRenderTarget->Clear();
	BackBufferRenderTarget->Setting();
}

void GameEngineDevice::RenderEnd()
{
	if (!Device)
	{
		return;
	}

	HRESULT Result = SwapChain->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}
}
