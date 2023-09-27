#pragma once
#include <GameEngineCore/GameEngineActor.h>

class MainUIActor : public GameEngineActor
{
public:
	MainUIActor() {}
	~MainUIActor() {}
	MainUIActor(const MainUIActor&) = delete;
	MainUIActor(MainUIActor&&) noexcept = delete;
	void operator=(const MainUIActor&) = delete;
	void operator=(MainUIActor&&) noexcept = delete;
protected:
	void Start() override;
private:
	std::shared_ptr<class GameEngineUIRenderer> HpBar;
};
