#include "PreCompile.h"
#include "GameEngineShader.h"

#include <GameEngineBase/GameEngineFile.h>

void GameEngineShader::CreateVersion(ShaderType _Type, UINT _VersionHigh,
	UINT _VersionLow)
{
	ShaderTypeValue = _Type;

	switch (_Type)
	{
	case ShaderType::None:
		MsgBoxAssert("쉐이더 타입이 잘못들어왔습니다.");
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
		MsgBoxAssert("쉐이더 타입이 잘못들어왔습니다.");
		break;
	default:
		break;
	}

	Version += "_";
	Version += std::to_string(_VersionHigh);
	Version += "_";
	Version += std::to_string(_VersionLow);
}

#include "GameEngineVertexShader.h"

bool GameEngineShader::AutoCompile(GameEngineFile& _File)
{
	_File.Open(FileOpenType::Read, FileDataType::Text);
	std::string_view ShaderCode = _File.GetStringView();

	{
		size_t EntryIndex = ShaderCode.find("_VS(");
		if (EntryIndex != std::string::npos)
		{
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			std::string_view EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEngineVertexShader::Load(_File.ToString(), EntryName);
		}
	}

	{
		size_t EntryIndex = ShaderCode.find("_PS(");
		if (EntryIndex != std::string::npos)
		{
			int a = 0;
		}
	}

	return true;
}
