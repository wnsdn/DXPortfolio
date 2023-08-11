#include "PreCompile.h"
#include "GameEngineDevice.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"
#include <d3d11.h>
#include <dxgi.h>

#pragma comment(lib, "d3d11")
#pragma comment(lib, "dxgi")

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
}

void GameEngineDevice::Initialize(const GameEngineWindow& _Window)
{
	if (!_Window.GetHwnd())
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	int iFlag = 0;
#ifdef _DEBUG
	iFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

	D3D_FEATURE_LEVEL Level = D3D_FEATURE_LEVEL_11_0;
	IDXGIAdapter* Adapter = GetHighPerformanceAdapter();
	if (!Adapter)
	{
		Adapter->Release();
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	HRESULT Result = D3D11CreateDevice
	(
		Adapter,
		D3D_DRIVER_TYPE::D3D_DRIVER_TYPE_UNKNOWN,
		nullptr,
		iFlag,
		nullptr,
		0,
		D3D11_SDK_VERSION,
		&Device,
		&Level,
		&Context
	);

	if (Adapter)
	{
		Adapter->Release();
		Adapter = nullptr;
	}

	if (Result != S_OK)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	if (Level != D3D_FEATURE_LEVEL_11_0)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	Result = CoInitializeEx(nullptr, COINIT_MULTITHREADED);
	if (Result != S_OK)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	Window = &_Window;
	CreateSwapChain();
	ResourcesInit();
}

IDXGIAdapter* GameEngineDevice::GetHighPerformanceAdapter()
{
	IDXGIFactory* Factory = nullptr;
	IDXGIAdapter* Adapter = nullptr;

	HRESULT Hr = CreateDXGIFactory(__uuidof(IDXGIFactory),
		reinterpret_cast<void**>(&Factory));
	if (!Factory)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return nullptr;
	}

	SIZE_T VideoMemory = 0;
	for (int i = 0;; ++i)
	{
		IDXGIAdapter* CurAdapter = nullptr;
		Factory->EnumAdapters(i, &CurAdapter);
		if (!CurAdapter)
		{
			break;
		}

		DXGI_ADAPTER_DESC Desc{};
		CurAdapter->GetDesc(&Desc);
		if (VideoMemory <= Desc.DedicatedVideoMemory)
		{
			VideoMemory = Desc.DedicatedVideoMemory;
			if (Adapter)
			{
				Adapter->Release();
			}

			Adapter = CurAdapter;
			continue;
		}

		CurAdapter->Release();
	}

	Factory->Release();
	return Adapter;
}

void GameEngineDevice::CreateSwapChain()
{
	float4 WindowScale = Window->GetInst().GetScale();

	DXGI_SWAP_CHAIN_DESC ScInfo{};
	ScInfo.BufferCount = 2;
	ScInfo.BufferDesc.Width = static_cast<int>(WindowScale.X);
	ScInfo.BufferDesc.Height = static_cast<int>(WindowScale.Y);
	ScInfo.OutputWindow = Window->GetHwnd();
	ScInfo.BufferDesc.RefreshRate.Denominator = 1;
	ScInfo.BufferDesc.RefreshRate.Numerator = 60;
	ScInfo.BufferDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
	ScInfo.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;
	ScInfo.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
	ScInfo.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	ScInfo.SampleDesc.Quality = 0;
	ScInfo.SampleDesc.Count = 1;
	ScInfo.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
	ScInfo.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
	ScInfo.Windowed = true;

	IDXGIDevice* pD = nullptr;
	IDXGIAdapter* pA = nullptr;
	IDXGIFactory* pF = nullptr;

	Device->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pD));
	if (!pD)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}
	pD->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pA));
	if (!pA)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}
	pA->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pF));
	if (!pF)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	pF->CreateSwapChain(Device, &ScInfo, &SwapChain);
	pF->Release();
	pA->Release();
	pD->Release();

	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	if (SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D),
		reinterpret_cast<void**>(&DXBackBufferTexture)) != S_OK)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}

	BackBufferTexture = GameEngineTexture::Create(DXBackBufferTexture);
	BackBufferRenderTarget = GameEngineRenderTarget::Create(BackBufferTexture);
}

void GameEngineDevice::RenderStart()
{
	BackBufferRenderTarget->Clear();
	BackBufferRenderTarget->Setting();
}

void GameEngineDevice::RenderEnd()
{
	HRESULT Result = SwapChain->Present(0, 0);
	if (Result == DXGI_ERROR_DEVICE_REMOVED || Result == DXGI_ERROR_DEVICE_RESET)
	{
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		return;
	}
}
