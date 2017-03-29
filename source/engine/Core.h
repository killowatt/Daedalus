#pragma once

#include <iostream>

typedef signed int int32; // TODO: make our own typedefs for this or cstdint?

enum class LogMessageType
{
	SYSTEM,
	ERROR
};

static void LogPrint(LogMessageType type, const char* message)
{
	// TODO: print this to something more helpful
	switch (type)
	{
	case LogMessageType::SYSTEM:
		std::cout << "[SYSTEM] ";
		break;
	case LogMessageType::ERROR:
		std::cout << "[ERROR] ";
		break;
	}

	std::cout << message << "\n";
}
static void Error(const char* error)
{
	std::cout << "Breakpoint\n"; // hey wow a breakpoint goes here (what a solution)
}