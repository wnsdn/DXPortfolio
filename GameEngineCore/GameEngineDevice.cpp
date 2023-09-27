#include "PreCompile.h"
#include "GameEngineDevice.h"

#include <GameEnginePlatform/GameEngineWindow.h>
#include "GameEngineTexture.h"
#include "GameEngineRenderTarget.h"

GameEngineDevice::~GameEngineDevice()
{
	SafeRelease(Device);
	SafeRelease(Context);
	SafeRelease(SwapChain);

	CoUninitialize();
}

void GameEngineDevice::Initialize(const GameEngineWindow& _Window)
{
	Check(CoInitializeEx(nullptr, COINIT_MULTITHREADED));

#ifdef _DEBUG
	UINT iFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
	UINT iFlag = 0;
#endif

	float4 WindowScale = _Window.GetInst().GetScale();
	DXGI_SWAP_CHAIN_DESC Desc{};
	Desc.BufferDesc.Width = static_cast<UINT>(WindowScale.X);
	Desc.BufferDesc.Height = static_cast<UINT>(WindowScale.Y);
	Desc.BufferDesc.RefreshRate.Numerator = 60;
	Desc.BufferDesc.RefreshRate.Denominator = 1;
	Desc.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
	Desc.SampleDesc.Count = 1;
	Desc.SampleDesc.Quality = 0;
	Desc.BufferCount = 2;
	Desc.OutputWindow = _Window.GetHwnd();
	Desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT | DXGI_USAGE_SHADER_INPUT;
	Desc.Windowed = true;
	Desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;
	Desc.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;

	D3D11CreateDeviceAndSwapChain(nullptr, D3D_DRIVER_TYPE_HARDWARE, nullptr, iFlag, nullptr, 0, D3D11_SDK_VERSION, &Desc, &SwapChain, &Device, nullptr, &Context);

	ID3D11Texture2D* DXBackBufferTexture = nullptr;
	SwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(&DXBackBufferTexture));

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
	//BackBufferRenderTarget->Setting();
}

void GameEngineDevice::RenderEnd()
{
	if (!Device)
	{
		return;
	}

	auto HR = SwapChain->Present(0, 0);
	if (HR == DXGI_ERROR_DEVICE_REMOVED || HR == DXGI_ERROR_DEVICE_RESET)
	{
		assert(false);
		return;
	}
}
