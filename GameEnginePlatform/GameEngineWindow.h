#pragma once
#include <Windows.h>
#include <functional>
#include <string_view>

class GameEngineDC;
class GameEngineWindow
{
private:
	static bool IsUpdate;

	HINSTANCE Hinst = nullptr;
	HWND Hwnd = nullptr;
	HDC Hdc = nullptr;
	GameEngineDC* MemDc = nullptr;
	POINT Scale{};

	static LRESULT CALLBACK WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp);
public:
	void Init(HINSTANCE _Hinst, std::string_view _Name, const POINT& _Pos, const POINT& _Scale);
	void MessageLoop(std::function<void()> _Start,
		std::function<void()> _Update,
		std::function<void()> _Release);
	void ClearBackBuffer();
	void DoubleBuffering();
public:
	HDC GetMemDc() const;
	const POINT& GetScale() const
	{
		return Scale;
	}
public:
	GameEngineWindow() {}
	~GameEngineWindow();
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;
};