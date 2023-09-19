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

	GameEngineShader() = default;
	~GameEngineShader() = default;
	GameEngineShader(const GameEngineShader&) = delete;
	GameEngineShader(GameEngineShader&&) noexcept = delete;
	void operator=(const GameEngineShader&) = delete;
	void operator=(GameEngineShader&&) noexcept = delete;

	GameEngineShaderResHelper ResHelper;
protected:
	void CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow);

	std::string Version;
	ID3DBlob* BinaryCode = nullptr;
private:
	ShaderType ShaderTypeValue = ShaderType::None;
};

