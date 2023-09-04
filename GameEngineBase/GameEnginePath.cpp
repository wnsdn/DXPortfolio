#include "PreCompile.h"
#include "GameEnginePath.h"

void GameEnginePath::SetPath(std::string_view _Path)
{
	Path = _Path;
}

void GameEnginePath::SetFilenameToPath(std::string_view _Filename)
{
	auto FindPath = std::filesystem::current_path();
	bool Find = false;

	while (true)
	{
		std::filesystem::directory_iterator DI{ FindPath };
		for (auto& Entry : DI)
		{
			if (Entry.path().filename().string() == _Filename)
			{
				Path = Entry;
				Find = true;
				break;
			}
		}

		if (!Find)
		{
			FindPath = FindPath.parent_path();

			if (FindPath == FindPath.root_path())
			{
				assert(false);
				return;
			}
		}
		else
		{
			break;
		}
	}
}
