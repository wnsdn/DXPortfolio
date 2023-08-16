#include "PreCompile.h"
#include "GameEngineDirectory.h"

GameEngineDirectory::GameEngineDirectory()
{
}

GameEngineDirectory::~GameEngineDirectory()
{
}

std::vector<GameEnginePath> GameEngineDirectory::GetAllFile(
	std::string_view _DirName, std::string_view _ExtName)
{
	std::filesystem::path Path = std::filesystem::current_path();

	while (true)
	{
		std::filesystem::directory_iterator DirIter{ Path };
		bool Check = false;
		for (auto& Dir : DirIter)
		{
			if (Dir.path().filename() == _DirName)
			{
				Check = true;
				Path = Dir;
				break;
			}
		}

		if (Check)
		{
			break;
		}
		else
		{
			Path = Path.parent_path();
		}

		if (Path == Path.root_path())
		{
			GameEngineDebug::MsgBoxAssert(_DirName);
			return std::vector<GameEnginePath>();
		}
	}

	std::vector<GameEnginePath> VecPath;
	std::filesystem::directory_iterator DirIter{ Path };
	for (auto& Dir : DirIter)
	{
		if (Dir.path().extension() == _ExtName)
		{
			VecPath.emplace_back(Dir);
		}
	}

	return VecPath;
}