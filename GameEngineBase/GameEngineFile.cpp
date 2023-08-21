#include "PreCompile.h"
#include "GameEngineFile.h"
#include "GameEngineDebug.h"

void GameEngineFile::Open(FileOpenType _OpenType, FileDataType _DataType, bool _IsStartAllData)
{
	std::string Mode{};

	switch (_OpenType)
	{
	case FileOpenType::Write:
		Mode += "w";
		break;
	case FileOpenType::Read:
		Mode += "r";
		break;
	}

	switch (_DataType)
	{
	case FileDataType::Binary:
		Mode += "b";
		break;
	case FileDataType::Text:
		Mode += "t";
		break;
	}

	fopen_s(&pFile, ToString().c_str(), Mode.c_str());

	OpenType = _OpenType;
	DataType = _DataType;

	if (_IsStartAllData)
	{
		Serializer.SetSize(GetFileSize<size_t>());
		Read(Serializer.GetDataPtr<void>(), Serializer.GetSize());
	}
}

void GameEngineFile::Read(void* _Data, size_t _Size)
{
	if (!pFile)
	{
		MsgBoxAssert("열리지 않은 파일을 읽으려고 했습니다. Open을 먼저 실행해주세요.");
	}
	if (OpenType != FileOpenType::Read)
	{
		MsgBoxAssert("읽기 모드로 열리지 않은 파일입니다.");
	}

	fread_s(_Data, _Size, _Size, 1, pFile);
}
