#include "PreCompile.h"
#include "GameEngineInput.h"

GameEngineInput::GameEngineKey GameEngineInput::AllKey[KeyMax]{};

void GameEngineInput::Init()
{
	for (unsigned char i = 0; i < KeyMax; ++i)
	{
		AllKey[i].Key = i;
	}
}

void GameEngineInput::Reset()
{
	for (unsigned char i = 0; i < KeyMax; ++i)
	{
		if (AllKey[i].State & 4)//Press
		{
			AllKey[i].State = 3;//Up Free
		}
		else if (AllKey[i].State & 2)//Up
		{
			AllKey[i].State = 1;//Free
		}
	}
}

void GameEngineInput::Update()
{
	//8.Down  4.Press  2.Up  1.Free
	for (unsigned char i = 0; i < KeyMax; ++i)
	{
		if (GetAsyncKeyState(static_cast<int>(AllKey[i].Key)))
		{
			if (AllKey[i].State & 1)//Free
			{
				AllKey[i].State = 12;//Down Press
			}
			else if (AllKey[i].State & 8)//Down
			{
				AllKey[i].State = 4;//Press
			}
		}
		else
		{
			if (AllKey[i].State & 4)//Press
			{
				AllKey[i].State = 3;//Up Free
			}
			else if (AllKey[i].State & 2)//Up
			{
				AllKey[i].State = 1;//Free
			}
		}
	}
}
