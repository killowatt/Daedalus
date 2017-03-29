#pragma once
#include "Core.h"

//struct WindowInfo // This is reserved just in case we want control over bit depth later or somethin
//{
//	const char* Title;
//	int32 Width;
//	int32 Height;
//
//	WindowInfo(const char* title = "Daedalus", int32 width = 960, int32 height = 540)
//	{
//		Title = title;
//		Width = width;
//		Height = height;
//	}
//};

class SystemWindow
{
public:
	virtual void Update() = 0;

private:

};

class Window
{
	SystemWindow* platformWindow;

public:
	void Update();

	Window();
	Window(const char* title, int32 width, int32 height);
	~Window();
};