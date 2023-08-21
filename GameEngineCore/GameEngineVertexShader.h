#pragma once
#include "GameEngineShader.h"
#include "GameEngineResources.h"
#include <d3d11.h>
#include <d3dcompiler.h>

class GameEngineVertexShader
	: public GameEngineResources<GameEngineVertexShader>
	, public GameEngineShader
{
private:
	std::string EntryName;
	ID3D11VertexShader* pShader = nullptr;

	void ShaderLoad(std::string_view _Path, std::string_view _EntryPoint,
		UINT _VersionHigh = 5, UINT _VersionLow = 0);
public:
	static std::shared_ptr<GameEngineVertexShader> Load(
		std::string_view _Path, std::string_view _EntryPoint,
		UINT _VersionHigh = 5, UINT _VersionLow = 0)
	{
		auto Res = GameEngineVertexShader::CreateRes(_EntryPoint);
		Res->ShaderLoad(_Path, _EntryPoint, _VersionHigh, _VersionLow);
		return Res;
	}

	void Setting();

	~GameEngineVertexShader()
	{
		pShader->Release();
		pShader = nullptr;
	}
	GameEngineVertexShader(const GameEngineVertexShader&) = delete;
	GameEngineVertexShader(GameEngineVertexShader&&) noexcept = delete;
	void operator=(const GameEngineVertexShader&) = delete;
	void operator=(GameEngineVertexShader&&) noexcept = delete;
};

