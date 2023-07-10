#pragma once
#include <filesystem>

class GameEnginePath
{
public:
	static std::string FilenameToPath(const std::string& _Filename);
private:
	GameEnginePath();
	~GameEnginePath();
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;
};