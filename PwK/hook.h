#pragma once
#include "patch.h"

bool Detour(BYTE* toHook, BYTE* jumpTo, const uintptr_t length, BYTE* restoreBuffer);
bool Detour(BYTE* toHook, BYTE* jumpTo, const uintptr_t length);
BYTE* TrampHook32(BYTE* src, BYTE* dst, const uintptr_t len);
