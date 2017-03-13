#include <iostream>

#include "Platform/Windows/WindowWin32.h"

int main()
{
	std::cout << "Hello!";

	//WindowWin32 window(u8"Hello你好مرحباこんにちは");
	Window window(u8"Hello你好مرحباこんにちは");

	while (true)
	{
		window.Update();
	}

	std::getchar();
}