#include "PreCompile.h"
#include "GameEngineString.h"

std::string GameEngineString::ToUpperReturn(std::string_view _Str)
{
	std::string Upper(_Str);

	for (auto& Ch : Upper)
	{
		Ch = toupper(Ch);
	}

	return Upper;
}

std::wstring GameEngineString::AnsiToUnicode(std::string_view _Text)
{
	std::wstring Result;
	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.data(),
		static_cast<int>(_Text.size()), nullptr, 0);

	Result.resize(Size);
	MultiByteToWideChar(CP_ACP, 0, _Text.data(),
		static_cast<int>(_Text.size()), &Result[0], Size);

	return Result;
}

std::string GameEngineString::UnicodeToAnsi(std::wstring_view _Text)
{
	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(),
		static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);
	if (!Size)
	{
		GameEngineDebug::MsgBoxAssert("문자열 반환 실패");
		return std::string();
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_ACP, 0, _Text.data(),
		static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
	if (!Size)
	{
		GameEngineDebug::MsgBoxAssert("문자열 반환 실패");
		return std::string();
	}

	return Result;
}

std::string GameEngineString::UnicodeToUTF8(std::wstring_view _Text)
{
	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(),
		static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);
	if (!Size)
	{
		GameEngineDebug::MsgBoxAssert("문자열 반환 실패");
		return std::string();
	}

	std::string Result;
	Result.resize(Size);

	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.data(),
		static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
	if (!Size)
	{
		GameEngineDebug::MsgBoxAssert("문자열 반환 실패");
		return std::string();
	}

	return Result;
}

std::string GameEngineString::AnsiToUTF8(std::string_view _Text)
{
	std::wstring_view Unicode = AnsiToUnicode(_Text);
	return UnicodeToUTF8(Unicode);
}
