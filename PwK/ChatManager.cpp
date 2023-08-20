#include "ChatManager.hpp"

DWORD jmpBackPrivate, jmpBackGeneralChat;
wchar_t* privateMsgBuff;
uintptr_t* AUIEditBox;

ChatManager::ChatManager()
{
	ReceivePrivateMessageLoc = (uintptr_t*)(global_offsets::ElementBaseAddress + 0x326E15);
	GeneralChatMsgSendLoc = (uintptr_t*)(global_offsets::ElementBaseAddress + 0x510170);

	jmpBackPrivate = (DWORD)ReceivePrivateMessageLoc + 6;
	jmpBackGeneralChat = (DWORD)GeneralChatMsgSendLoc + 6;
}

void ChatManager::SendPublicChat(wchar_t* msg)
{
	void(__thiscall * pMsg)(uintptr_t*, const char*) = (void(__thiscall*)(uintptr_t*, const char*))(global_offsets::ElementBaseAddress + 0x12B4E0);
	uintptr_t* dlgBase = (uintptr_t*)(*((uintptr_t*)(global_offsets::GameUIMan + 0x330)));
	uintptr_t* spk = (uintptr_t*)(((uintptr_t)AUIEditBox) + 0x13FC);
	*spk = (uintptr_t)msg;
	pMsg(dlgBase, "speak");
}

void __stdcall ProcessTrivia()
{
	Beep(432, 300);
	LogCyan(privateMsgBuff);
	if(wcsstr(privateMsgBuff, L"uanto é") && wcsstr(privateMsgBuff, L"?"))
	{
		std::wstring ws_msg = std::wstring(privateMsgBuff);
		ws_msg = ws_msg.substr(ws_msg.find_first_of(L"0123456789"));
		ws_msg.erase(std::remove_if(ws_msg.begin(), ws_msg.end(), ::isspace), ws_msg.end());
		ws_msg.pop_back();
		char wtoa[16]; wcstombs_s(NULL, wtoa, ws_msg.c_str(), 10);
		double num = te_interp(wtoa, 0);
		char a_answer[8]; dtoa(a_answer, num);
		wchar_t* wc_msg = ctowc(a_answer);
		ChatManager::SendPublicChat(wc_msg);
	}
}