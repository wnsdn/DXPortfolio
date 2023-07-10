#pragma once
#include <Windows.h>
#include <string>

class GameEngineWindow
{
private:
	static GameEngineWindow Instance;

	HINSTANCE Hinst = nullptr;
	HWND Hwnd = nullptr;
	std::string Name{};
	bool IsUpdate = true;

	static LRESULT CALLBACK WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp);
public:
	static GameEngineWindow& GetInst()
	{
		return Instance;
	}

	void Init(HINSTANCE _Hinst, const std::string& _Name);
	void MessageLoop();
};