#pragma once
#include <GameEngineCore/GameEngineActor.h>

class Background : public GameEngineActor
{
public:
	Background();
	~Background();
	Background(const Background&) = delete;
	Background(Background&&) noexcept = delete;
	void operator=(const Background&) = delete;
	void operator=(Background&&) noexcept = delete;
protected:
	void Start() override;
	void Update(float _Delta) override;
private:
};
