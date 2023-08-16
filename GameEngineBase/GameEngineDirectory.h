#pragma once
#include <vector>
#include <string_view>
#include "GameEnginePath.h"

class GameEngineDirectory
{
private:

protected:

public:
	static std::vector<GameEnginePath> GetAllFile(std::string_view _DirName,
		std::string_view _ExtName);

#pragma region Constructor
	GameEngineDirectory();
	~GameEngineDirectory();
	GameEngineDirectory(const GameEngineDirectory&) = delete;
	GameEngineDirectory(GameEngineDirectory&&) noexcept = delete;
	void operator=(const GameEngineDirectory&) = delete;
	void operator=(GameEngineDirectory&&) noexcept = delete;
#pragma endregion
};

