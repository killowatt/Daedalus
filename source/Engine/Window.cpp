#include "Window.h"

#ifdef PLATFORM_WINDOWS
#include "Platform/Windows/WindowWin32.h"
typedef WindowWin32 PlatformWindow;
#elif PLATFORM_MACOS
#include "Platform/MacOS/WindowMacOS.h"
typedef WindowMacOS PlatformWindow; // TODO: this is just an example
#endif

// Window
void Window::Update()
{
	if (platformWindow)
		platformWindow->Update();
}

Window::Window() : Window("Daedalus", 1280, 720) {}
Window::Window(const char* title, int32 width, int32 height)
{
	platformWindow = new PlatformWindow(title, width, height);
}
Window::~Window()
{
	delete platformWindow;
}