#include "patch.h"
#include <iostream>
void Patch(BYTE* destination, BYTE* source, BYTE*& buffer, unsigned int size)
{
	if(source)
	{
		buffer = new BYTE[size];
		DWORD oldProtect;
		VirtualProtect(destination, size, PAGE_EXECUTE_READWRITE, &oldProtect);
		memcpy(buffer, destination, size);
		memcpy(destination, source, size);
		VirtualProtect(destination, size, oldProtect, &oldProtect);
	}
}

void Patch(BYTE* destination, BYTE*& source, unsigned int size)
{
	DWORD oldProtect;
	VirtualProtect(destination, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(destination, source, size);
	VirtualProtect(destination, size, oldProtect, &oldProtect);
	delete source;
	source = nullptr;
}

void Patch(unsigned int size, BYTE* destination, BYTE* source)
{
	DWORD oldProtect;
	VirtualProtect(destination, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memcpy(destination, source, size);
	VirtualProtect(destination, size, oldProtect, &oldProtect);
}

void Nop(BYTE* destination, unsigned int size)
{
	DWORD oldProtect;
	VirtualProtect(destination, size, PAGE_EXECUTE_READWRITE, &oldProtect);
	memset(destination, 0x90, size);
	VirtualProtect(destination, size, oldProtect, &oldProtect);
}
