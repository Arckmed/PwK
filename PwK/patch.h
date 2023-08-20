#pragma once
#include <Windows.h>
#include <vector>

void Patch(BYTE* destination, BYTE*& source, unsigned int size);
void Patch(unsigned int size, BYTE* destination, BYTE* source);
void Patch(BYTE* destination, BYTE* source, BYTE*& buffer, unsigned int size);
void Nop(BYTE* destination, unsigned int size);


