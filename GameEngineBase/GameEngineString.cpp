#include "GameEngineString.h"
#include "GameEngineDebug.h"
#include <Windows.h>

GameEngineString::GameEngineString()
{
}

GameEngineString::~GameEngineString()
{
}

std::string GameEngineString::ToUpperReturn(const std::string& _Str)
{
	std::string Upper = _Str;

	for (auto& Ch : Upper)
	{
		Ch = toupper(Ch);
	}

	return Upper;
}

std::wstring GameEngineString::AnsiToUnicode(const std::string& _Text)
{
	std::wstring Result;
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(), 
		static_cast<int>(_Text.size()), nullptr, 0);

	Result.resize(Size);
	MultiByteToWideChar(CP_ACP, 0, _Text.c_str(),
		static_cast<int>(_Text.size()), &Result[0], Size);

	return Result;
}

std::string GameEngineString::UnicodeToAnsi(const std::wstring& _Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(),
		static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);
	if (!Size)
	{
		MsgBoxAssert("문자열 반환 실패");
		return std::string();
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(),
		static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
	if (!Size)
	{
		MsgBoxAssert("문자열 반환 실패");
		return std::string();
	}

	return Result;
}

std::string GameEngineString::UnicodeToUTF8(const std::wstring& _Text)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(),
		static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);
	if (!Size)
	{
		MsgBoxAssert("문자열 반환 실패");
		return std::string();
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(),
		static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
	if (!Size)
	{
		MsgBoxAssert("문자열 반환 실패");
		return std::string();
	}

	return Result;
}

std::string GameEngineString::AnsiToUTF8(const std::string& _Text)
{
	std::wstring Unicode = AnsiToUnicode(_Text);
	return UnicodeToUTF8(Unicode);
}
