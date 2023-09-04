#include "PreCompile.h"
#include "GameEngineDirectory.h"

std::vector<GameEnginePath> GameEngineDirectory::GetAllPathByExt(std::vector<std::string> _ExtArr)
{
	std::vector<GameEnginePath> Result;

	if (!std::filesystem::exists(Path))
	{
		assert(false);
		return std::vector<GameEnginePath>();
	}

	std::filesystem::directory_iterator RDI{ Path };
	for (auto& Entry : RDI)
	{
		for (auto& Ext : _ExtArr)
		{
			if (Entry.path().extension().string() == Ext)
			{
				GameEnginePath NewPath;
				NewPath.SetPath(Entry.path().string());
				Result.push_back(NewPath);
				break;
			}
		}
	}

	return Result;
}

std::vector<GameEnginePath> GameEngineDirectory::GetAllFileInDir(std::string_view _Directory)
{
	std::vector<GameEnginePath> Result;
	if (_Directory.data())
	{
		Path.append(_Directory);
	}

	if (!std::filesystem::exists(Path))
	{
		assert(false);
		return std::vector<GameEnginePath>();
	}

	std::filesystem::recursive_directory_iterator RDI{ Path };
	for (auto& Entry : RDI)
	{
		if (std::filesystem::is_directory(Entry))
		{
			continue;
		}

		GameEnginePath NewPath;
		NewPath.SetPath(Entry.path().string());
		Result.push_back(NewPath);
	}

	return Result;
}

std::vector<GameEnginePath> GameEngineDirectory::GetAllDirInDir(std::string_view _Directory)
{
	std::vector<GameEnginePath> Result;
	Path.append(_Directory);

	if (!std::filesystem::exists(Path))
	{
		assert(false);
		return std::vector<GameEnginePath>();
	}

	std::filesystem::recursive_directory_iterator RDI{ Path };
	for (auto& Entry : RDI)
	{
		if (!std::filesystem::is_directory(Entry))
		{
			continue;
		}

		GameEnginePath NewPath;
		NewPath.SetPath(Entry.path().string());
		Result.push_back(NewPath);
	}

	return Result;
}
