#include "Window.h"

#ifdef DAEDALUS_PLATFORM_WINDOWS
#include "Platform/Windows/WindowWin32.h"
typedef WindowWin32 PlatformWindow;
#endif

SystemWindow::SystemWindow()
{
}

// Window
void Window::Update()
{
	if (platformWindow)
		platformWindow->Update();
}

Window::Window() : Window("Daedalus") {}
Window::Window(const char* title)
{
	platformWindow = new PlatformWindow(title);
}
Window::~Window()
{
	delete platformWindow;
}