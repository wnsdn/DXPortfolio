#pragma once
#include <filesystem>

class GameEnginePath
{
protected:
	std::filesystem::path Path{};
public:
	void SetPath(std::string_view _Path);
	void SetFilenameToPath(std::string_view _Filename);

	std::string GetPath() const
	{
		return Path.string();
	}
	std::string GetFilename() const
	{
		return Path.filename().string();
	}
	std::string GetExtension() const
	{
		return Path.extension().string();
	}
};