#include "PreCompile.h"
#include "GameEngineRandom.h"

std::random_device GameEngineRandom::Seed;
std::mt19937_64 GameEngineRandom::Gen(Seed());

int GameEngineRandom::RandomInt(int _Max, int _Min)
{
	std::uniform_int_distribution<int> RndInt(_Min, _Max);

	return RndInt(Gen);
}

float GameEngineRandom::RandomFloat(float _Max, float _Min)
{
	std::uniform_real_distribution<float> RndFloat(_Min, _Max);

	return RndFloat(Gen);
}
