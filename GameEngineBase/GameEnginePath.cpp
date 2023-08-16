#include "PreCompile.h"
#include "GameEnginePath.h"

void GameEnginePath::FilenameToPath(std::string_view _Filename)
{
	std::filesystem::path ResPath = std::filesystem::current_path();

	while (true)
	{
		std::filesystem::directory_iterator DirIter(ResPath);
		bool Find = false;

		for (auto& Dir : DirIter)
		{
			if (Dir.path().filename() == "Resource")
			{
				ResPath = Dir;
				Find = true;
				break;
			}
		}

		if (Find)
		{
			break;
		}

		ResPath = ResPath.parent_path();

		if (ResPath == ResPath.root_path())
		{
			GameEngineDebug::MsgBoxAssert(_Filename);
			return;
		}
	}

	std::filesystem::recursive_directory_iterator RecDirIter(ResPath);
	for (auto& Dir : RecDirIter)
	{
		if (Dir.path().filename() == _Filename)
		{
			Path = Dir.path();
		}
	}

	GameEngineDebug::MsgBoxAssert(_Filename);
	return;
}