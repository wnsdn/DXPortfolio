#pragma once
#include "GameEngineResources.h"
#include "GameEngineVertexBuffer.h"
#include "GameEngineIndexBuffer.h"

class GameEngineMesh : public GameEngineResources<GameEngineMesh>
{
public:
	GameEngineMesh();
	~GameEngineMesh();
	GameEngineMesh(const GameEngineMesh&) = delete;
	GameEngineMesh(GameEngineMesh&&) noexcept = delete;
	void operator=(const GameEngineMesh&) = delete;
	void operator=(GameEngineMesh&&) noexcept = delete;

	void InputAssembler1();
	void InputAssembler2();

	static std::shared_ptr<GameEngineMesh> Create(std::string_view _Name)
	{
		return Create(_Name, _Name, _Name);
	}
	static std::shared_ptr<GameEngineMesh> Create(std::string_view _Name, std::string_view _VtxName, std::string_view _IdxName)
	{
		auto Res = CreateRes(_Name);
		Res->VertexBufferPtr = GameEngineVertexBuffer::Find(_VtxName);
		Res->IndexBufferPtr = GameEngineIndexBuffer::Find(_IdxName);

		if (!Res->VertexBufferPtr || !Res->IndexBufferPtr)
		{
			assert(false);
			return nullptr;
		}

		return Res;
	}

	std::shared_ptr<GameEngineVertexBuffer> GetVertexBuffer() const
	{
		return VertexBufferPtr;
	}

	void Draw();
private:
	D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
	std::shared_ptr<GameEngineVertexBuffer> VertexBufferPtr;
	std::shared_ptr<GameEngineIndexBuffer> IndexBufferPtr;
};
