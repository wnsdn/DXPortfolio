#pragma once
#include <string>
#include <string_view>

class GameEngineString
{
private:
	GameEngineString() {}
	~GameEngineString() {}
	GameEngineString(const GameEngineString& _Other) = delete;
	GameEngineString(GameEngineString&& _Other) noexcept = delete;
	GameEngineString& operator=(const GameEngineString& _Other) = delete;
	GameEngineString& operator=(GameEngineString&& _Other) noexcept = delete;
public:
	static std::wstring AnsiToUnicode(std::string_view _Text);
	static std::string UnicodeToAnsi(std::wstring_view _Text);
	static std::string UnicodeToUTF8(std::wstring_view _Text);
	static std::string AnsiToUTF8(std::string_view _Text);
};