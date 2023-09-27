#include "PreCompile.h"
#include "GameEngineVertexShader.h"

GameEngineVertexShader::~GameEngineVertexShader()
{
	SafeRelease(ShaderPtr);
}

void GameEngineVertexShader::ShaderLoad(std::string_view _Path, std::string_view _EntryPoint, UINT _VersionHigh, UINT _VersionLow)
{
	std::wstring UniPath = GameEngineString::AnsiToUnicode(_Path);
	CreateVersion(ShaderType::Vertex, _VersionHigh, _VersionLow);
	EntryName = _EntryPoint;

#ifdef _DEBUG
	int iFlag = D3DCOMPILE_DEBUG | D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
#else
	int iFlag = D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;
#endif

	Check(D3DCompileFromFile(UniPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, EntryName.c_str(), Version.c_str(), iFlag, 0, &BinaryCode, nullptr));
	Check(GameEngineCore::GetDevice()->CreateVertexShader(BinaryCode->GetBufferPointer(), BinaryCode->GetBufferSize(), nullptr, &ShaderPtr));

	ShaderResCheck();
}

void GameEngineVertexShader::Setting()
{
	GameEngineCore::GetContext()->VSSetShader(ShaderPtr, nullptr, 0);
}
