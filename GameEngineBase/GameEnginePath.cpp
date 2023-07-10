#include "GameEnginePath.h"
#include "GameEngineDebug.h"

GameEnginePath::GameEnginePath()
{
}

GameEnginePath::~GameEnginePath()
{
}

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
			MsgBoxAssert("FilenameToPath() ResPath " + _Filename);
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

	MsgBoxAssert("FilenameToPath() Path " + _Filename);
	return std::string();
}
