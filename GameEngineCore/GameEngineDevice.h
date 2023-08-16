#pragma once
#include <memory>

class GameEngineWindow;
class GameEngineTexture;
class GameEngineRenderTarget;
class GameEngineDevice
{
	friend class GameEngineCore;
private:
	struct IDXGISwapChain* SwapChain = nullptr;
	struct ID3D11Device* Device = nullptr;
	struct ID3D11DeviceContext* Context = nullptr;

	std::shared_ptr<GameEngineTexture> BackBufferTexture;
	std::shared_ptr<GameEngineRenderTarget> BackBufferRenderTarget;

	void RenderStart();
	void RenderEnd();
	void ResourcesInit();
protected:
public:
	void Initialize(const GameEngineWindow& _Window);
	struct ID3D11Device* GetDevice() const
	{
		return Device;
	}
	struct ID3D11DeviceContext* GetContext() const
	{
		return Context;
	}

#pragma region Constructor
	GameEngineDevice();
	~GameEngineDevice();
	GameEngineDevice(const GameEngineDevice&) = delete;
	GameEngineDevice(GameEngineDevice&&) noexcept = delete;
	GameEngineDevice& operator=(const GameEngineDevice&) = delete;
	GameEngineDevice& operator=(GameEngineDevice&&) noexcept = delete;
#pragma endregion
};