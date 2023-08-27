#include "PreCompile.h"
#include "GameEngineShader.h"

void GameEngineShader::CreateVersion(ShaderType _Type, UINT _VersionHigh,
	UINT _VersionLow)
{
	ShaderTypeValue = _Type;

	switch (_Type)
	{
	case ShaderType::None:
	{
		MsgBoxAssert("���̴� Ÿ���� �߸����Խ��ϴ�.");
		break;
	}
	case ShaderType::Vertex:
		Version = "vs";
		break;
	case ShaderType::Pixel:
		Version = "ps";
		break;
	case ShaderType::Max:
	{
		MsgBoxAssert("���̴� Ÿ���� �߸����Խ��ϴ�.");
		break;
	}
	default:
		break;
	}

	Version += "_";
	Version += std::to_string(_VersionHigh);
	Version += "_";
	Version += std::to_string(_VersionLow);
}

#include "GameEngineVertexShader.h"
#include "GameEnginePixelShader.h"

bool GameEngineShader::AutoCompile(GameEngineFile& _File)
{
	_File.Open(FileOpenType::Read, FileDataType::Text);
	auto ShaderCode = _File.GetStringView();

	{
		size_t EntryIndex = ShaderCode.find("_VS(");
		if (EntryIndex != std::string::npos)
		{
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			auto EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEngineVertexShader::Load(_File.ToString(), EntryName);
		}
	}

	{
		size_t EntryIndex = ShaderCode.find("_PS(");
		if (EntryIndex != std::string::npos)
		{
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			auto EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEnginePixelShader::Load(_File.ToString(), EntryName);
		}
	}

	return true;
}
