#pragma once
#include "GameEngineShaderResHelper.h"

enum class ShaderType
{
	None = 0,
	Vertex,
	Hull,
	Tessellator,
	Domain,
	Geometry,
	Pixel,
	Max,
};

class GameEngineShader
{
public:
	static bool AutoCompile(GameEngineFile& _File);

	GameEngineShader() {}
	~GameEngineShader();
	GameEngineShader(const GameEngineShader&) = delete;
	GameEngineShader(GameEngineShader&&) noexcept = delete;
	void operator=(const GameEngineShader&) = delete;
	void operator=(GameEngineShader&&) noexcept = delete;

	ShaderType GetShaderType() const
	{
		return ShaderTypeValue;
	}

	GameEngineShaderResHelper ResHelper;
protected:
	void CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow);
	void ShaderResCheck();

	ID3DBlob* BinaryCode = nullptr;
	std::string Version;
	std::string EntryName = "";
private:
	ShaderType ShaderTypeValue = ShaderType::None;
};

