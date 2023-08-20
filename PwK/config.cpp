#include "config.h"

uintptr_t global_offsets::ElementBaseAddress = (uintptr_t)(GetModuleHandle(L"ELEMENTCLIENT.EXE"));
uintptr_t global_offsets::Game = (uintptr_t)(*((uintptr_t*)(global_offsets::ElementBaseAddress + 0x843540)));
uintptr_t global_offsets::GameRun = (uintptr_t)(*((uintptr_t*)(global_offsets::Game + 0x1C)));
uintptr_t global_offsets::UIManager = (uintptr_t)(*((uintptr_t*)(global_offsets::GameRun + 0x28)));
uintptr_t global_offsets::GameUIMan = (uintptr_t)(*((uintptr_t*)(global_offsets::UIManager + 0xC)));
uintptr_t global_offsets::GameSession = (uintptr_t)(*((uintptr_t*)(global_offsets::Game + 0x94)));
uintptr_t global_offsets::World = (uintptr_t)(*((uintptr_t*)(global_offsets::GameRun + 0x24)));
uintptr_t global_offsets::PlayerMan = (uintptr_t)(*((uintptr_t*)(global_offsets::World + 0x3C)));
uintptr_t global_offsets::NPCManager = (uintptr_t)(*(uintptr_t*)((global_offsets::World + 0x30)));
uintptr_t global_offsets::HostPlayer = (uintptr_t)(*((uintptr_t*)(global_offsets::GameRun + 0x40)));
