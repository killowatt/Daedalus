#include <iostream>

#include "Platform/Windows/Window.h"

int main()
{
	std::cout << "Hello!";
	Window window;
	window.DoStuff();
	std::getchar();
}