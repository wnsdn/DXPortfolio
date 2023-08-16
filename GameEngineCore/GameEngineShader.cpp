#include "PreCompile.h"
#include "GameEngineShader.h"

GameEngineShader::GameEngineShader()
{
}

GameEngineShader::~GameEngineShader()
{
}

void GameEngineShader::CreateVersion(ShaderType _Type, UINT _VersionHigh,
	UINT _VersionLow)
{
	ShaderTypeValue = _Type;

	switch (_Type)
	{
	case ShaderType::None:
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		break;
	case ShaderType::Vertex:
		Version = "vs";
		break;
	case ShaderType::Hull:
		break;
	case ShaderType::Tessellator:
		break;
	case ShaderType::Domain:
		break;
	case ShaderType::Geometry:
		break;
	case ShaderType::Pixel:
		Version = "ps";
		break;
	case ShaderType::Max:
		GameEngineDebug::MsgBoxAssert(__FUNCTION__);
		break;
	default:
		break;
	}

	Version += "_";
	Version += std::to_string(_VersionHigh);
	Version += "_";
	Version += std::to_string(_VersionLow);
}
