#pragma once
#include <GameEngineBase/GameEnginePath.h>
#include "GameEngineShader.h"
#include "GameEngineResources.h"
#include <string_view>
#include <d3dcompiler.h>

class GameEngineVertexShader
	: public GameEngineResources<GameEngineVertexShader>
	, public GameEngineShader
{
private:
	std::string EntryName;

	void ShaderLoad(std::string_view _Path, std::string_view _EntryPoint,
		UINT _VersionHigh = 5, UINT _VersionLow = 0);
protected:

public:
	static std::shared_ptr<GameEngineVertexShader> Load(
		std::string_view _Path, std::string_view _EntryPoint,
		UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		GameEnginePath Path = _Path;
		std::string Name = Path.GetFilename();

		auto Res = GameEngineVertexShader::CreateRes(Name);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

#pragma region Constructor
	GameEngineVertexShader();
	~GameEngineVertexShader();
	GameEngineVertexShader(const GameEngineVertexShader&) = delete;
	GameEngineVertexShader(GameEngineVertexShader&&) noexcept = delete;
	void operator=(const GameEngineVertexShader&) = delete;
	void operator=(GameEngineVertexShader&&) noexcept = delete;
#pragma endregion
};

