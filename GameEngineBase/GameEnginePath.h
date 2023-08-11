#pragma once
#include <filesystem>
#include <string_view>

class GameEnginePath
{
private:
	std::filesystem::path Path{};
public:
	void FilenameToPath(std::string_view _Filename);
#pragma region Constructor
	GameEnginePath() {}
	~GameEnginePath() {}
	GameEnginePath(const GameEnginePath& _Other) = delete;
	GameEnginePath(GameEnginePath&& _Other) noexcept = delete;
	GameEnginePath& operator=(const GameEnginePath& _Other) = delete;
	GameEnginePath& operator=(GameEnginePath&& _Other) noexcept = delete;
	void operator=(std::string_view _Path)
	{
		Path = _Path;
	}
#pragma endregion
};