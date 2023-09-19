#pragma once

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
	void Setting() override;
	void Reset() override;
};

class GameEngineTextureSetter : public GameEngineShaderResources
{
public:
	void Setting() override;
	void Reset() override;
};

class GameEngineSamplerSetter : public GameEngineShaderResources
{
public:
	void Setting() override;
	void Reset() override;
};

class GameEngineShaderResHelper
{
public:
	GameEngineShaderResHelper();
	~GameEngineShaderResHelper();
	GameEngineShaderResHelper(const GameEngineShaderResHelper&) = delete;
	GameEngineShaderResHelper(GameEngineShaderResHelper&&) noexcept = delete;
	void operator=(const GameEngineShaderResHelper&) = delete;
	void operator=(GameEngineShaderResHelper&&) noexcept = delete;

	void ShaderResCheck(std::string _FunctionName, ID3DBlob* _CompileCode);
protected:

private:
	std::multimap<std::string, GameEngineConstantBufferSetter> ConstantBufferSetters;
	std::multimap<std::string, GameEngineTextureSetter> TextureSetters;
	std::multimap<std::string, GameEngineSamplerSetter> SamplerSetters;
};
