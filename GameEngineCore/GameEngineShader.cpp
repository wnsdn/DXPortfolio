#include "PreCompile.h"
#include "GameEngineShader.h"

GameEngineShader::~GameEngineShader()
{
	SafeRelease(BinaryCode);
}

void GameEngineShader::CreateVersion(ShaderType _Type, UINT _VersionHigh,
	UINT _VersionLow)
{
	ShaderTypeValue = _Type;

	switch (_Type)
	{
	case ShaderType::None:
	{
		assert(false);
		break;
	}
	case ShaderType::Vertex:
		Version = "vs";
		break;
	case ShaderType::Geometry:
		Version = "gs";
		break;
	case ShaderType::Pixel:
		Version = "ps";
		break;
	case ShaderType::Max:
	{
		assert(false);
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

void GameEngineShader::ShaderResCheck()
{
	ResHelper.ShaderResCheck(EntryName, this, BinaryCode);
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

			GameEngineVertexShader::Load(_File.GetPath(), EntryName);
		}
	}

	{
		size_t EntryIndex = ShaderCode.find("_GS(");
		if (EntryIndex != std::string::npos)
		{
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			auto EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			//GameEnginePixelShader::Load(_File.GetPath(), EntryName);
		}
	}

	{
		size_t EntryIndex = ShaderCode.find("_PS(");
		if (EntryIndex != std::string::npos)
		{
			size_t FirstIndex = ShaderCode.find_last_of(" ", EntryIndex);
			auto EntryName = ShaderCode.substr(FirstIndex + 1, EntryIndex - FirstIndex + 2);

			GameEnginePixelShader::Load(_File.GetPath(), EntryName);
		}
	}

	return true;
}
