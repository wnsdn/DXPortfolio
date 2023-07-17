#pragma once
#include <filesystem>
#include <string_view>

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
	static std::string FilenameToPath(std::string_view _Filename);
};