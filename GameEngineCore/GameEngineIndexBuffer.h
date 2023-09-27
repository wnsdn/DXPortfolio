#pragma once
#include "GameEngineDirectBuffer.h"

class GameEngineInputLayoutInfo;
class GameEngineIndexBuffer : public GameEngineResources<GameEngineIndexBuffer>, public GameEngineDirectBuffer
{
	friend class GameEngineInputLayout;
public:
	GameEngineIndexBuffer() {}
	~GameEngineIndexBuffer() {}
	GameEngineIndexBuffer(const GameEngineIndexBuffer&) = delete;
	GameEngineIndexBuffer(GameEngineIndexBuffer&&) noexcept = delete;
	void operator=(const GameEngineIndexBuffer&) = delete;
	void operator=(GameEngineIndexBuffer&&) noexcept = delete;

	static std::shared_ptr<GameEngineIndexBuffer> Create(std::string_view _Name, const std::vector<unsigned int>& _Data)
	{
		auto Res = CreateRes(_Name);
		Res->ResCreate(&_Data[0], _Data.size());
		return nullptr;
	}

	void Setting();

	int GetIndexCount() const
	{
		return IndexCount;
	}
private:
	void ResCreate(const void* _Data, size_t _IndexCount);

	DXGI_FORMAT Format = DXGI_FORMAT::DXGI_FORMAT_R32_UINT;
	UINT IndexSize = 4;
	UINT IndexCount = 0;
	UINT Offset = 0;
};

