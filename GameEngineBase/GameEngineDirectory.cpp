#include "PreCompile.h"
#include "GameEngineDirectory.h"

#include "GameEngineFile.h"

std::vector<GameEngineFile> GameEngineDirectory::GetAllFile(std::vector<std::string> _Ext)
{
	std::filesystem::directory_iterator DirIter{ Path };

	std::vector<GameEngineFile> Result;
	for (const auto& Entry : DirIter)
	{
		if (Entry.is_directory())
		{
			continue;
		}

		for (const auto& Ext : _Ext)
		{
			if (Entry.path().extension().string() == Ext)
			{
				Result.push_back(Entry.path());
				break;
			}
		}
	}

	return Result;
}
