#pragma once
#include "GameEngineResources.h"

class GameEngineDirectBuffer
{
protected:
	D3D11_BUFFER_DESC BufferInfo{};
	ID3D11Buffer* Buffer = nullptr;
public:
	GameEngineDirectBuffer() {}
	~GameEngineDirectBuffer();
	GameEngineDirectBuffer(const GameEngineDirectBuffer&) = delete;
	GameEngineDirectBuffer(GameEngineDirectBuffer&&) noexcept = delete;
	void operator=(const GameEngineDirectBuffer&) = delete;
	void operator=(GameEngineDirectBuffer&&) noexcept = delete;
};