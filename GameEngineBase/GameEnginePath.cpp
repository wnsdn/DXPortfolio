#include "PreCompile.h"
#include "GameEnginePath.h"

void GameEnginePath::SetPath(std::string_view _Name)
{
	Path = std::filesystem::current_path();

	bool Find = false;
	while (true)
	{
		std::filesystem::directory_iterator DirIter(Path);
		for (const auto& Entry : DirIter)
		{
			if (Entry.path().filename() == _Name)
			{
				Path = Entry.path();
				Find = true;
				break;
			}
		}

		if (Find)
		{
			break;
		}
		else
		{
			Path = Path.parent_path();
		}

		if (Path == Path.root_path())
		{
			MsgBoxAssert(std::string(_Name) + "찾을수없습니다");
			break;
		}
	}
}
