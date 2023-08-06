#include "PreCompile.h"
#include "GameEngineCoreObject.h"

#include "GameEngineLevel.h"
#include "GameEngineActor.h"

GameEngineLevel* GameEngineCoreObject::GetLevel()
{
	GameEngineObject* ParentType = GetParent();

	while (ParentType)
	{
		GameEngineLevel* Level = dynamic_cast<GameEngineLevel*>(ParentType);
		if (Level)
		{
			return Level;
		}

		ParentType = ParentType->GetParent();
	}

	GameEngineDebug::MsgBoxAssert(__FUNCTION__);
	return nullptr;
}

GameEngineActor* GameEngineCoreObject::GetActor()
{
	GameEngineObject* ParentType = GetParent();

	while (ParentType)
	{
		GameEngineActor* Actor = dynamic_cast<GameEngineActor*>(ParentType);
		if (Actor)
		{
			return Actor;
		}

		ParentType = ParentType->GetParent();
	}

	GameEngineDebug::MsgBoxAssert(__FUNCTION__);
	return nullptr;
}
