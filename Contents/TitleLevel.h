#pragma once
#include <GameEngineCore/GameEngineLevel.h>

class TitleLevel : public GameEngineLevel
{
private:

protected:
	void Start() override;
	void Update(float _Delta) override;

	void LevelStart(GameEngineLevel* _PrevLevel) override;
	void LevelEnd(GameEngineLevel* _NextLevel) override;
public:
	TitleLevel();
	~TitleLevel();
	TitleLevel(const TitleLevel&) = delete;
	TitleLevel(TitleLevel&&) noexcept = delete;
	void operator=(const TitleLevel&) = delete;
	void operator=(TitleLevel&&) noexcept = delete;
};
