#pragma once
#include <GameEngineCore/GameEngineObject.h>

class ContentsCore : public GameEngineObject
{
public:
	ContentsCore() {}
	~ContentsCore() override {}
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;

	static std::string_view GetWndName()
	{
		return "A Dance of Fire and Ice";
	}
	static POINT GetWndPos()
	{
		return { 100, 100 };
	}
	static POINT GetWndScale()
	{
		return { 960, 540};
	}
protected:
	void Start() override;
	void Update(float _Delta) override;
};