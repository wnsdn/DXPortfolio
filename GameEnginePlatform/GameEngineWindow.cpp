#include "PreCompile.h"
#include "GameEngineWindow.h"
#include "GameEngineDC.h"

bool GameEngineWindow::IsUpdate = true;

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

void GameEngineWindow::Init(HINSTANCE _Hinst, std::string_view _Name, const POINT& _Pos, const POINT& _Scale)
{
	Hinst = _Hinst;
	Scale = _Scale;

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

	RECT Rect{ 0, 0, Scale.x, Scale.y };
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(Hwnd, nullptr, _Pos.x, _Pos.y,
		Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOZORDER);

	Hdc = GetDC(Hwnd);
	MemDc = new GameEngineDC(Scale.x, Scale.y);

	ShowWindow(Hwnd, SW_SHOW);
}

void GameEngineWindow::MessageLoop(std::function<void()> _Start,
	std::function<void()> _Update,
	std::function<void()> _Release)
{
	if (_Start)
	{
		_Start();
	}

	MSG Msg = {};
	while (IsUpdate)
	{
		if (PeekMessageA(&Msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
			continue;
		}

		if (_Update)
		{
			_Update();
		}
	}

	if (_Release)
	{
		_Release();
	}
}

void GameEngineWindow::ClearBackBuffer()
{
	Rectangle(MemDc->GetHdc(), -1, -1, Scale.x + 1, Scale.y + 1);
}

void GameEngineWindow::DoubleBuffering()
{
	BitBlt(Hdc, 0, 0, Scale.x, Scale.y,
		MemDc->GetHdc(), 0, 0, SRCCOPY);
}

LRESULT GameEngineWindow::WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp)
{
	switch (_Msg)
	{
	case WM_DESTROY:
		IsUpdate = false;
		return 0;
	}

	return DefWindowProcA(_Hwnd, _Msg, _Wp, _Lp);
}

HDC GameEngineWindow::GetMemDc() const
{
	return MemDc->GetHdc();
}
