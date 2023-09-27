#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"

class GameEngineGeometryShader : public GameEngineResources<GameEngineGeometryShader>, public GameEngineShader
{
	friend class GameEngineInputLayout;
public:
	GameEngineGeometryShader() {}
	~GameEngineGeometryShader();
	GameEngineGeometryShader(const GameEngineGeometryShader&) = delete;
	GameEngineGeometryShader(GameEngineGeometryShader&&) noexcept = delete;
	void operator=(const GameEngineGeometryShader&) = delete;
	void operator=(GameEngineGeometryShader&&) noexcept = delete;

	static std::shared_ptr<GameEngineGeometryShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		auto Res = CreateRes(_EntryPoint);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	void Setting();
private:
	void ShaderLoad(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

	ID3D11GeometryShader* ShaderPtr = nullptr;
};
