#include "Window.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowWin32.h"
typedef WindowWin32 SystemWindow;

#elif PLATFORM_MACOS
#include "Platform/MacOS/WindowMacOS.h"
typedef WindowMacOS SystemWindow; // TODO: this is just an example
#endif

void Window::Update()
{
	if (platformWindow)
		platformWindow->Update();
}

Window::Window()
{
	platformWindow = new SystemWindow();
}