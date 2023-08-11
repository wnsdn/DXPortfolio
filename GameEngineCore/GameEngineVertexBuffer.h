#pragma once
#include "GameEngineResources.h"
#include "GameEngineDirectBuffer.h"

class GameEngineVertexBuffer
	: public GameEngineResources<GameEngineVertexBuffer>
	, public GameEngineDirectBuffer
{
private:
	UINT VertexSize = 0;
	UINT VertexCount = 0;
	UINT Offset = 0;

	void ResCreate(const void* _Data, size_t _VertexSize, size_t _VertexCount);
protected:
public:
	void Setting();

	template <typename VertexType>
	static std::shared_ptr<GameEngineVertexBuffer> Create(std::string_view _Name,
		const std::vector<VertexType>& _Data)
	{
		std::shared_ptr<GameEngineVertexBuffer> Res =
			GameEngineResources::CreateRes(_Name);
		Res->ResCreate(&_Data[0], sizeof(VertexType), _Data.size());
		return nullptr;
	}

#pragma region Constructor
	GameEngineVertexBuffer() {}
	~GameEngineVertexBuffer() {}
	GameEngineVertexBuffer(const GameEngineVertexBuffer&) = delete;
	GameEngineVertexBuffer(GameEngineVertexBuffer&&) noexcept = delete;
	GameEngineVertexBuffer& operator=(const GameEngineVertexBuffer&) = delete;
	GameEngineVertexBuffer& operator=(GameEngineVertexBuffer&&) noexcept = delete;
#pragma endregion
};