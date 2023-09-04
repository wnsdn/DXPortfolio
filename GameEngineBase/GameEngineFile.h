#pragma once
#include "GameEnginePath.h"
#include "GameEngineSerializer.h"

enum class FileOpenType
{
	Write,
	Read,
};

enum class FileDataType
{
	Binary,
	Text,
};

class GameEngineFile : public GameEnginePath
{
private:
	FILE* pFile = nullptr;
	FileOpenType OpenType;
	FileDataType DataType;
	GameEngineSerializer Serializer;
public:
	~GameEngineFile();

	void Open(FileOpenType _OpenType, FileDataType _DataType, bool _IsStartAllData = true);
	void Read(void* _Data, size_t _Size);
	//void Write(void* _Data, size_t _Size);

	template <typename ReturnType>
	ReturnType GetFileSize()
	{
		return static_cast<ReturnType>(std::filesystem::file_size(Path));
	}
	std::string_view GetStringView()
	{
		return Serializer.GetDataPtr<const char>();
	}
};

