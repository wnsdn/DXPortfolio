#pragma once
#include <string>

class GameEngineString
{
public:
	static std::string ToUpperReturn(const std::string& _Str);
	static std::wstring AnsiToUnicode(const std::string& _Text);
	static std::string UnicodeToAnsi(const std::wstring& _Text);
	static std::string UnicodeToUTF8(const std::wstring& _Text);
	static std::string AnsiToUTF8(const std::string& _Text);
private:
	GameEngineString();
	~GameEngineString();
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
};