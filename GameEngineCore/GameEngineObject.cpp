#include "PreCompile.h"
#include "GameEngineObject.h"

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
