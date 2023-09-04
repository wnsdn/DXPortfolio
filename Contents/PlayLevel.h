#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class PlayLevel : public GameEngineLevel
{
private:
	std::shared_ptr<class PlayMap> Map;
protected:
	void Start() override;
	void Update(float _Delta) override;
	
	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
public:
	PlayLevel() {}
	~PlayLevel() {}
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;
};