#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>

#pragma comment(lib, "GameEngineBase.lib")

GameEngineWindow GameEngineWindow::Instance;

void GameEngineWindow::Init(HINSTANCE _Hinst, const std::string& _Name)
{
	Hinst = _Hinst;
	Name = _Name;

	if (!Hinst)
	{
		MsgBoxAssert("GameEngineWindow::Init(1)");
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
		MsgBoxAssert("GameEngineWindow::Init(2)");
		return;
	}

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
		else
		{

		}
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
