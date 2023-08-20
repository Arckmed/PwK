#pragma once
#include <windows.h>
#include <string>
#include <atomic>
#include <iostream>
#include <wchar.h>
#include <thread>
#include "config.h"
#include "tinyexpr.h"
#include "dtoa.h"
#include "ctowc.h"
#include "log.h"

extern DWORD jmpBackPrivate, jmpBackGeneralChat;
extern wchar_t* privateMsgBuff;
extern uintptr_t* AUIEditBox;

class ChatManager
{
public:

	uintptr_t* ReceivePrivateMessageLoc;
	uintptr_t* GeneralChatMsgSendLoc;
	BYTE TriviaHookBuffer[6]{};
	BYTE FetchPlayerChatBuffer[6]{};

	ChatManager();
	static void SendPublicChat(wchar_t* msg);
};

void __stdcall ProcessTrivia();

// chat detours

inline void _declspec(naked) StealEditBox()
{
	_asm
	{
		mov[AUIEditBox], edi
		mov eax, [edi + 0x13FC]
		jmp[jmpBackGeneralChat]
	}
}

inline void _declspec(naked) DetourPrivateMessage()
{
	_asm
	{
		mov[privateMsgBuff], ecx
		pushad
	}

	ProcessTrivia();

	_asm
	{
		popad
		mov[ebp + 0x8], ecx
		lea ecx, [edi + 0x34]
		jmp[jmpBackPrivate]
	}
}



