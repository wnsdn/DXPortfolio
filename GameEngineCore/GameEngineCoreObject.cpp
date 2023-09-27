#include "PreCompile.h"
#include "GameEngineCoreObject.h"

#include "GameEngineLevel.h"
#include "GameEngineActor.h"

GameEngineLevel* GameEngineCoreObject::GetLevel()
{
	GameEngineObject* ParentType = GetParentObject();

	while (ParentType)
	{
		GameEngineLevel* Level = dynamic_cast<GameEngineLevel*>(ParentType);
		if (Level)
		{
			return Level;
		}

		ParentType = ParentType->GetParentObject();
	}

	assert(false);
	return nullptr;
}

GameEngineActor* GameEngineCoreObject::GetActor()
{
	GameEngineObject* ParentType = GetParentObject();

	while (ParentType)
	{
		GameEngineActor* Actor = dynamic_cast<GameEngineActor*>(ParentType);
		if (Actor)
		{
			return Actor;
		}

		ParentType = ParentType->GetParentObject();
	}

	assert(false);
	return nullptr;
}
