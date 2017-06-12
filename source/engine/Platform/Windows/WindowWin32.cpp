#include "WindowWin32.h"

void WindowWin32::Update()
{
	MSG msg;
	GetMessage(&msg, NULL, 0, 0);
	TranslateMessage(&msg);
	DispatchMessage(&msg);
}

WindowWin32::WindowWin32()
{
}