#pragma once
#include <filesystem>

class GameEnginePath
{
private:
	GameEnginePath() {}
	~GameEnginePath() {}
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;
public:
	static std::string_view FilenameToPath(const std::string_view& _Filename);
};