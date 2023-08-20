#include "InputManager.hpp"

InputManager::InputManager()
{
	vKeyArray = *((uintptr_t*)(global_offsets::GameRun + 0x1C));
}

