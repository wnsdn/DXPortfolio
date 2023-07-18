#include "PreCompile.h"
#include "GameEngineWindow.h"
#include "GameEngineDC.h"

#include "GameEngineText.h"

GameEngineWindow GameEngineWindow::Instance;

GameEngineWindow::~GameEngineWindow()
{
	if (Hdc)
	{
		ReleaseDC(Hwnd, Hdc);
		Hdc = nullptr;
	}
	if (MemDc)
	{
		delete MemDc;
		MemDc = nullptr;
	}
}

void GameEngineWindow::Init(HINSTANCE _Hinst, std::string_view _Name, int _Left, int _Top, int _Width, int _Height)
{
	GameEngineDebug::LeakCheck();

	Hinst = _Hinst;
	Width = _Width;
	Height = _Height;

	if (!Hinst)
	{
		GameEngineDebug::MsgBoxAssert("GameEngineWindow::Init(1)");
		return;
	}

	WNDCLASSEXA Wc = {};
	Wc.cbSize = sizeof(WNDCLASSEXA);
	Wc.lpfnWndProc = WndProc;
	Wc.lpszClassName = _Name.data();
	Wc.hInstance = Hinst;
	Wc.style = CS_VREDRAW | CS_HREDRAW;
	Wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	RegisterClassExA(&Wc);

	Hwnd = CreateWindowA(_Name.data(), _Name.data(), WS_OVERLAPPEDWINDOW,
		0, 0, 0, 0, nullptr, nullptr, Hinst, nullptr);

	if (!Hwnd)
	{
		GameEngineDebug::MsgBoxAssert("GameEngineWindow::Init(2)");
		return;
	}

	RECT Rect{ 0, 0, Width, Height };
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(Hwnd, nullptr, _Left, _Top,
		Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOZORDER);

	Hdc = GetDC(Hwnd);
	MemDc = new GameEngineDC(Width, Height);

	ShowWindow(Hwnd, SW_SHOW);
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

		Rectangle(MemDc->GetHdc(), -1, -1, Width + 1, Height + 1);

		GameEngineText::FormatTextOut("String", 10, 10, "Hello");

		BitBlt(Hdc, 0, 0, Width, Height,
			MemDc->GetHdc(), 0, 0, SRCCOPY);
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

HDC GameEngineWindow::GetMemDc() const
{
	return MemDc->GetHdc();
}
