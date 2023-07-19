#pragma once
#include <string_view>
#include <GameEngineBase/GameEngineMath.h>
#include <GameEngineCore/GameEngineObject.h>

class ContentsCore : public GameEngineObject
{
protected:
	void Start() override;
	void Update(const float _Delta) override;
	void Release() override;
public:
	static std::string_view GetWndName()
	{
		return "MyGame";
	}
	static POINT GetWndPos()
	{
		return { 100, 100 };
	}
	static POINT GetWndScale()
	{
		return { 1080, 720 };
	}

	ContentsCore() {}
	~ContentsCore() {}
	ContentsCore(const ContentsCore& _Other) = delete;
	ContentsCore(ContentsCore&& _Other) noexcept = delete;
	ContentsCore& operator=(const ContentsCore& _Other) = delete;
	ContentsCore& operator=(ContentsCore&& _Other) noexcept = delete;
};