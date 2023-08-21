#pragma once
#include <Windows.h>
#include <functional>
#include <string_view>
#include <memory>

class GameEngineWindow
{
private:
	static bool bUpdate;
	static bool bFocus;

	HINSTANCE Hinst = nullptr;
	HWND Hwnd = nullptr;
	float4 Scale{};

	static LRESULT CALLBACK WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp);
public:
	void Init(HINSTANCE _Hinst, std::string_view _Name, const POINT& _Pos, const POINT& _Scale);
	void MessageLoop(
		std::function<void()> _Start,
		std::function<void()> _Update,
		std::function<void()> _Release);

#pragma region GetSet
	static GameEngineWindow& GetInst()
	{
		static GameEngineWindow Instance;
		return Instance;
	}
	HWND GetHwnd() const
	{
		return Hwnd;
	}
	bool IsFocus() const
	{
		return bFocus;
	}
	float4 GetScale() const
	{
		return Scale;
	}
#pragma endregion

	GameEngineWindow() {}
	~GameEngineWindow() {}
	GameEngineWindow(const GameEngineWindow&) = delete;
	GameEngineWindow(GameEngineWindow&&) noexcept = delete;
	void operator=(const GameEngineWindow&) = delete;
	void operator=(GameEngineWindow&&) noexcept = delete;
};