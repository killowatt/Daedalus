#pragma once

class PlatformWindow
{
public:
	virtual void Update() = 0;
};

class Window
{
	PlatformWindow* platformWindow;

public:
	void Update();

	Window();
	~Window();
};