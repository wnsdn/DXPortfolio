#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class PlayLevel : public GameEngineLevel
{
private:
protected:
	void Start() override;
	void Update(float _Delta) override;
public:
	PlayLevel() {}
	~PlayLevel() {}
	PlayLevel(const PlayLevel& _Other) = delete;
	PlayLevel(PlayLevel&& _Other) noexcept = delete;
	PlayLevel& operator=(const PlayLevel& _Other) = delete;
	PlayLevel& operator=(PlayLevel&& _Other) noexcept = delete;
};