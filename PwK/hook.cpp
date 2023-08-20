#include "hook.h"
#include "patch.h"

bool Detour(BYTE* toHook, BYTE* jumpTo, const uintptr_t length, BYTE* restoreBuffer)
{
	if(length < 5) return false;

	DWORD currentProtection;
	VirtualProtect(toHook, length, PAGE_EXECUTE_READWRITE, &currentProtection);
	memcpy(restoreBuffer, toHook, length);
	memset(toHook, 0x90, length);
	uintptr_t relativeAddress = jumpTo - toHook - 5;
	*toHook = 0xE9;
	*(uintptr_t*)(toHook + 1) = relativeAddress;
	VirtualProtect(toHook, length, currentProtection, &currentProtection);
	return true;
}

bool Detour(BYTE* toHook, BYTE* jumpTo, const uintptr_t length)
{
	if(length < 5) return false;

	DWORD currentProtection;
	VirtualProtect(toHook, length, PAGE_EXECUTE_READWRITE, &currentProtection);
	memset(toHook, 0x90, length);
	uintptr_t relativeAddress = jumpTo - toHook - 5;
	*toHook = 0xE9;
	*(uintptr_t*)(toHook + 1) = relativeAddress;
	VirtualProtect(toHook, length, currentProtection, &currentProtection);
	return true;
}

BYTE* TrampHook32(BYTE* source, BYTE* destination, const uintptr_t len)
{
	if(len < 5) return 0;
	BYTE* gateway = (BYTE*)VirtualAlloc(0, len, MEM_COMMIT | MEM_RESERVE, PAGE_EXECUTE_READWRITE);
	memcpy_s(gateway, len, source, len);
	uintptr_t gatewayRelativeAddress = source - gateway - 5;
	*(gateway + len) = 0xe9;
	*(uintptr_t*)((uintptr_t)gateway + len + 1) = gatewayRelativeAddress;
	Detour(source, destination, len);
	return gateway;
}
