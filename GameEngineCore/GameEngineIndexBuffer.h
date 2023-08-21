#pragma once
#include "GameEngineResources.h"
#include "GameEngineDirectBuffer.h"

class GameEngineInputLayoutInfo;
class GameEngineIndexBuffer
	: public GameEngineResources<GameEngineIndexBuffer>
	, public GameEngineDirectBuffer
{
	friend class GameEngineInputLayout;
private:
	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
	UINT IndexSize = 4;
	UINT IndexCount = 0;
	UINT Offset = 0;

	const GameEngineInputLayoutInfo* VertexInfoPtr;

	void ResCreate(const void* _Data, size_t _IndexCount);
public:
	static std::shared_ptr<GameEngineIndexBuffer> Create(std::string_view _Name, const std::vector<unsigned int>& _Data)
	{
		auto Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(&_Data[0], _Data.size());
		return nullptr;
	}

	void Setting();

	GameEngineIndexBuffer() {}
	~GameEngineIndexBuffer() {}
	GameEngineIndexBuffer(const GameEngineIndexBuffer&) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&&) noexcept = delete;
	void operator=(const GameEngineIndexBuffer&) = delete;
	void operator=(GameEngineIndexBuffer&&) noexcept = delete;
};

