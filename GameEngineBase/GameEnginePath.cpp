#include "PreCompile.h"
#include "GameEnginePath.h"

std::string GameEnginePath::FilenameToPath(const std::string& _Filename)
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
			GameEngineDebug::MsgBoxAssert("GameEnginePath::FilenameToPath(1) " + _Filename);
			return std::string();
		}
	}

	std::filesystem::recursive_directory_iterator RecDirIter(ResPath);
	for (auto& Dir : RecDirIter)
	{
		if (Dir.path().filename() == _Filename)
		{
			return Dir.path().string();
		}
	}

	GameEngineDebug::MsgBoxAssert("GameEnginePath::FilenameToPath(2) " + _Filename);
	return std::string();
}
