#pragma once
#include <string>
#include <d3d11.h>

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
private:
	ShaderType ShaderTypeValue = ShaderType::None;
protected:
	std::string Version;
	ID3DBlob* BinaryCode = nullptr;

	void CreateVersion(ShaderType _Type, UINT _VersionHigh, UINT _VersionLow);
public:
	static bool AutoCompile(GameEngineFile& _File);

	GameEngineShader() = default;
	~GameEngineShader() = default;
	GameEngineShader(const GameEngineShader&) = delete;
	GameEngineShader(GameEngineShader&&) noexcept = delete;
	void operator=(const GameEngineShader&) = delete;
	void operator=(GameEngineShader&&) noexcept = delete;
};

