#pragma once
#include "GameEnginePath.h"

class GameEngineDirectory : public GameEnginePath
{
public:
	std::vector<GameEnginePath> GetAllPathByExt(std::vector<std::string> _ExtArr);
	std::vector<GameEnginePath> GetAllFileInDir(std::string_view _Directory = std::string_view());
	std::vector<GameEnginePath> GetAllDirInDir(std::string_view _Directory = std::string_view());
};
