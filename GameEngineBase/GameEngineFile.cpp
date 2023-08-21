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
		MsgBoxAssert("������ ���� ������ �������� �߽��ϴ�. Open�� ���� �������ּ���.");
	}
	if (OpenType != FileOpenType::Read)
	{
		MsgBoxAssert("�б� ���� ������ ���� �����Դϴ�.");
	}

	fread_s(_Data, _Size, _Size, 1, pFile);
}
