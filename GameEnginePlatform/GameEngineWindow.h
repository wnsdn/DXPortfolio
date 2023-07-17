#pragma once
#include <Windows.h>
#include <string_view>
#include <GameEngineBase/GameEngineForm.h>

class GameEngineWindow
{
private:
	static GameEngineWindow Instance;

	HINSTANCE Hinst = nullptr;
	HWND Hwnd = nullptr;
	HDC Hdc = nullptr;

	HDC MemDc = nullptr;
	HBITMAP Hbmp = nullptr;

	GameEngineForm Form{};
	bool IsUpdate = true;

	static LRESULT CALLBACK WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp);

	GameEngineWindow() {}
	~GameEngineWindow() {}
	GameEngineWindow(const GameEngineWindow& _Other) = delete;
	GameEngineWindow(GameEngineWindow&& _Other) noexcept = delete;
	GameEngineWindow& operator=(const GameEngineWindow& _Other) = delete;
	GameEngineWindow& operator=(GameEngineWindow&& _Other) noexcept = delete;
public:
	static GameEngineWindow& GetInst()
	{
		return Instance;
	}

	void Init(HINSTANCE _Hinst, std::string_view _Name, const GameEngineForm& _Form);
	void MessageLoop();

	HDC GetMemDc() const
	{
		return MemDc;
	}
};