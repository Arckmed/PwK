#include "pch.h"
#include "PW.h"
#include <mutex>

PW::PW() { }

void PW::StartAutoFarming()
{
	std::thread farm(&PW::AutoFarm, this);
	farm.detach();
}

void PW::StopAutoFarming()
{
	toggleFarming.store(false);
}

void PW::StartAutoTrivia()
{
	Detour((BYTE*)chat.ReceivePrivateMessageLoc, (BYTE*)DetourPrivateMessage, 6, chat.TriviaHookBuffer);
	Detour((BYTE*)chat.GeneralChatMsgSendLoc, (BYTE*)StealEditBox, 6, chat.FetchPlayerChatBuffer);
}

void PW::StopAutoTrivia()
{
	Patch(6, (BYTE*)chat.ReceivePrivateMessageLoc, chat.TriviaHookBuffer);
	Patch(6, (BYTE*)chat.GeneralChatMsgSendLoc, chat.FetchPlayerChatBuffer);
}

void PW::AutoFarm()
{
	int monsterCounter = 0;
	toggleFarming.store(true);

	while(toggleFarming.load())
	{
		uintptr_t* playerList = ((uintptr_t*)(*((uintptr_t*)(global_offsets::PlayerMan + 0x24))));
		int playerCount = (int)*((int*)(global_offsets::PlayerMan + 0x78));

		if(playerCount)
		{
			for(size_t i = 0; i < playerCount; i++)
			{
				uintptr_t* playerTmp = (uintptr_t*)*((uintptr_t*)((uintptr_t)playerList) + i);
				std::once_flag onceFlag;
				bool leaving = false;

				if((uintptr_t)*playerTmp == 0xb33604)
				{

					Vector3* tmpPos = (Vector3*)(((uintptr_t)playerTmp) + 0x38);
					Vector3* hostPos = (Vector3*)(global_offsets::HostPlayer + 0x38);

					auto start = std::chrono::system_clock::now();
					std::chrono::duration<double> end{};
					while(tmpPos->Distance(*hostPos) < 12.5f && toggleFarming.load() == true)
					{
						std::call_once(onceFlag, [playerTmp]
							{
								wchar_t* name = (wchar_t*)(*(((uintptr_t*)(((uintptr_t)playerTmp) + 0x6B4))));
								Log(L"The following player is close by:"); Log(name); Beep(432, 150); Beep(432, 150);
							});

						std::this_thread::sleep_for(std::chrono::milliseconds(1000));

						end = std::chrono::system_clock::now() - start;
						if(end.count() > 60)
						{
							leaving = true;
							Log(L"We're waiting for way too long, ignoring people for now...");
							break;
						}
					}
					if(leaving) break;
				}
			}
		}

		monster.SwitchMonster();
		auto start = std::chrono::system_clock::now();
		std::chrono::duration<double> end{};
		short tries = 0;

		do
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			monster.AttackSelected();
			end = std::chrono::system_clock::now() - start;
		} while(monster.IsCurrentMonsterAlive() && toggleFarming.load() == true && *((uintptr_t*)(global_offsets::HostPlayer + 0x4A4)) >= 1 && end.count() < 60);

		if(end.count() > 60)
		{
			Log(L"Stuck in a monster for more than 60sec, restarting...");
			auto strt = std::chrono::system_clock::now();
			std::chrono::duration<double> nd{};

			do
			{
				input.SimulateInput(0x57);
				nd = std::chrono::system_clock::now() - strt;
			} while(nd.count() <= 2);

			do
			{
				input.SimulateInput(0x44);
				nd = std::chrono::system_clock::now() - strt;
			} while(nd.count() <= 4);

			do
			{
				input.SimulateInput(0x41);
				nd = std::chrono::system_clock::now() - strt;
			} while(nd.count() <= 6);

			continue;
		}

		if(*((uintptr_t*)(global_offsets::HostPlayer + 0x4A8)) < 1)
		{
			LogRed(L"You died!");
			Beep(432, 200);
			Beep(432, 200);
			Beep(432, 200);
			StopAutoFarming();
			StopAutoTrivia();
			break;
		}

		if(monsterCounter % 50 == 0 && monsterCounter != 0)
		{
			wchar_t monster[32] = L"monsters kill count - ";
			char c[8];
			dtoa(c, monsterCounter);
			wcscat_s(monster, ctowc(c));
			LogPurple(monster);
		}

		++monsterCounter;

		item.PickupItem();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		item.PickupItem();
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}
}