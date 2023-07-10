#include "GameEngineWindow.h"
#include <GameEngineBase/GameEngineDebug.h>
#include <GameEngineBase/GameEnginePath.h>

bool GameEngineWindow::IsWindowUpdate = true;
bool GameEngineWindow::IsFocusValue = true;

GameEngineWindow::GameEngineWindow()
{
}

GameEngineWindow::~GameEngineWindow()
{
	if (BackBuffer)
	{
		delete BackBuffer;
		BackBuffer = nullptr;
	}
}

void GameEngineWindow::Open(HINSTANCE _Hinst, const std::string& _Title)
{
	Hinst = _Hinst;
	Title = _Title;

	if (!Hinst)
	{
		MsgBoxAssert("HINSTANCE == nullptr");
		return;
	}

	WNDCLASSEXA Wc = {};
	Wc.cbSize = sizeof(WNDCLASSEXA);
	Wc.lpfnWndProc = WndProc;
	Wc.lpszClassName = Title.c_str();
	Wc.hInstance = Hinst;
	Wc.style = CS_VREDRAW | CS_HREDRAW;
	Wc.hCursor = LoadCursorA(nullptr, IDC_ARROW);
	RegisterClassExA(&Wc);

	Hwnd = CreateWindowA(Title.c_str(), Title.c_str(), WS_OVERLAPPEDWINDOW,
		0, 0, 0, 0, nullptr, nullptr, Hinst, nullptr);

	if (!Hwnd)
	{
		MsgBoxAssert("HWND == nullptr");
		return;
	}

	Hdc = GetDC(Hwnd);

	ShowWindow(Hwnd, SW_SHOW);
	UpdateWindow(Hwnd);
}

void GameEngineWindow::MessageLoop(void(*_Start)(), void(*_Update)(), void(*_End)())
{
	if (_Start)
	{
		_Start();
	}

	MSG Msg = {};
	while (IsWindowUpdate)
	{
		if (PeekMessageA(&Msg, nullptr, 0, 0, PM_REMOVE))
		{
			if (_Update)
			{
				_Update();
			}

			TranslateMessage(&Msg);
			DispatchMessageA(&Msg);
			continue;
		}

		if (_Update)
		{
			_Update();
		}
	}

	if (_End)
	{
		_End();
	}
}

LRESULT GameEngineWindow::WndProc(HWND _Hwnd, UINT _Msg, WPARAM _Wp, LPARAM _Lp)
{
	switch (_Msg)
	{
	case WM_SETFOCUS:
	{
		IsFocusValue = true;
		break;
	}
	case WM_KILLFOCUS:
	{
		IsFocusValue = false;
		break;
	}
	case WM_DESTROY:
		IsWindowUpdate = false;
		return 0;
	}

	return DefWindowProcA(_Hwnd, _Msg, _Wp, _Lp);
}

void GameEngineWindow::SetPosAndScale(const float4& _Pos, const float4& _Scale)
{
	Scale = _Scale;

	BackBuffer = new GameEngineTexture();
	BackBuffer->ResCreate(Scale);

	RECT Rc = { 0, 0, Scale.iX(), Scale.iY() };
	AdjustWindowRect(&Rc, WS_OVERLAPPEDWINDOW, false);
	SetWindowPos(Hwnd, nullptr, _Pos.iX(), _Pos.iY(),
		Rc.right - Rc.left, Rc.bottom - Rc.top, SWP_NOZORDER);
}

void GameEngineWindow::ClearBackBuffer()
{
	Rectangle(BackBuffer->GetImageDC(), -1, -1,
		BackBuffer->GetScale().iX() + 1,
		BackBuffer->GetScale().iY() + 1);
}

void GameEngineWindow::DoubleBuffering()
{
	BitBlt(Hdc,
		Scale.Half().iX() - BackBuffer->GetScale().ihX(),
		Scale.Half().iY() - BackBuffer->GetScale().ihY(),
		BackBuffer->GetScale().iX(),
		BackBuffer->GetScale().iY(),
		BackBuffer->GetImageDC(),
		0, 0, SRCCOPY);
}

float4 GameEngineWindow::GetMousePos()
{
	POINT Point = {};
	GetCursorPos(&Point);
	ScreenToClient(Hwnd, &Point);

	return { static_cast<float>(Point.x), static_cast<float>(Point.y) };
}
