#include "Window.h"

#include <iostream>

#include <gl/GL.h>
#include "../../tempGLext.h"

Window::Window()
{
	Instance = GetModuleHandle(0);
}

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

void *GetAnyGLFuncAddress(const char *name)
{
	void *p = (void *)wglGetProcAddress(name);
	if (p == 0 ||
		(p == (void*)0x1) || (p == (void*)0x2) || (p == (void*)0x3) ||
		(p == (void*)-1))
	{
		HMODULE module = LoadLibraryA("opengl32.dll");
		p = (void *)GetProcAddress(module, name);
	}

	return p;
}


void Window::DoStuff()
{




	// WIN

	WNDCLASSEX wc;
		

	HINSTANCE hInstance = GetModuleHandle(0);

	ZeroMemory(&wc, sizeof(WNDCLASSEX));

	wc.cbSize = sizeof(WNDCLASSEX);
	wc.style = CS_OWNDC;
	wc.lpfnWndProc = WndProc;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
	wc.lpszClassName = L"Daedalus";

	if (!RegisterClassEx(&wc))
	{
		MessageBox(NULL, L"RegisterClassEx failed.", L"Failure",
			NULL);

		return;
	}

	const char xyz[] = u8"Daedalus 你好";
	std::cout << xyz;
	std::cout << strlen("Daedalus 你好");

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

	int vv = MultiByteToWideChar(CP_UTF8, 0, xyz, -1, nullptr, 0);
	wchar_t* namez = new wchar_t[vv];
	MultiByteToWideChar(CP_UTF8, 0, xyz, -1, namez, vv);

	HWND hWnd = CreateWindow(
		L"Daedalus",
		namez,
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
		MessageBox(NULL, L"Creatwindow failed", L"Wow",
			NULL);

		return;
	}

	// The parameters to ShowWindow explained:  
	// hWnd: the value returned from CreateWindow  
	// nCmdShow: the fourth parameter from WinMain  
	ShowWindow(hWnd,
		5);
	UpdateWindow(hWnd);


	// GL

	PIXELFORMATDESCRIPTOR pfd =
	{
		sizeof(PIXELFORMATDESCRIPTOR),
		1,
		PFD_DRAW_TO_WINDOW | PFD_SUPPORT_OPENGL | PFD_DOUBLEBUFFER,    //Flags
		PFD_TYPE_RGBA,            //The kind of framebuffer. RGBA or palette.
		32,                        //Colordepth of the framebuffer.
		0, 0, 0, 0, 0, 0,
		0,
		0,
		0,
		0, 0, 0, 0,
		24,                        //Number of bits for the depthbuffer
		8,                        //Number of bits for the stencilbuffer
		0,                        //Number of Aux buffers in the framebuffer.
		PFD_MAIN_PLANE,
		0,
		0, 0, 0
	};


	HDC device = GetDC(hWnd); // NULL for the entire scren??!!

	int pixelFormatNum = ChoosePixelFormat(device, &pfd);
	if (pixelFormatNum == 0)
		MessageBox(nullptr, L"Couldnt get pixel format", L"Pixel Format", 0);

	SetPixelFormat(device, pixelFormatNum, &pfd);


	HGLRC Context = wglCreateContext(device);
	wglMakeCurrent(device, Context);

	//MessageBoxA(0, (char*)glGetString(GL_VERSION), "OPENGL VERSION", 0);

	PFNGLGETSTRINGIPROC glGetStringi = (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi");





	int num;
	glGetIntegerv(GL_NUM_EXTENSIONS, &num);

	for (int i = 0; i < num - 1; i++)
	{
		const GLubyte* xy = glGetStringi(GL_EXTENSIONS, i);
		std::cout << xy << std::endl;
		
	}

	// WIN


	MSG msg;
	while (GetMessage(&msg, NULL, 0, 0))
	{
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}

	std::cout << (int)msg.wParam;


	// DEL CONTEXT
	wglMakeCurrent(device, nullptr);
	wglDeleteContext(Context);

	return;
}

