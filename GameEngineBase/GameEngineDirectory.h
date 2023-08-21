#pragma once
#include "GameEnginePath.h"

class GameEngineFile;
class GameEngineDirectory : public GameEnginePath
{
public:
	std::vector<GameEngineFile> GetAllFile(std::vector<std::string> _Ext);
};
