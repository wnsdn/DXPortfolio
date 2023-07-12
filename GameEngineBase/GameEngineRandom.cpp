#include "PreCompile.h"
#include "GameEngineRandom.h"

std::random_device GameEngineRandom::Seed;
std::mt19937 GameEngineRandom::Gen(Seed());

int GameEngineRandom::RandomInt(int _Max, int _Min)
{
	std::uniform_int_distribution<int> RndInt(_Min, _Max);

	return RndInt(Gen);
}
