#pragma once
#include <filesystem>
#include <string_view>

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

	GameEnginePath() = default;
	GameEnginePath(const std::filesystem::path& _Path) : Path(_Path) {}
};