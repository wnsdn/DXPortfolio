#pragma once
#include <Windows.h>
#include <string_view>

class GameEngineDC;
class GameEngineWindow
{
private:
	static GameEngineWindow Instance;

	HINSTANCE Hinst = nullptr;
	HWND Hwnd = nullptr;
	HDC Hdc = nullptr;
	GameEngineDC* MemDc = nullptr;

	int Width = 0;
	int Height = 0;

	bool IsUpdate = true;

	static LRESULT CALLBACK WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp);

	GameEngineWindow() {}
	~GameEngineWindow();
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;
public:
	static GameEngineWindow& GetInst()
	{
		return Instance;
	}

	void Init(HINSTANCE _Hinst, std::string_view _Name, int _Left, int _Top, int _Width, int _Height);
	void MessageLoop();

	HDC GetMemDc() const;
	int GetWidth() const
	{
		return Width;
	}
	int GetHeight() const
	{
		return Height;
	}
};