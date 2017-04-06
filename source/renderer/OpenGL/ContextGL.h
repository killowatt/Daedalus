#pragma once

#include <Windows.h>

struct ContextGL
{
#ifdef PLATFORM_WINDOWS
	HWND WindowHandle;
	HDC WindowDevice;
	HGLRC Context;
#elif PLATFORM_MACOS
	// TODO: mac context
#endif

	ContextGL(void* windowHandle);
	ContextGL() = delete;
	~ContextGL();
};
