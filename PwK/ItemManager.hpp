#pragma once
#include "config.h"

class ItemManager
{
	typedef char(__thiscall* tPickupItem)(uintptr_t*);
	tPickupItem pickupItem;

public:
	ItemManager();

	void PickupItem();
};

