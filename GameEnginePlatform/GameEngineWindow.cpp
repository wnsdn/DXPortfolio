#include "PreCompile.h"
#include "GameEngineWindow.h"

bool GameEngineWindow::bFocus = true;

void GameEngineWindow::Init(HINSTANCE _Hinst, std::string_view _Name, const POINT& _Pos, const POINT& _Scale)
{
	Hinst = _Hinst;
	Scale = _Scale;

	WNDCLASSEXA Wc = {};
	Wc.cbSize = sizeof(WNDCLASSEXA);
	Wc.lpfnWndProc = WndProc;
	Wc.lpszClassName = _Name.data();
	Wc.hInstance = Hinst;
	Wc.style = CS_VREDRAW | CS_HREDRAW;
	Wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	RegisterClassExA(&Wc);

	Hwnd = CreateWindowA(_Name.data(), _Name.data(), WS_OVERLAPPEDWINDOW, 0, 0, 0, 0, nullptr, nullptr, Hinst, nullptr);

	RECT Rect{ 0, 0, _Scale.x, _Scale.y };
	AdjustWindowRect(&Rect, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(Hwnd, nullptr, _Pos.x, _Pos.y, Rect.right - Rect.left, Rect.bottom - Rect.top, SWP_NOZORDER);

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

	MSG Msg{};
	while (Msg.message != WM_QUIT)
	{
		if (PeekMessageA(&Msg, nullptr, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
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

LRESULT GameEngineWindow::WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp)
{
	switch (_Msg)
	{
	case WM_SETFOCUS:
		bFocus = true;
		return 0;
	case WM_KILLFOCUS:
		bFocus = false;
		return 0;
	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	}

	return DefWindowProcA(_Hwnd, _Msg, _Wp, _Lp);
}
