#include "pch.h"
#include "log.h"

void Log(const wchar_t* msg, int attrib)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), attrib);
	std::wcout << "[" << getCurrentDateTime() << "]: " << msg << std::endl;
}

void LogPurple(const wchar_t* msg)
{
	Log(msg, 0x5);
}

void LogGreen(const wchar_t* msg)
{
	Log(msg, 0xA);
}

void LogCyan(const wchar_t* msg)
{
	Log(msg, 0xB);
}

void LogRed(const wchar_t* msg)
{
	Log(msg, 0xC);
}



