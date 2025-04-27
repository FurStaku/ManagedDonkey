#pragma once

#include "cseries/cseries.hpp"
#include "objects/objects.hpp"

struct _item_datum
{
	uint8 flags;
	uint8 inventory_state;
	int16 detonation_ticks;
	int32 ignore_object_index;
	int32 last_relevant_time;
	int32 inventory_unit_index;
	int32 last_inventory_unit_index;
};
static_assert(sizeof(_item_datum) == 0x14);

struct item_datum
{
	int32 definition_index;
	_object_datum object;
	_item_datum item;
};
static_assert(sizeof(item_datum) == sizeof(int32) + sizeof(_object_datum) + sizeof(_item_datum));

extern bool __cdecl dangerous_items_near_player(int32* out_item_index);

