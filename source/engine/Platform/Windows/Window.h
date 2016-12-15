#pragma once

#include <Windows.h>

class Window
{
public:
	HINSTANCE Instance;
	HWND Handle;

	void DoStuff();

	Window();
};
