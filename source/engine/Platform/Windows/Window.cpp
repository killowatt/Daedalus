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

	//PFNGLGETSTRINGIPROC glGetStringi = (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi");





	PFNGLDRAWRANGEELEMENTSPROC glDrawRangeElements = (PFNGLDRAWRANGEELEMENTSPROC)wglGetProcAddress("glDrawRangeElements");
	PFNGLTEXIMAGE3DPROC glTexImage3D = (PFNGLTEXIMAGE3DPROC)wglGetProcAddress("glTexImage3D");
	PFNGLTEXSUBIMAGE3DPROC glTexSubImage3D = (PFNGLTEXSUBIMAGE3DPROC)wglGetProcAddress("glTexSubImage3D");
	PFNGLCOPYTEXSUBIMAGE3DPROC glCopyTexSubImage3D = (PFNGLCOPYTEXSUBIMAGE3DPROC)wglGetProcAddress("glCopyTexSubImage3D");
	PFNGLACTIVETEXTUREPROC glActiveTexture = (PFNGLACTIVETEXTUREPROC)wglGetProcAddress("glActiveTexture");
	PFNGLSAMPLECOVERAGEPROC glSampleCoverage = (PFNGLSAMPLECOVERAGEPROC)wglGetProcAddress("glSampleCoverage");
	PFNGLCOMPRESSEDTEXIMAGE3DPROC glCompressedTexImage3D = (PFNGLCOMPRESSEDTEXIMAGE3DPROC)wglGetProcAddress("glCompressedTexImage3D");
	PFNGLCOMPRESSEDTEXIMAGE2DPROC glCompressedTexImage2D = (PFNGLCOMPRESSEDTEXIMAGE2DPROC)wglGetProcAddress("glCompressedTexImage2D");
	PFNGLCOMPRESSEDTEXIMAGE1DPROC glCompressedTexImage1D = (PFNGLCOMPRESSEDTEXIMAGE1DPROC)wglGetProcAddress("glCompressedTexImage1D");
	PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC glCompressedTexSubImage3D = (PFNGLCOMPRESSEDTEXSUBIMAGE3DPROC)wglGetProcAddress("glCompressedTexSubImage3D");
	PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC glCompressedTexSubImage2D = (PFNGLCOMPRESSEDTEXSUBIMAGE2DPROC)wglGetProcAddress("glCompressedTexSubImage2D");
	PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC glCompressedTexSubImage1D = (PFNGLCOMPRESSEDTEXSUBIMAGE1DPROC)wglGetProcAddress("glCompressedTexSubImage1D");
	PFNGLGETCOMPRESSEDTEXIMAGEPROC glGetCompressedTexImage = (PFNGLGETCOMPRESSEDTEXIMAGEPROC)wglGetProcAddress("glGetCompressedTexImage");
	PFNGLBLENDFUNCSEPARATEPROC glBlendFuncSeparate = (PFNGLBLENDFUNCSEPARATEPROC)wglGetProcAddress("glBlendFuncSeparate");
	PFNGLMULTIDRAWARRAYSPROC glMultiDrawArrays = (PFNGLMULTIDRAWARRAYSPROC)wglGetProcAddress("glMultiDrawArrays");
	PFNGLMULTIDRAWELEMENTSPROC glMultiDrawElements = (PFNGLMULTIDRAWELEMENTSPROC)wglGetProcAddress("glMultiDrawElements");
	PFNGLPOINTPARAMETERFPROC glPointParameterf = (PFNGLPOINTPARAMETERFPROC)wglGetProcAddress("glPointParameterf");
	PFNGLPOINTPARAMETERFVPROC glPointParameterfv = (PFNGLPOINTPARAMETERFVPROC)wglGetProcAddress("glPointParameterfv");
	PFNGLPOINTPARAMETERIPROC glPointParameteri = (PFNGLPOINTPARAMETERIPROC)wglGetProcAddress("glPointParameteri");
	PFNGLPOINTPARAMETERIVPROC glPointParameteriv = (PFNGLPOINTPARAMETERIVPROC)wglGetProcAddress("glPointParameteriv");
	PFNGLBLENDCOLORPROC glBlendColor = (PFNGLBLENDCOLORPROC)wglGetProcAddress("glBlendColor");
	PFNGLBLENDEQUATIONPROC glBlendEquation = (PFNGLBLENDEQUATIONPROC)wglGetProcAddress("glBlendEquation");
	PFNGLGENQUERIESPROC glGenQueries = (PFNGLGENQUERIESPROC)wglGetProcAddress("glGenQueries");
	PFNGLDELETEQUERIESPROC glDeleteQueries = (PFNGLDELETEQUERIESPROC)wglGetProcAddress("glDeleteQueries");
	PFNGLISQUERYPROC glIsQuery = (PFNGLISQUERYPROC)wglGetProcAddress("glIsQuery");
	PFNGLBEGINQUERYPROC glBeginQuery = (PFNGLBEGINQUERYPROC)wglGetProcAddress("glBeginQuery");
	PFNGLENDQUERYPROC glEndQuery = (PFNGLENDQUERYPROC)wglGetProcAddress("glEndQuery");
	PFNGLGETQUERYIVPROC glGetQueryiv = (PFNGLGETQUERYIVPROC)wglGetProcAddress("glGetQueryiv");
	PFNGLGETQUERYOBJECTIVPROC glGetQueryObjectiv = (PFNGLGETQUERYOBJECTIVPROC)wglGetProcAddress("glGetQueryObjectiv");
	PFNGLGETQUERYOBJECTUIVPROC glGetQueryObjectuiv = (PFNGLGETQUERYOBJECTUIVPROC)wglGetProcAddress("glGetQueryObjectuiv");
	PFNGLBINDBUFFERPROC glBindBuffer = (PFNGLBINDBUFFERPROC)wglGetProcAddress("glBindBuffer");
	PFNGLDELETEBUFFERSPROC glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)wglGetProcAddress("glDeleteBuffers");
	PFNGLGENBUFFERSPROC glGenBuffers = (PFNGLGENBUFFERSPROC)wglGetProcAddress("glGenBuffers");
	PFNGLISBUFFERPROC glIsBuffer = (PFNGLISBUFFERPROC)wglGetProcAddress("glIsBuffer");
	PFNGLBUFFERDATAPROC glBufferData = (PFNGLBUFFERDATAPROC)wglGetProcAddress("glBufferData");
	PFNGLBUFFERSUBDATAPROC glBufferSubData = (PFNGLBUFFERSUBDATAPROC)wglGetProcAddress("glBufferSubData");
	PFNGLGETBUFFERSUBDATAPROC glGetBufferSubData = (PFNGLGETBUFFERSUBDATAPROC)wglGetProcAddress("glGetBufferSubData");
	PFNGLMAPBUFFERPROC glMapBuffer = (PFNGLMAPBUFFERPROC)wglGetProcAddress("glMapBuffer");
	PFNGLUNMAPBUFFERPROC glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)wglGetProcAddress("glUnmapBuffer");
	PFNGLGETBUFFERPARAMETERIVPROC glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetBufferParameteriv");
	PFNGLGETBUFFERPOINTERVPROC glGetBufferPointerv = (PFNGLGETBUFFERPOINTERVPROC)wglGetProcAddress("glGetBufferPointerv");
	PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)wglGetProcAddress("glBlendEquationSeparate");
	PFNGLDRAWBUFFERSPROC glDrawBuffers = (PFNGLDRAWBUFFERSPROC)wglGetProcAddress("glDrawBuffers");
	PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)wglGetProcAddress("glStencilOpSeparate");
	PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)wglGetProcAddress("glStencilFuncSeparate");
	PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)wglGetProcAddress("glStencilMaskSeparate");
	PFNGLATTACHSHADERPROC glAttachShader = (PFNGLATTACHSHADERPROC)wglGetProcAddress("glAttachShader");
	PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)wglGetProcAddress("glBindAttribLocation");
	PFNGLCOMPILESHADERPROC glCompileShader = (PFNGLCOMPILESHADERPROC)wglGetProcAddress("glCompileShader");
	PFNGLCREATEPROGRAMPROC glCreateProgram = (PFNGLCREATEPROGRAMPROC)wglGetProcAddress("glCreateProgram");
	PFNGLCREATESHADERPROC glCreateShader = (PFNGLCREATESHADERPROC)wglGetProcAddress("glCreateShader");
	PFNGLDELETEPROGRAMPROC glDeleteProgram = (PFNGLDELETEPROGRAMPROC)wglGetProcAddress("glDeleteProgram");
	PFNGLDELETESHADERPROC glDeleteShader = (PFNGLDELETESHADERPROC)wglGetProcAddress("glDeleteShader");
	PFNGLDETACHSHADERPROC glDetachShader = (PFNGLDETACHSHADERPROC)wglGetProcAddress("glDetachShader");
	PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glDisableVertexAttribArray");
	PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)wglGetProcAddress("glEnableVertexAttribArray");
	PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)wglGetProcAddress("glGetActiveAttrib");
	PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)wglGetProcAddress("glGetActiveUniform");
	PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)wglGetProcAddress("glGetAttachedShaders");
	PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)wglGetProcAddress("glGetAttribLocation");
	PFNGLGETPROGRAMIVPROC glGetProgramiv = (PFNGLGETPROGRAMIVPROC)wglGetProcAddress("glGetProgramiv");
	PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)wglGetProcAddress("glGetProgramInfoLog");
	PFNGLGETSHADERIVPROC glGetShaderiv = (PFNGLGETSHADERIVPROC)wglGetProcAddress("glGetShaderiv");
	PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)wglGetProcAddress("glGetShaderInfoLog");
	PFNGLGETSHADERSOURCEPROC glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)wglGetProcAddress("glGetShaderSource");
	PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)wglGetProcAddress("glGetUniformLocation");
	PFNGLGETUNIFORMFVPROC glGetUniformfv = (PFNGLGETUNIFORMFVPROC)wglGetProcAddress("glGetUniformfv");
	PFNGLGETUNIFORMIVPROC glGetUniformiv = (PFNGLGETUNIFORMIVPROC)wglGetProcAddress("glGetUniformiv");
	PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)wglGetProcAddress("glGetVertexAttribdv");
	PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)wglGetProcAddress("glGetVertexAttribfv");
	PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)wglGetProcAddress("glGetVertexAttribiv");
	PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)wglGetProcAddress("glGetVertexAttribPointerv");
	PFNGLISPROGRAMPROC glIsProgram = (PFNGLISPROGRAMPROC)wglGetProcAddress("glIsProgram");
	PFNGLISSHADERPROC glIsShader = (PFNGLISSHADERPROC)wglGetProcAddress("glIsShader");
	PFNGLLINKPROGRAMPROC glLinkProgram = (PFNGLLINKPROGRAMPROC)wglGetProcAddress("glLinkProgram");
	PFNGLSHADERSOURCEPROC glShaderSource = (PFNGLSHADERSOURCEPROC)wglGetProcAddress("glShaderSource");
	PFNGLUSEPROGRAMPROC glUseProgram = (PFNGLUSEPROGRAMPROC)wglGetProcAddress("glUseProgram");
	PFNGLUNIFORM1FPROC glUniform1f = (PFNGLUNIFORM1FPROC)wglGetProcAddress("glUniform1f");
	PFNGLUNIFORM2FPROC glUniform2f = (PFNGLUNIFORM2FPROC)wglGetProcAddress("glUniform2f");
	PFNGLUNIFORM3FPROC glUniform3f = (PFNGLUNIFORM3FPROC)wglGetProcAddress("glUniform3f");
	PFNGLUNIFORM4FPROC glUniform4f = (PFNGLUNIFORM4FPROC)wglGetProcAddress("glUniform4f");
	PFNGLUNIFORM1IPROC glUniform1i = (PFNGLUNIFORM1IPROC)wglGetProcAddress("glUniform1i");
	PFNGLUNIFORM2IPROC glUniform2i = (PFNGLUNIFORM2IPROC)wglGetProcAddress("glUniform2i");
	PFNGLUNIFORM3IPROC glUniform3i = (PFNGLUNIFORM3IPROC)wglGetProcAddress("glUniform3i");
	PFNGLUNIFORM4IPROC glUniform4i = (PFNGLUNIFORM4IPROC)wglGetProcAddress("glUniform4i");
	PFNGLUNIFORM1FVPROC glUniform1fv = (PFNGLUNIFORM1FVPROC)wglGetProcAddress("glUniform1fv");
	PFNGLUNIFORM2FVPROC glUniform2fv = (PFNGLUNIFORM2FVPROC)wglGetProcAddress("glUniform2fv");
	PFNGLUNIFORM3FVPROC glUniform3fv = (PFNGLUNIFORM3FVPROC)wglGetProcAddress("glUniform3fv");
	PFNGLUNIFORM4FVPROC glUniform4fv = (PFNGLUNIFORM4FVPROC)wglGetProcAddress("glUniform4fv");
	PFNGLUNIFORM1IVPROC glUniform1iv = (PFNGLUNIFORM1IVPROC)wglGetProcAddress("glUniform1iv");
	PFNGLUNIFORM2IVPROC glUniform2iv = (PFNGLUNIFORM2IVPROC)wglGetProcAddress("glUniform2iv");
	PFNGLUNIFORM3IVPROC glUniform3iv = (PFNGLUNIFORM3IVPROC)wglGetProcAddress("glUniform3iv");
	PFNGLUNIFORM4IVPROC glUniform4iv = (PFNGLUNIFORM4IVPROC)wglGetProcAddress("glUniform4iv");
	PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)wglGetProcAddress("glUniformMatrix2fv");
	PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)wglGetProcAddress("glUniformMatrix3fv");
	PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)wglGetProcAddress("glUniformMatrix4fv");
	PFNGLVALIDATEPROGRAMPROC glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)wglGetProcAddress("glValidateProgram");
	PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)wglGetProcAddress("glVertexAttrib1d");
	PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)wglGetProcAddress("glVertexAttrib1dv");
	PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)wglGetProcAddress("glVertexAttrib1f");
	PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)wglGetProcAddress("glVertexAttrib1fv");
	PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)wglGetProcAddress("glVertexAttrib1s");
	PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)wglGetProcAddress("glVertexAttrib1sv");
	PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)wglGetProcAddress("glVertexAttrib2d");
	PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)wglGetProcAddress("glVertexAttrib2dv");
	PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)wglGetProcAddress("glVertexAttrib2f");
	PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)wglGetProcAddress("glVertexAttrib2fv");
	PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)wglGetProcAddress("glVertexAttrib2s");
	PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)wglGetProcAddress("glVertexAttrib2sv");
	PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)wglGetProcAddress("glVertexAttrib3d");
	PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)wglGetProcAddress("glVertexAttrib3dv");
	PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)wglGetProcAddress("glVertexAttrib3f");
	PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)wglGetProcAddress("glVertexAttrib3fv");
	PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)wglGetProcAddress("glVertexAttrib3s");
	PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)wglGetProcAddress("glVertexAttrib3sv");
	PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)wglGetProcAddress("glVertexAttrib4Nbv");
	PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)wglGetProcAddress("glVertexAttrib4Niv");
	PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)wglGetProcAddress("glVertexAttrib4Nsv");
	PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)wglGetProcAddress("glVertexAttrib4Nub");
	PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)wglGetProcAddress("glVertexAttrib4Nubv");
	PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)wglGetProcAddress("glVertexAttrib4Nuiv");
	PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)wglGetProcAddress("glVertexAttrib4Nusv");
	PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)wglGetProcAddress("glVertexAttrib4bv");
	PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)wglGetProcAddress("glVertexAttrib4d");
	PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)wglGetProcAddress("glVertexAttrib4dv");
	PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)wglGetProcAddress("glVertexAttrib4f");
	PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)wglGetProcAddress("glVertexAttrib4fv");
	PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)wglGetProcAddress("glVertexAttrib4iv");
	PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)wglGetProcAddress("glVertexAttrib4s");
	PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)wglGetProcAddress("glVertexAttrib4sv");
	PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)wglGetProcAddress("glVertexAttrib4ubv");
	PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)wglGetProcAddress("glVertexAttrib4uiv");
	PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)wglGetProcAddress("glVertexAttrib4usv");
	PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)wglGetProcAddress("glVertexAttribPointer");
	PFNGLUNIFORMMATRIX2X3FVPROC glUniformMatrix2x3fv = (PFNGLUNIFORMMATRIX2X3FVPROC)wglGetProcAddress("glUniformMatrix2x3fv");
	PFNGLUNIFORMMATRIX3X2FVPROC glUniformMatrix3x2fv = (PFNGLUNIFORMMATRIX3X2FVPROC)wglGetProcAddress("glUniformMatrix3x2fv");
	PFNGLUNIFORMMATRIX2X4FVPROC glUniformMatrix2x4fv = (PFNGLUNIFORMMATRIX2X4FVPROC)wglGetProcAddress("glUniformMatrix2x4fv");
	PFNGLUNIFORMMATRIX4X2FVPROC glUniformMatrix4x2fv = (PFNGLUNIFORMMATRIX4X2FVPROC)wglGetProcAddress("glUniformMatrix4x2fv");
	PFNGLUNIFORMMATRIX3X4FVPROC glUniformMatrix3x4fv = (PFNGLUNIFORMMATRIX3X4FVPROC)wglGetProcAddress("glUniformMatrix3x4fv");
	PFNGLUNIFORMMATRIX4X3FVPROC glUniformMatrix4x3fv = (PFNGLUNIFORMMATRIX4X3FVPROC)wglGetProcAddress("glUniformMatrix4x3fv");
	PFNGLCOLORMASKIPROC glColorMaski = (PFNGLCOLORMASKIPROC)wglGetProcAddress("glColorMaski");
	PFNGLGETBOOLEANI_VPROC glGetBooleani_v = (PFNGLGETBOOLEANI_VPROC)wglGetProcAddress("glGetBooleani_v");
	PFNGLGETINTEGERI_VPROC glGetIntegeri_v = (PFNGLGETINTEGERI_VPROC)wglGetProcAddress("glGetIntegeri_v");
	PFNGLENABLEIPROC glEnablei = (PFNGLENABLEIPROC)wglGetProcAddress("glEnablei");
	PFNGLDISABLEIPROC glDisablei = (PFNGLDISABLEIPROC)wglGetProcAddress("glDisablei");
	PFNGLISENABLEDIPROC glIsEnabledi = (PFNGLISENABLEDIPROC)wglGetProcAddress("glIsEnabledi");
	PFNGLBEGINTRANSFORMFEEDBACKPROC glBeginTransformFeedback = (PFNGLBEGINTRANSFORMFEEDBACKPROC)wglGetProcAddress("glBeginTransformFeedback");
	PFNGLENDTRANSFORMFEEDBACKPROC glEndTransformFeedback = (PFNGLENDTRANSFORMFEEDBACKPROC)wglGetProcAddress("glEndTransformFeedback");
	PFNGLBINDBUFFERRANGEPROC glBindBufferRange = (PFNGLBINDBUFFERRANGEPROC)wglGetProcAddress("glBindBufferRange");
	PFNGLBINDBUFFERBASEPROC glBindBufferBase = (PFNGLBINDBUFFERBASEPROC)wglGetProcAddress("glBindBufferBase");
	PFNGLTRANSFORMFEEDBACKVARYINGSPROC glTransformFeedbackVaryings = (PFNGLTRANSFORMFEEDBACKVARYINGSPROC)wglGetProcAddress("glTransformFeedbackVaryings");
	PFNGLGETTRANSFORMFEEDBACKVARYINGPROC glGetTransformFeedbackVarying = (PFNGLGETTRANSFORMFEEDBACKVARYINGPROC)wglGetProcAddress("glGetTransformFeedbackVarying");
	PFNGLCLAMPCOLORPROC glClampColor = (PFNGLCLAMPCOLORPROC)wglGetProcAddress("glClampColor");
	PFNGLBEGINCONDITIONALRENDERPROC glBeginConditionalRender = (PFNGLBEGINCONDITIONALRENDERPROC)wglGetProcAddress("glBeginConditionalRender");
	PFNGLENDCONDITIONALRENDERPROC glEndConditionalRender = (PFNGLENDCONDITIONALRENDERPROC)wglGetProcAddress("glEndConditionalRender");
	PFNGLVERTEXATTRIBIPOINTERPROC glVertexAttribIPointer = (PFNGLVERTEXATTRIBIPOINTERPROC)wglGetProcAddress("glVertexAttribIPointer");
	PFNGLGETVERTEXATTRIBIIVPROC glGetVertexAttribIiv = (PFNGLGETVERTEXATTRIBIIVPROC)wglGetProcAddress("glGetVertexAttribIiv");
	PFNGLGETVERTEXATTRIBIUIVPROC glGetVertexAttribIuiv = (PFNGLGETVERTEXATTRIBIUIVPROC)wglGetProcAddress("glGetVertexAttribIuiv");
	PFNGLVERTEXATTRIBI1IPROC glVertexAttribI1i = (PFNGLVERTEXATTRIBI1IPROC)wglGetProcAddress("glVertexAttribI1i");
	PFNGLVERTEXATTRIBI2IPROC glVertexAttribI2i = (PFNGLVERTEXATTRIBI2IPROC)wglGetProcAddress("glVertexAttribI2i");
	PFNGLVERTEXATTRIBI3IPROC glVertexAttribI3i = (PFNGLVERTEXATTRIBI3IPROC)wglGetProcAddress("glVertexAttribI3i");
	PFNGLVERTEXATTRIBI4IPROC glVertexAttribI4i = (PFNGLVERTEXATTRIBI4IPROC)wglGetProcAddress("glVertexAttribI4i");
	PFNGLVERTEXATTRIBI1UIPROC glVertexAttribI1ui = (PFNGLVERTEXATTRIBI1UIPROC)wglGetProcAddress("glVertexAttribI1ui");
	PFNGLVERTEXATTRIBI2UIPROC glVertexAttribI2ui = (PFNGLVERTEXATTRIBI2UIPROC)wglGetProcAddress("glVertexAttribI2ui");
	PFNGLVERTEXATTRIBI3UIPROC glVertexAttribI3ui = (PFNGLVERTEXATTRIBI3UIPROC)wglGetProcAddress("glVertexAttribI3ui");
	PFNGLVERTEXATTRIBI4UIPROC glVertexAttribI4ui = (PFNGLVERTEXATTRIBI4UIPROC)wglGetProcAddress("glVertexAttribI4ui");
	PFNGLVERTEXATTRIBI1IVPROC glVertexAttribI1iv = (PFNGLVERTEXATTRIBI1IVPROC)wglGetProcAddress("glVertexAttribI1iv");
	PFNGLVERTEXATTRIBI2IVPROC glVertexAttribI2iv = (PFNGLVERTEXATTRIBI2IVPROC)wglGetProcAddress("glVertexAttribI2iv");
	PFNGLVERTEXATTRIBI3IVPROC glVertexAttribI3iv = (PFNGLVERTEXATTRIBI3IVPROC)wglGetProcAddress("glVertexAttribI3iv");
	PFNGLVERTEXATTRIBI4IVPROC glVertexAttribI4iv = (PFNGLVERTEXATTRIBI4IVPROC)wglGetProcAddress("glVertexAttribI4iv");
	PFNGLVERTEXATTRIBI1UIVPROC glVertexAttribI1uiv = (PFNGLVERTEXATTRIBI1UIVPROC)wglGetProcAddress("glVertexAttribI1uiv");
	PFNGLVERTEXATTRIBI2UIVPROC glVertexAttribI2uiv = (PFNGLVERTEXATTRIBI2UIVPROC)wglGetProcAddress("glVertexAttribI2uiv");
	PFNGLVERTEXATTRIBI3UIVPROC glVertexAttribI3uiv = (PFNGLVERTEXATTRIBI3UIVPROC)wglGetProcAddress("glVertexAttribI3uiv");
	PFNGLVERTEXATTRIBI4UIVPROC glVertexAttribI4uiv = (PFNGLVERTEXATTRIBI4UIVPROC)wglGetProcAddress("glVertexAttribI4uiv");
	PFNGLVERTEXATTRIBI4BVPROC glVertexAttribI4bv = (PFNGLVERTEXATTRIBI4BVPROC)wglGetProcAddress("glVertexAttribI4bv");
	PFNGLVERTEXATTRIBI4SVPROC glVertexAttribI4sv = (PFNGLVERTEXATTRIBI4SVPROC)wglGetProcAddress("glVertexAttribI4sv");
	PFNGLVERTEXATTRIBI4UBVPROC glVertexAttribI4ubv = (PFNGLVERTEXATTRIBI4UBVPROC)wglGetProcAddress("glVertexAttribI4ubv");
	PFNGLVERTEXATTRIBI4USVPROC glVertexAttribI4usv = (PFNGLVERTEXATTRIBI4USVPROC)wglGetProcAddress("glVertexAttribI4usv");
	PFNGLGETUNIFORMUIVPROC glGetUniformuiv = (PFNGLGETUNIFORMUIVPROC)wglGetProcAddress("glGetUniformuiv");
	PFNGLBINDFRAGDATALOCATIONPROC glBindFragDataLocation = (PFNGLBINDFRAGDATALOCATIONPROC)wglGetProcAddress("glBindFragDataLocation");
	PFNGLGETFRAGDATALOCATIONPROC glGetFragDataLocation = (PFNGLGETFRAGDATALOCATIONPROC)wglGetProcAddress("glGetFragDataLocation");
	PFNGLUNIFORM1UIPROC glUniform1ui = (PFNGLUNIFORM1UIPROC)wglGetProcAddress("glUniform1ui");
	PFNGLUNIFORM2UIPROC glUniform2ui = (PFNGLUNIFORM2UIPROC)wglGetProcAddress("glUniform2ui");
	PFNGLUNIFORM3UIPROC glUniform3ui = (PFNGLUNIFORM3UIPROC)wglGetProcAddress("glUniform3ui");
	PFNGLUNIFORM4UIPROC glUniform4ui = (PFNGLUNIFORM4UIPROC)wglGetProcAddress("glUniform4ui");
	PFNGLUNIFORM1UIVPROC glUniform1uiv = (PFNGLUNIFORM1UIVPROC)wglGetProcAddress("glUniform1uiv");
	PFNGLUNIFORM2UIVPROC glUniform2uiv = (PFNGLUNIFORM2UIVPROC)wglGetProcAddress("glUniform2uiv");
	PFNGLUNIFORM3UIVPROC glUniform3uiv = (PFNGLUNIFORM3UIVPROC)wglGetProcAddress("glUniform3uiv");
	PFNGLUNIFORM4UIVPROC glUniform4uiv = (PFNGLUNIFORM4UIVPROC)wglGetProcAddress("glUniform4uiv");
	PFNGLTEXPARAMETERIIVPROC glTexParameterIiv = (PFNGLTEXPARAMETERIIVPROC)wglGetProcAddress("glTexParameterIiv");
	PFNGLTEXPARAMETERIUIVPROC glTexParameterIuiv = (PFNGLTEXPARAMETERIUIVPROC)wglGetProcAddress("glTexParameterIuiv");
	PFNGLGETTEXPARAMETERIIVPROC glGetTexParameterIiv = (PFNGLGETTEXPARAMETERIIVPROC)wglGetProcAddress("glGetTexParameterIiv");
	PFNGLGETTEXPARAMETERIUIVPROC glGetTexParameterIuiv = (PFNGLGETTEXPARAMETERIUIVPROC)wglGetProcAddress("glGetTexParameterIuiv");
	PFNGLCLEARBUFFERIVPROC glClearBufferiv = (PFNGLCLEARBUFFERIVPROC)wglGetProcAddress("glClearBufferiv");
	PFNGLCLEARBUFFERUIVPROC glClearBufferuiv = (PFNGLCLEARBUFFERUIVPROC)wglGetProcAddress("glClearBufferuiv");
	PFNGLCLEARBUFFERFVPROC glClearBufferfv = (PFNGLCLEARBUFFERFVPROC)wglGetProcAddress("glClearBufferfv");
	PFNGLCLEARBUFFERFIPROC glClearBufferfi = (PFNGLCLEARBUFFERFIPROC)wglGetProcAddress("glClearBufferfi");
	PFNGLGETSTRINGIPROC glGetStringi = (PFNGLGETSTRINGIPROC)wglGetProcAddress("glGetStringi");
	PFNGLISRENDERBUFFERPROC glIsRenderbuffer = (PFNGLISRENDERBUFFERPROC)wglGetProcAddress("glIsRenderbuffer");
	PFNGLBINDRENDERBUFFERPROC glBindRenderbuffer = (PFNGLBINDRENDERBUFFERPROC)wglGetProcAddress("glBindRenderbuffer");
	PFNGLDELETERENDERBUFFERSPROC glDeleteRenderbuffers = (PFNGLDELETERENDERBUFFERSPROC)wglGetProcAddress("glDeleteRenderbuffers");
	PFNGLGENRENDERBUFFERSPROC glGenRenderbuffers = (PFNGLGENRENDERBUFFERSPROC)wglGetProcAddress("glGenRenderbuffers");
	PFNGLRENDERBUFFERSTORAGEPROC glRenderbufferStorage = (PFNGLRENDERBUFFERSTORAGEPROC)wglGetProcAddress("glRenderbufferStorage");
	PFNGLGETRENDERBUFFERPARAMETERIVPROC glGetRenderbufferParameteriv = (PFNGLGETRENDERBUFFERPARAMETERIVPROC)wglGetProcAddress("glGetRenderbufferParameteriv");
	PFNGLISFRAMEBUFFERPROC glIsFramebuffer = (PFNGLISFRAMEBUFFERPROC)wglGetProcAddress("glIsFramebuffer");
	PFNGLBINDFRAMEBUFFERPROC glBindFramebuffer = (PFNGLBINDFRAMEBUFFERPROC)wglGetProcAddress("glBindFramebuffer");
	PFNGLDELETEFRAMEBUFFERSPROC glDeleteFramebuffers = (PFNGLDELETEFRAMEBUFFERSPROC)wglGetProcAddress("glDeleteFramebuffers");
	PFNGLGENFRAMEBUFFERSPROC glGenFramebuffers = (PFNGLGENFRAMEBUFFERSPROC)wglGetProcAddress("glGenFramebuffers");
	PFNGLCHECKFRAMEBUFFERSTATUSPROC glCheckFramebufferStatus = (PFNGLCHECKFRAMEBUFFERSTATUSPROC)wglGetProcAddress("glCheckFramebufferStatus");
	PFNGLFRAMEBUFFERTEXTURE1DPROC glFramebufferTexture1D = (PFNGLFRAMEBUFFERTEXTURE1DPROC)wglGetProcAddress("glFramebufferTexture1D");
	PFNGLFRAMEBUFFERTEXTURE2DPROC glFramebufferTexture2D = (PFNGLFRAMEBUFFERTEXTURE2DPROC)wglGetProcAddress("glFramebufferTexture2D");
	PFNGLFRAMEBUFFERTEXTURE3DPROC glFramebufferTexture3D = (PFNGLFRAMEBUFFERTEXTURE3DPROC)wglGetProcAddress("glFramebufferTexture3D");
	PFNGLFRAMEBUFFERRENDERBUFFERPROC glFramebufferRenderbuffer = (PFNGLFRAMEBUFFERRENDERBUFFERPROC)wglGetProcAddress("glFramebufferRenderbuffer");
	PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC glGetFramebufferAttachmentParameteriv = (PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC)wglGetProcAddress("glGetFramebufferAttachmentParameteriv");
	PFNGLGENERATEMIPMAPPROC glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)wglGetProcAddress("glGenerateMipmap");
	PFNGLBLITFRAMEBUFFERPROC glBlitFramebuffer = (PFNGLBLITFRAMEBUFFERPROC)wglGetProcAddress("glBlitFramebuffer");
	PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC glRenderbufferStorageMultisample = (PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC)wglGetProcAddress("glRenderbufferStorageMultisample");
	PFNGLFRAMEBUFFERTEXTURELAYERPROC glFramebufferTextureLayer = (PFNGLFRAMEBUFFERTEXTURELAYERPROC)wglGetProcAddress("glFramebufferTextureLayer");
	PFNGLMAPBUFFERRANGEPROC glMapBufferRange = (PFNGLMAPBUFFERRANGEPROC)wglGetProcAddress("glMapBufferRange");
	PFNGLFLUSHMAPPEDBUFFERRANGEPROC glFlushMappedBufferRange = (PFNGLFLUSHMAPPEDBUFFERRANGEPROC)wglGetProcAddress("glFlushMappedBufferRange");
	PFNGLBINDVERTEXARRAYPROC glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)wglGetProcAddress("glBindVertexArray");
	PFNGLDELETEVERTEXARRAYSPROC glDeleteVertexArrays = (PFNGLDELETEVERTEXARRAYSPROC)wglGetProcAddress("glDeleteVertexArrays");
	PFNGLGENVERTEXARRAYSPROC glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)wglGetProcAddress("glGenVertexArrays");
	PFNGLISVERTEXARRAYPROC glIsVertexArray = (PFNGLISVERTEXARRAYPROC)wglGetProcAddress("glIsVertexArray");










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

