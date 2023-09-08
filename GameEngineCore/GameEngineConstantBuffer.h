#pragma once
#include "GameEngineDirectBuffer.h"
#include "GameEngineShader.h"

class GameEngineConstantBuffer
	: public GameEngineResources<GameEngineConstantBuffer>
	, public GameEngineDirectBuffer
{
private:
	static std::map<int, std::map<std::string, std::shared_ptr<GameEngineConstantBuffer>>> ConstantBuffers;

	ShaderType Type = ShaderType::None;
	int Slot = 0;

	void ResCreate(int _ByteSize);
public:
	static std::shared_ptr<GameEngineConstantBuffer> CreateAndFind(
		int _Byte,
		std::string_view _Name,
		ShaderType _Type = ShaderType::None,
		int _Slot = 0)
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
		Res->Type = _Type;
		Res->Slot = _Slot;
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
	void Setting(UINT _Slot);

	GameEngineConstantBuffer() {}
	~GameEngineConstantBuffer() {}
	GameEngineConstantBuffer(const GameEngineConstantBuffer&) = delete;
	GameEngineConstantBuffer(GameEngineConstantBuffer&&) noexcept = delete;
	void operator=(const GameEngineConstantBuffer&) = delete;
	void operator=(GameEngineConstantBuffer&&) noexcept = delete;
};

