#pragma once
#include <random>
#include "GameEngineMath.h"

class GameEngineRandom
{
private:
	static std::random_device Seed;
	static std::mt19937_64 Gen;

	GameEngineRandom() {}
	~GameEngineRandom() {}
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;
public:
	static int RandomInt(int _Max, int _Min);
	static float RandomFloat(float _Max, float _Min);
	static float4 RandomVectorBox2D(float _MinX, float _MaxX, float _MinY, float _MaxY);
};