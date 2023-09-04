#include "PreCompile.h"
#include "GameEngineObject.h"

void GameEngineObject::AllLevelStart(GameEngineLevel* _PrevLevel)
{
	LevelStart(_PrevLevel);

	for (auto& Pair : Childs)
	{
		for (auto& Child : Pair.second)
		{
			if (!Child->bUpdate)
			{
				continue;
			}

			Child->LevelStart(_PrevLevel);
		}
	}
}

void GameEngineObject::AllLevelEnd(GameEngineLevel* _NextLevel)
{
	LevelEnd(_NextLevel);

	for (auto& Pair : Childs)
	{
		for (auto& Child : Pair.second)
		{
			if (!Child->bUpdate)
			{
				continue;
			}

			Child->LevelEnd(_NextLevel);
		}
	}
}

void GameEngineObject::AllReleaseCheck()
{
	if (IsDeath())
	{
		Release();
	}

	for (auto& Pair : Childs)
	{
		auto Beg = Pair.second.begin();
		auto End = Pair.second.end();

		for (; Beg != End;)
		{
			if (!(*Beg)->IsDeath())
			{
				(*Beg)->AllReleaseCheck();
				++Beg;
				continue;
			}

			Beg = Pair.second.erase(Beg);
		}
	}
}

void GameEngineObject::AllUpdate(float _Delta)
{
	Update(_Delta);

	for (auto& Pair : Childs)
	{
		for (auto& Child : Pair.second)
		{
			if (!Child->bUpdate)
			{
				continue;
			}

			Child->AddLiveTime(_Delta);
			Child->Update(_Delta);
		}
	}
}
