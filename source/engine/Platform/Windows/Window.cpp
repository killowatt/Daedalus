#include "Window.h"

#include <iostream>

LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam)
{
	switch (message)
	{
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	default:
		return DefWindowProc(hWnd, message, wParam, lParam);
		break;
	}

	return 0;
}

void Window::DoStuff()
{
	WNDCLASSEX wc;

	HINSTANCE hInstance = GetModuleHandle(0);

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_APPLICATION));
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_WINDOW - 4);
	wc.lpszMenuName = NULL;
	wc.lpszClassName = "Daedalus";
	wc.hIconSm = LoadIcon(wc.hInstance, MAKEINTRESOURCE(IDI_APPLICATION));

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, "RegisterClassEx failed.", "Failure",
			NULL);

		return;
	}

	// The parameters to CreateWindow explained:  
	// szWindowClass: the name of the application  
	// szTitle: the text that appears in the title bar  
	// WS_OVERLAPPEDWINDOW: the type of window to create  
	// CW_USEDEFAULT, CW_USEDEFAULT: initial position (x, y)  
	// 500, 100: initial size (width, length)  
	// NULL: the parent of this window  
	// NULL: this application does not have a menu bar  
	// hInstance: the first parameter from WinMain  
	// NULL: not used in this application  
	HWND hWnd = CreateWindow(
		"Daedalus",
		"Daedalus Title",
		WS_OVERLAPPEDWINDOW ^ WS_THICKFRAME ^ WS_MAXIMIZEBOX,
		CW_USEDEFAULT, CW_USEDEFAULT,
		1024, 576,
		NULL,
		NULL,
		hInstance,
		NULL
		);

	if (!hWnd)
	{
		MessageBox(NULL, "Creatwindow failed", "Wow",
			NULL);

		return;
	}

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		5);
	UpdateWindow(hWnd);

	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	std::cout << (int)msg.wParam;
	return;
}

