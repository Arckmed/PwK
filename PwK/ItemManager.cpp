#include "ItemManager.hpp"

ItemManager::ItemManager()
{
	pickupItem = (tPickupItem)(global_offsets::ElementBaseAddress + 0x15D84);
}

void ItemManager::PickupItem()
{
	pickupItem((uintptr_t*)global_offsets::HostPlayer);
}
