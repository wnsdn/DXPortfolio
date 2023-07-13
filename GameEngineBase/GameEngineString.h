#pragma once

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
	static std::string_view ToUpperReturn(const std::string_view& _Str);
	//static std::wstring_view AnsiToUnicode(const std::string_view& _Text);
	//static std::string_view UnicodeToAnsi(const std::wstring_view& _Text);
	//static std::string_view UnicodeToUTF8(const std::wstring_view& _Text);
	//static std::string_view AnsiToUTF8(const std::string_view& _Text);
};