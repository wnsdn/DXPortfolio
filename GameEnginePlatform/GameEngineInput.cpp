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
		AllKey[i].Reset();
	}
}

void GameEngineInput::Update()
{
	for (int i = 0; i < 255; ++i)
	{
		AllKey[i].Update();
	}
}

void GameEngineInput::GameEngineKey::Reset()
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

void GameEngineInput::GameEngineKey::Update()
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