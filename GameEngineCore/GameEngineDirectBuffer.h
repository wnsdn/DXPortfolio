#pragma once
#include <d3d11.h>

class GameEngineDirectBuffer
{
private:
protected:
	D3D11_BUFFER_DESC BufferInfo{};
	ID3D11Buffer* Buffer = nullptr;
public:

#pragma region Constructor
	GameEngineDirectBuffer() {}
	~GameEngineDirectBuffer();
	GameEngineDirectBuffer(const GameEngineDirectBuffer&) = delete;
	GameEngineDirectBuffer(GameEngineDirectBuffer&&) noexcept = delete;
	GameEngineDirectBuffer& operator=(const GameEngineDirectBuffer&) = delete;
	GameEngineDirectBuffer& operator=(GameEngineDirectBuffer&&) noexcept = delete;
#pragma endregion
};