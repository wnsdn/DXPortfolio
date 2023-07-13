#include "PreCompile.h"
#include "GameEngineInput.h"

GameEngineInput::GameEngineKey GameEngineInput::AllKey[255] = {};

void GameEngineInput::Init()
{
	for (int i = 0; i < 255; ++i)
	{
		AllKey[i] = GameEngineKey(i);
	}
}

void GameEngineInput::Reset()
{
	for (int i = 0; i < 255; ++i)
	{
		if (AllKey[i].Press)
		{
			AllKey[i].Down = false;
			AllKey[i].Press = false;
			AllKey[i].Up = true;
			AllKey[i].Free = true;
		}
		else if (AllKey[i].Up)
		{
			AllKey[i].Down = false;
			AllKey[i].Press = false;
			AllKey[i].Up = false;
			AllKey[i].Free = true;
		}
	}
}

void GameEngineInput::Update()
{
	for (int i = 0; i < 255; ++i)
	{
		if (GetAsyncKeyState(AllKey[i].Key))
		{
			if (AllKey[i].Free)
			{
				AllKey[i].Down = true;
				AllKey[i].Press = true;
				AllKey[i].Up = false;
				AllKey[i].Free = false;
			}
			else if (AllKey[i].Down)
			{
				AllKey[i].Down = false;
				AllKey[i].Press = true;
				AllKey[i].Up = false;
				AllKey[i].Free = false;
			}
		}
		else
		{
			if (AllKey[i].Press)
			{
				AllKey[i].Down = false;
				AllKey[i].Press = false;
				AllKey[i].Up = true;
				AllKey[i].Free = true;
			}
			else if (AllKey[i].Up)
			{
				AllKey[i].Down = false;
				AllKey[i].Press = false;
				AllKey[i].Up = false;
				AllKey[i].Free = true;
			}
		}
	}
}
