#include "PreCompile.h"
#include "GameEngineTime.h"

LARGE_INTEGER GameEngineTime::Freq = {};
LARGE_INTEGER GameEngineTime::Prev = {};
LARGE_INTEGER GameEngineTime::Cur = {};
double GameEngineTime::Delta = 0.f;

void GameEngineTime::Init()
{
	QueryPerformanceFrequency(&Freq);
	QueryPerformanceCounter(&Cur);
	Prev = Cur;
}

void GameEngineTime::Reset()
{
	QueryPerformanceCounter(&Prev);
}

void GameEngineTime::Update()
{
	QueryPerformanceCounter(&Cur);
	Delta = static_cast<double>(Cur.QuadPart - Prev.QuadPart) / static_cast<double>(Freq.QuadPart);
	Prev = Cur;
}
