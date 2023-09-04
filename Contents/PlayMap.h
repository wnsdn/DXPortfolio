#pragma once
#include <GameEngineCore/GameEngineActor.h>

class PlayMap : public GameEngineActor
{
private:
	std::shared_ptr<class GameEngineSpriteRenderer> Renderer;
protected:
	void Start() override;
	void Update(float _Delta) override;
public:
	PlayMap();
	~PlayMap();
	PlayMap(const PlayMap&) = delete;
	PlayMap(PlayMap&&) noexcept = delete;
	void operator=(const PlayMap&) = delete;
	void operator=(PlayMap&&) noexcept = delete;

	static PlayMap* MainMap;

	GameEngineColor GetColor(float4 _Pos, GameEngineColor _DefaultColor = { 255, 255, 255, 255 });
};
