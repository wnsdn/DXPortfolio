#include "PreCompile.h"
#include "GameEngineWindow.h"

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
		0, 0, 0, 0, nullptr, nullptr, Hinst, nullptr);

	if (!Hwnd)
	{
		GameEngineDebug::MsgBoxAssert("GameEngineWindow::Init(2)");
		return;
	}

	ShowWindow(Hwnd, SW_SHOW);
	UpdateWindow(Hwnd);
}

void GameEngineWindow::MessageLoop()
{
	RECT Rect{ 0, 0, 600, 400 };
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(Hwnd, nullptr, 100, 100,
		Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOZORDER);

	Hdc = GetDC(Hwnd);
	MemDc = CreateCompatibleDC(Hdc);
	HBITMAP Hbmp = CreateCompatibleBitmap(Hdc, 600, 400);
	SelectObject(MemDc, Hbmp);

	MSG Msg = {};
	while (IsUpdate)
	{
		if (PeekMessageA(&Msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
		}

		Rectangle(MemDc, -1, -1, 601, 401);



		BitBlt(Hdc, 0, 0, 600, 400,
			MemDc, 0, 0, SRCCOPY);
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
