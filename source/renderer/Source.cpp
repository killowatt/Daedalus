#include <iostream>
#include "GL/DaedalusGL.h"

int main()
{
	std::cout << "Hello";

	InitializeGL();

	glUseProgram(0);

	std::getchar();
}