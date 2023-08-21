#include "PreCompile.h"
#include "GameEngineVertexShader.h"

#pragma comment(lib, "d3d11")
#pragma comment(lib, "d3dcompiler")

void GameEngineVertexShader::ShaderLoad(
	std::string_view _Path,
	std::string_view _EntryPoint,
	UINT _VersionHigh,
	UINT _VersionLow)
{
	std::wstring UniPath = GameEngineString::AnsiToUnicode(_Path);

	CreateVersion(ShaderType::Vertex, _VersionHigh, _VersionLow);

	EntryName = _EntryPoint;

#ifdef _DEBUG
	int iFlag = D3D10_SHADER_DEBUG;
#else
	int iFlag = 0;
#endif

	iFlag |= D3DCOMPILE_PACK_MATRIX_ROW_MAJOR;

	ID3DBlob* Error = nullptr;

	HRESULT Hresult = D3DCompileFromFile(
		UniPath.c_str(),
		nullptr,
		D3D_COMPILE_STANDARD_FILE_INCLUDE,
		EntryName.c_str(),
		Version.c_str(),
		iFlag,
		0,
		&BinaryCode,
		&Error);
	if (Hresult == E_FAIL)
	{
		std::string ErrorString =
			reinterpret_cast<char*>(Error->GetBufferPointer());

		MsgBoxAssert(ErrorString);
		return;
	}

	Hresult = GameEngineCore::MainDevice.GetDevice()->CreateVertexShader(
		BinaryCode->GetBufferPointer(),
		BinaryCode->GetBufferSize(),
		nullptr,
		&pShader);
	if (Hresult == E_FAIL)
	{
		MsgBoxAssert("버텍스 쉐이더 생성에 실패했습니다.");
		return;
	}
}

void GameEngineVertexShader::Setting()
{
	GameEngineCore::MainDevice.GetContext()->VSSetShader(pShader, nullptr, 0);
}
