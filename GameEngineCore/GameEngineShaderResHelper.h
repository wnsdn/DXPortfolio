#pragma once
#include "GameEngineConstantBuffer.h"
#include "GameEngineTexture.h"
#include "GameEngineSampler.h"

class GameEngineShaderResources
{
public:
	std::string Name;
	class GameEngineShader* ParentShader;
	int BindPoint = -1;
private:
	virtual void Setting() = 0;
	virtual void Reset() = 0;
};

class GameEngineConstantBufferSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineConstantBuffer> Res;

	const void* CPUDataPtr = nullptr;
	UINT DataSize = -1;

	void Setting() override;
	void Reset() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineTexture> Res;

	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	std::shared_ptr<GameEngineSampler> Res;

	void Setting() override;
	void Reset() override;
};

class GameEngineShaderResHelper
{
public:
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();

	void ShaderResCheck(std::string _FunctionName, class GameEngineShader* _Shader, ID3DBlob* _CompileCode);

	void ShaderResCopy(class GameEngineShader* _Shader);

	void AllShaderResourcesSetting();

	bool IsConstantBuffer(std::string_view _Name)
	{
		std::string Name{ _Name };
		return ConstantBufferSetters.contains(Name);
	}
	bool IsTexture(std::string_view _Name)
	{
		std::string Name{ _Name };
		return TextureSetters.contains(Name);
	}
	bool IsSampler(std::string_view _Name)
	{
		std::string Name{ _Name };
		return SamplerSetters.contains(Name);
	}

	template <typename DataType>
	void SetConstantBufferLink(std::string_view _Name, const DataType& _Data)
	{
		SetConstantBufferLink(_Name, &_Data, sizeof(_Data));
	}
	void SetConstantBufferLink(std::string_view _Name, const void* _Data, size_t _Size);

	void SetTexture(std::string_view _Name, std::string_view _TextureName);
	void SetTexture(std::string_view _Name, std::shared_ptr<GameEngineTexture> _Texture);
	void SetSampler(std::string_view _Name, std::shared_ptr<GameEngineSampler> _TextureSampler);

	void ResClear();
protected:

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;
};
