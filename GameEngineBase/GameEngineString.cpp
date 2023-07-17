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

//std::wstring_view GameEngineString::AnsiToUnicode(const std::string_view& _Text)
//{
//	std::wstring_view Result;
//	int Size = MultiByteToWideChar(CP_ACP, 0, _Text.c_str(),
//		static_cast<int>(_Text.size()), nullptr, 0);
//
//	Result.resize(Size);
//	MultiByteToWideChar(CP_ACP, 0, _Text.c_str(),
//		static_cast<int>(_Text.size()), &Result[0], Size);
//
//	return Result;
//}
//
//std::string_view GameEngineString::UnicodeToAnsi(const std::wstring_view& _Text)
//{
//	int Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(),
//		static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);
//	if (!Size)
//	{
//		GameEngineDebug::MsgBoxAssert("문자열 반환 실패");
//		return std::string_view();
//	}
//
//	std::string_view Result;
//	Result.resize(Size);
//
//	Size = WideCharToMultiByte(CP_ACP, 0, _Text.c_str(),
//		static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
//	if (!Size)
//	{
//		GameEngineDebug::MsgBoxAssert("문자열 반환 실패");
//		return std::string_view();
//	}
//
//	return Result;
//}
//
//std::string_view GameEngineString::UnicodeToUTF8(const std::wstring_view& _Text)
//{
//	int Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(),
//		static_cast<int>(_Text.size()), nullptr, 0, nullptr, 0);
//	if (!Size)
//	{
//		GameEngineDebug::MsgBoxAssert("문자열 반환 실패");
//		return std::string_view();
//	}
//
//	std::string_view Result;
//	Result.resize(Size);
//
//	Size = WideCharToMultiByte(CP_UTF8, 0, _Text.c_str(),
//		static_cast<int>(_Text.size()), &Result[0], Size, nullptr, nullptr);
//	if (!Size)
//	{
//		GameEngineDebug::MsgBoxAssert("문자열 반환 실패");
//		return std::string_view();
//	}
//
//	return Result;
//}
//
//std::string_view GameEngineString::AnsiToUTF8(const std::string_view& _Text)
//{
//	std::wstring_view Unicode = AnsiToUnicode(_Text);
//	return UnicodeToUTF8(Unicode);
//}
