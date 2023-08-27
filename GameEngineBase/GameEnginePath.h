#pragma once
#include <filesystem>

class GameEnginePath
{
protected:
	std::filesystem::path Path{};
public:
	void SetPath(std::string_view _Name);

	std::string ToString() const
	{
		return Path.string();
	}
	std::string GetExtension() const
	{
		return Path.extension().string();
	}
	std::string GetFilename() const
	{
		return Path.filename().string();
	}

	GameEnginePath() {}
	GameEnginePath(std::string_view _Path)
		: Path(_Path) {}
	GameEnginePath(const std::filesystem::path& _Path)
		: Path(_Path) {}
};