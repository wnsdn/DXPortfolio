#pragma once
#include "GameEngineDirectBuffer.h"

class GameEngineConstantBuffer : public GameEngineResources<GameEngineConstantBuffer>, public GameEngineDirectBuffer
{
public:
	GameEngineConstantBuffer() : BufferDesc{} {}
	~GameEngineConstantBuffer() {}
	GameEngineConstantBuffer(const GameEngineConstantBuffer&) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&&) noexcept = delete;
	void operator=(const GameEngineConstantBuffer&) = delete;
	void operator=(GameEngineConstantBuffer&&) noexcept = delete;

	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(int _Byte, std::string_view _Name, D3D11_SHADER_BUFFER_DESC _BufferDesc)
	{
		if (ConstantBuffers.find(_Byte) == ConstantBuffers.end())
		{
			ConstantBuffers[_Byte];
		}

		auto& Buffers = ConstantBuffers[_Byte];
		std::string Name{ _Name };

		if (Buffers.find(Name) != Buffers.end())
		{
			return ConstantBuffers[_Byte][Name];
		}

		auto Res = CreateRes();
		Res->SetName(Name);
		Res->BufferDesc = _BufferDesc;
		ConstantBuffers[_Byte][Name] = Res;
		Res->ResCreate(_Byte);
		return Res;
	}

	template <typename DataType>
	void ChangeData(const DataType& _Data)
	{
		ChangeData(&_Data, sizeof(DataType));
	}
	void ChangeData(const void* _Data, UINT _Size);

	void VSSetting(UINT _Slot);
	void PSSetting(UINT _Slot);
private:
	void ResCreate(int _ByteSize);

	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBuffers;
	D3D11_SHADER_BUFFER_DESC BufferDesc;
};

