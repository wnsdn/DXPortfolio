#include "GameEngineInput.h"

GameEngineInput::GameEngineKey GameEngineInput::AllKey[255] = {};

GameEngineInput::GameEngineInput()
{
}

GameEngineInput::~GameEngineInput()
{
}

void GameEngineInput::GameEngineKey::Update(float _DeltaTime)
{
	if (GetAsyncKeyState(Key))
	{
		if (Free)
		{
			Down = true;
			Press = true;
			Up = false;
			Free = false;
		}
		else if (Down)
		{
			Down = false;
			Press = true;
			Up = false;
			Free = false;
		}
	}
	else
	{
		if (Press)
		{
			Down = false;
			Press = false;
			Up = true;
			Free = true;
		}
		else if (Up)
		{
			Down = false;
			Press = false;
			Up = false;
			Free = true;
		}
	}
}

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
		AllKey[i].Reset();
	}
}

void GameEngineInput::Update(float _Delta)
{
	for (int i = 0; i < 255; ++i)
	{
		AllKey[i].Update(_Delta);
	}
}

bool GameEngineInput::IsDown(int _Key)
{
	return AllKey[_Key].Down;
}

bool GameEngineInput::IsUp(int _Key)
{
	return AllKey[_Key].Up;
}

bool GameEngineInput::IsPress(int _Key)
{
	return AllKey[_Key].Press;
}

bool GameEngineInput::IsFree(int _Key)
{
	return AllKey[_Key].Free;
}	

