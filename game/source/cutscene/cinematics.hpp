#pragma once

#include "cseries/cseries.hpp"

struct s_cinematic_new_globals_definition
{
	byte __data[0x3C];
};
static_assert(sizeof(s_cinematic_new_globals_definition) == 0x3C);

struct s_cinematic_globals_definition
{
	byte __unknown0[4];
	bool letter_box;
	bool cinematic_in_progress;
	bool cinematic_skip_in_progress;
	bool cinematic_suppress_bsp_object_creation;
	byte __unknown8[24];
	dword subtitle_string_id;
	real subtitle_time_shown;
	real subtitle_time_shown2;
	byte __unknown2C[2];
	bool outro_start_stop;
	byte __unknown2F[10201];
};
static_assert(sizeof(s_cinematic_globals_definition) == 0x2808);

struct s_cinematic_light_globals
{
	byte __data[0xB2C8];
};
static_assert(sizeof(s_cinematic_light_globals) == 0xB2C8);

struct s_game_non_bsp_zone_set;
struct c_scenario_resource_registry;

extern void __cdecl cinematic_dispose();
extern void __cdecl cinematic_dispose_from_old_map();
extern void __cdecl cinematic_dispose_from_old_non_bsp_zone_set(s_game_non_bsp_zone_set const* non_bsp_zone_set);
extern void __cdecl cinematic_dispose_from_old_structure_bsp(dword structure_bsp_mask);
extern void __cdecl cinematic_game_pause_handler(bool paused);
extern bool __cdecl cinematic_in_progress();
extern void __cdecl cinematic_initialize();
extern void __cdecl cinematic_initialize_for_new_map();
extern void __cdecl cinematic_initialize_for_new_non_bsp_zone_set(s_game_non_bsp_zone_set const* non_bsp_zone_set);
extern void __cdecl cinematic_initialize_for_new_structure_bsp(dword structure_bsp_mask);
extern void __cdecl cinematic_prepare_for_new_zone_set(dword a1, dword a2);
extern void __cdecl cinematic_prepare_for_non_bsp_zone_set_switch(s_game_non_bsp_zone_set const* a1, s_game_non_bsp_zone_set const* a2, c_scenario_resource_registry* resource_registry);
extern void __cdecl cinematic_update();
extern void __cdecl cinematics_game_tick();
extern void __cdecl draw_quad(short_rectangle2d* rect, dword color);

extern void cinematic_debug_camera_control_update();

