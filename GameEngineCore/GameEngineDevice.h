#pragma once
#include <memory>
#include <d3d11.h>

class GameEngineWindow;
class GameEngineTexture;
class GameEngineRenderTarget;
class GameEngineDevice
{
	friend class GameEngineCore;
private:
	IDXGISwapChain* SwapChain = nullptr;
	ID3D11Device* Device = nullptr;
	ID3D11DeviceContext* Context = nullptr;

	std::shared_ptr<GameEngineTexture> BackBufferTexture;
	std::shared_ptr<GameEngineRenderTarget> BackBufferRenderTarget;

	void RenderStart();
	void RenderEnd();
	void ResourcesInit();
public:
	void Initialize(const GameEngineWindow& _Window);
	ID3D11Device* GetDevice() const
	{
		return Device;
	}
	ID3D11DeviceContext* GetContext() const
	{
		return Context;
	}
	auto GetBackBufferRenderTarget() const
	{
		return BackBufferRenderTarget;
	}

	GameEngineDevice() {}
	~GameEngineDevice();
	GameEngineDevice(const GameEngineDevice&) = delete;
	GameEngineDevice(GameEngineDevice&&) noexcept = delete;
	void operator=(const GameEngineDevice&) = delete;
	void operator=(GameEngineDevice&&) noexcept = delete;
};