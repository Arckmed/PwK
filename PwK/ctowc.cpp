#include <iostream>
#include "ctowc.h"

wchar_t* ctowc(const char* text)
{
	const size_t size = (strlen(text) + 1);
	size_t pReturnValue;
	int size_ = 0;
	wchar_t* wText = new wchar_t[size];
	mbstowcs_s(&pReturnValue, wText, size, text, size - 1);
	return wText;
}