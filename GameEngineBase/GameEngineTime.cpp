#include "GameEngineTime.h"

LARGE_INTEGER GameEngineTime::Freq = {};
LARGE_INTEGER GameEngineTime::Prev = {};
LARGE_INTEGER GameEngineTime::Cur = {};
double GameEngineTime::DoubleDelta = 0.f;
float GameEngineTime::FloatDelta = 0.f;

GameEngineTime::GameEngineTime()
{
}

GameEngineTime::~GameEngineTime()
{
}

void GameEngineTime::Init()
{
	QueryPerformanceFrequency(&Freq);
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(&Cur);
	DoubleDelta = static_cast<double>(Cur.QuadPart - Prev.QuadPart)
		/ static_cast<double>(Freq.QuadPart);
	FloatDelta = static_cast<float>(DoubleDelta);
	Prev = Cur;
}
