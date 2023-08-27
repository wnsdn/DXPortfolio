#include "PreCompile.h"
#include "GameEnginePixelShader.h"

GameEnginePixelShader::~GameEnginePixelShader()
{
	if (ShaderPtr)
	{
		ShaderPtr->Release();
		ShaderPtr = nullptr;
	}
}

void GameEnginePixelShader::ShaderLoad(
	std::string_view _Path,
	std::string_view _EntryPoint,
	UINT _VersionHigh,
	UINT _VersionLow)
{
	std::wstring UniPath = GameEngineString::AnsiToUnicode(_Path);
	CreateVersion(ShaderType::Pixel, _VersionHigh, _VersionLow);
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
		std::string ErrorString = reinterpret_cast<char*>(Error->GetBufferPointer());
		MsgBoxAssert(ErrorString);
		return;
	}

	Hresult = GameEngineCore::GetDevice()->CreatePixelShader(
		BinaryCode->GetBufferPointer(),
		BinaryCode->GetBufferSize(),
		nullptr,
		&ShaderPtr);
	if (Hresult == E_FAIL)
	{
		MsgBoxAssert("버텍스 쉐이더 생성에 실패했습니다.");
		return;
	}
}

void GameEnginePixelShader::Setting()
{
	GameEngineCore::GetContext()->PSSetShader(ShaderPtr, nullptr, 0);
}
