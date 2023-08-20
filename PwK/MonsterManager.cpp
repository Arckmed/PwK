#include "MonsterManager.hpp"

MonsterManager::MonsterManager()
{
	observedEntityID = (uintptr_t*)(global_offsets::HostPlayer + 0x3F8);
	attackSelected = (tAttack)(global_offsets::ElementBaseAddress + 0x648D4);
	returnAddressFromID = (tReturnAddress)(global_offsets::ElementBaseAddress + 0x04D56F);
	switchMonster = (tSwitchMonster)(global_offsets::ElementBaseAddress + 0x85C44);
}

void MonsterManager::AttackSelected()
{
	attackSelected((uintptr_t*)global_offsets::HostPlayer, 0, 0, 0, 0xFFFFFFFF);
}

void MonsterManager::SwitchMonster()
{
	switchMonster((uintptr_t*)global_offsets::HostPlayer);
}

int MonsterManager::GetCurrentMonsterState()
{
	int MonsterAddress = returnAddressFromID((uintptr_t*)global_offsets::NPCManager, *observedEntityID, 0);
	int MonsterState = *(uintptr_t*)(MonsterAddress + 0x2E0);
	return MonsterState;
}

bool MonsterManager::IsCurrentMonsterAlive()
{
	int MonsterAddress = returnAddressFromID((uintptr_t*)global_offsets::NPCManager, *observedEntityID, 0);
	if(MonsterAddress)
	{
		int MonsterState = *(uintptr_t*)(MonsterAddress + 0x2E0);
		if(MonsterState == CurrentState::DYING)
			return false;

		return true;
	}
	return false;
}