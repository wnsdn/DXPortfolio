#pragma once
#include <filesystem>
#include <string_view>

class GameEnginePath
{
private:
	std::filesystem::path Path{};
public:
	void FilenameToPath(std::string_view _Filename);
	std::string GetFilename() const
	{
		return Path.filename().string();
	}

#pragma region Constructor
	GameEnginePath() {}
	GameEnginePath(std::string_view _Path)
	{
		Path = _Path;
	}
	GameEnginePath(std::filesystem::directory_entry _Path)
	{
		Path = _Path;
	}
	~GameEnginePath() {}
	void operator=(std::string_view _Path)
	{
		Path = _Path;
	}
#pragma endregion
};