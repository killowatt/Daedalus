#pragma once

#include "Platform/Window.h"
#include <Windows.h>

class WindowWin32 : public PlatformWindow
{
	HINSTANCE instance;
	HWND handle;

	void Update();

public:
	WindowWin32();
};