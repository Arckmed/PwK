#pragma once
#include "config.h"
#include <windows.h>

class MonsterManager
{
private:
	typedef int(__thiscall* tReturnAddress)(uintptr_t*, int, int);
	typedef char(__thiscall* tAttack)(uintptr_t*, int, int, int, int);
	typedef int(__thiscall* tSwitchMonster)(uintptr_t*);
	tSwitchMonster switchMonster;
	tReturnAddress returnAddressFromID;
	tAttack attackSelected;
	uintptr_t* observedEntityID;

	enum CurrentState
	{
		STANDING_STILL = 0,
		ATTACKING = 2,
		DYING = 4,
		WALKING = 5
	};

public:
	MonsterManager();
	void AttackSelected();
	void SwitchMonster();
	int GetCurrentMonsterState();
	bool IsCurrentMonsterAlive();
};


