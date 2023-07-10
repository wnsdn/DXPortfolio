#pragma once
#include <random>

class GameEngineRandom
{
public:
	static int RandomInt(int _Max, int _Min);
private:
	static std::random_device Seed;
	static std::mt19937 Gen;

	GameEngineRandom();
	~GameEngineRandom();
	GameEngineRandom(const GameEngineRandom& _Other) = delete;
	GameEngineRandom(GameEngineRandom&& _Other) noexcept = delete;
	GameEngineRandom& operator=(const GameEngineRandom& _Other) = delete;
	GameEngineRandom& operator=(GameEngineRandom&& _Other) noexcept = delete;
};