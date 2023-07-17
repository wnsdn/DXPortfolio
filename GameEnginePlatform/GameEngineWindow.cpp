#include "PreCompile.h"
#include "GameEngineWindow.h"

#include "GameEngineText.h"

GameEngineWindow GameEngineWindow::Instance;

void GameEngineWindow::Init(HINSTANCE _Hinst, std::string_view _Name, const GameEngineForm& _Form)
{
	GameEngineDebug::LeakCheck();

	Hinst = _Hinst;
	Form = _Form;

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

	RECT Rect{ Form.Left<int>(), Form.Top<int>(), Form.Right<int>(), Form.Bottom<int>() };
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(Hwnd, nullptr, Form.GetPos<int>().X, Form.GetPos<int>().Y,
		Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOZORDER);

	Hdc = GetDC(Hwnd);
	MemDc = CreateCompatibleDC(Hdc);
	Hbmp = CreateCompatibleBitmap(Hdc, Form.GetSize<int>().X, Form.GetSize<int>().Y);
	SelectObject(MemDc, Hbmp);

	ShowWindow(Hwnd, SW_SHOW);
}

void GameEngineWindow::MessageLoop()
{
	GameEngineText::Init();

	MSG Msg = {};
	while (IsUpdate)
	{
		if (PeekMessageA(&Msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
		}

		Rectangle(MemDc, -1, -1, Form.GetSize<int>().X + 1, Form.GetSize<int>().Y + 1);

		int x = 10;
		int y = 20;
		int z = 30;
		TextOutA(MemDc, 10, 10, GameEngineText::FormatTextOut(x, y).c_str(), ))

		BitBlt(Hdc, 0, 0, Form.GetSize<int>().X, Form.GetSize<int>().Y,
			MemDc, 0, 0, SRCCOPY);
	}

	ReleaseDC(Hwnd, Hdc);
	DeleteDC(MemDc);
	DeleteObject(Hbmp);
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
