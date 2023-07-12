#include "PreCompile.h"
#include "GameEngineWindow.h"

//#include <GameEngineBase/GameEngineDebug.h>
//#include <GameEngineBase/GameEngineMath.h>
#include <format>

GameEngineWindow GameEngineWindow::Instance;

void GameEngineWindow::Init(HINSTANCE _Hinst, const std::string& _Name)
{
	GameEngineDebug::LeakCheck();

	Hinst = _Hinst;
	Name = _Name;

	if (!Hinst)
	{
		GameEngineDebug::MsgBoxAssert("GameEngineWindow::Init(1)");
		return;
	}

	WNDCLASSEXA Wc = {};
	Wc.cbSize = sizeof(WNDCLASSEXA);
	Wc.lpfnWndProc = WndProc;
	Wc.lpszClassName = Name.c_str();
	Wc.hInstance = Hinst;
	Wc.style = CS_VREDRAW | CS_HREDRAW;
	Wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	RegisterClassExA(&Wc);

	Hwnd = CreateWindowA(Name.c_str(), Name.c_str(), WS_OVERLAPPEDWINDOW,
		100, 100, 600, 400, nullptr, nullptr, Hinst, nullptr);

	if (!Hwnd)
	{
		GameEngineDebug::MsgBoxAssert("GameEngineWindow::Init(2)");
		return;
	}

	Hdc = GetDC(Hwnd);

	ShowWindow(Hwnd, SW_SHOW);
	UpdateWindow(Hwnd);
}

void GameEngineWindow::MessageLoop()
{
	MSG Msg = {};
	while (IsUpdate)
	{
		if (PeekMessageA(&Msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
		}

		std::string Buffer{};
		short KeyState = GetAsyncKeyState(VK_SPACE);

		Buffer.clear();
		std::format_to(std::back_inserter(Buffer), "{}", KeyState);
		TextOut(Hdc, 10, 30, Buffer.c_str(), static_cast<int>(Buffer.size()));
	}
}

LRESULT GameEngineWindow::WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp)
{
	switch (_Msg)
	{
	case WM_DESTROY:
		Instance.IsUpdate = false;
		return 0;
	}

	return DefWindowProcA(_Hwnd, _Msg, _Wp, _Lp);
}
