#include "PreCompile.h"
#include "GameEngineObject.h"

void GameEngineObject::AllLevelStart(GameEngineLevel* _PrevLevel)
{
	LevelStart(_PrevLevel);

	for (auto& Pair : Childs)
	{
		for (auto& Child : Pair.second)
		{
			if (!Child->IsUpdate())
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
			if (!Child->IsUpdate())
			{
				continue;
			}

			Child->LevelEnd(_NextLevel);
		}
	}
}

void GameEngineObject::AllRelease()
{
	Release();

	for (auto& Pair : Childs)
	{
		for (auto& Object : Pair.second)
		{
			Object->IsDeathValue = true;
			Object->Parent = nullptr;
			Object->AllRelease();
		}
	}
}

void GameEngineObject::AllReleaseCheck()
{
	if (IsDeath())
	{
		AllRelease();
		return;
	}

	for (auto& Pair : Childs)
	{
		auto Start = Pair.second.begin();
		auto End = Pair.second.end();

		for (; Start != End;)
		{
			if (!(*Start)->IsDeath())
			{
				(*Start)->AllReleaseCheck();
				++Start;
				continue;
			}

			Start = Pair.second.erase(Start);
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
			if (!Child->IsUpdate())
			{
				continue;
			}

			Child->AddLiveTime(_Delta);
			Child->Update(_Delta);
		}
	}
}
