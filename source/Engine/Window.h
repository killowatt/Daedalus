#pragma once

class SystemWindow
{
public:

	virtual void Update() = 0;

	SystemWindow();
	SystemWindow(const char* title);
};

class Window
{
	SystemWindow* platformWindow;

public:
	void Update();

	Window();
	Window(const char* title);
	~Window();
};