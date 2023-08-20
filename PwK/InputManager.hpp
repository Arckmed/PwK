#pragma once
#include "config.h"
#include <windows.h>

struct InputManager
{
private:
	uintptr_t vKeyArray;

public:
	InputManager();

	__forceinline void SimulateInput(int vKey)
	{
		*(bool*)(vKeyArray + vKey + 0x4C) = true;
	}
};

