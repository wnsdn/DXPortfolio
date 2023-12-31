#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"

class GameEnginePixelShader : public GameEngineResources<GameEnginePixelShader>, public GameEngineShader
{
public:
	GameEnginePixelShader() {}
	~GameEnginePixelShader();
	GameEnginePixelShader(const GameEnginePixelShader&) = delete;
	GameEnginePixelShader(GameEnginePixelShader&&) noexcept = delete;
	void operator=(const GameEnginePixelShader&) = delete;
	void operator=(GameEnginePixelShader&&) noexcept = delete;

	static std::shared_ptr<GameEnginePixelShader> Load(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		auto Res = CreateRes(_EntryPoint);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	void Setting();
private:
	void ShaderLoad(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHigh = 5, UINT _VersionLow = 0);

	ID3D11PixelShader* ShaderPtr = nullptr;
};
