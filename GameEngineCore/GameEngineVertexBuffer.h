#pragma once
#include "GameEngineResources.h"
#include "GameEngineDirectBuffer.h"

class GameEngineInputLayoutInfo;
class GameEngineVertexBuffer
	: public GameEngineResources<GameEngineVertexBuffer>
	, public GameEngineDirectBuffer
{
	friend class GameEngineInputLayout;
private:
	UINT VertexSize = 0;
	UINT VertexCount = 0;
	UINT Offset = 0;

	const GameEngineInputLayoutInfo* VertexInfoPtr;

	void ResCreate(const void* _Data, size_t _VertexSize, size_t _VertexCount);
public:
	void Setting();

	template <typename VertexType>
	static std::shared_ptr<GameEngineVertexBuffer> Create(
		std::string_view _Name,
		const std::vector<VertexType>& _Data)
	{
		auto Res = GameEngineResources::CreateRes(_Name);
		Res->ResCreate(&_Data[0], sizeof(VertexType), _Data.size());
		Res->VertexInfoPtr = &VertexType::VertexInfo;
		return nullptr;
	}

	GameEngineVertexBuffer() = default;
	~GameEngineVertexBuffer() = default;
	GameEngineVertexBuffer(const GameEngineVertexBuffer&) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&&) noexcept = delete;
	void operator=(const GameEngineVertexBuffer&) = delete;
	void operator=(GameEngineVertexBuffer&&) noexcept = delete;
};