#pragma once

#include "cseries/cseries.hpp"
#include "memory/data.hpp"

struct game_looping_sound_datum :
	s_datum_header
{
	byte __data[0x1E];
};
static_assert(sizeof(game_looping_sound_datum) == 0x20);

struct s_game_sound_globals
{
	byte __data[0x154];
};
static_assert(sizeof(s_game_sound_globals) == 0x154);

struct s_game_sound_impulse_datum
{
	byte __data[0x200];
};
static_assert(sizeof(s_game_sound_impulse_datum) == 0x200);

extern void __cdecl game_sound_dispose();
extern void __cdecl game_sound_dispose_from_old_map();
extern void __cdecl game_sound_dispose_from_old_structure_bsp(dword old_structure_bsp_mask);
extern void __cdecl game_sound_initialize();
extern void __cdecl game_sound_initialize_for_new_map();
extern void __cdecl game_sound_initialize_for_new_structure_bsp(dword new_structure_bsp_mask);
extern void __cdecl game_sound_process_update_messages();
extern void __cdecl game_sound_update(real game_seconds_elapsed);

