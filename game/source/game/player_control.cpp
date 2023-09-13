#include "game/player_control.hpp"

#include "game/game.hpp"
#include "memory/thread_local.hpp"

s_player_control_globals* __cdecl player_control_globals_get()
{
	if (!get_tls())
		return nullptr;

	TLS_DATA_GET_VALUE_REFERENCE(player_control_globals);
	return player_control_globals;
}

bool __cdecl player_control_get_machinima_camera_debug()
{
	if (player_control_get_machinima_camera_enabled())
		return player_control_globals_get()->machinima_camera_debug;

	return false;
}

bool __cdecl player_control_get_machinima_camera_enabled()
{
	if (game_in_progress() && !game_is_ui_shell())
		return player_control_globals_get()->machinima_camera_enabled;

	return false;
}

bool __cdecl player_control_get_machinima_camera_use_old_controls()
{
	if (player_control_get_machinima_camera_enabled())
		return player_control_globals_get()->machinima_camera_use_old_controls;

	return false;
}

void __cdecl player_control_set_machinima_camera(bool enabled, bool debug, bool use_old_controls)
{
	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->machinima_camera_enabled = enabled;
	player_control_globals->machinima_camera_debug = debug;
	player_control_globals->machinima_camera_use_old_controls = use_old_controls;
}

void __cdecl player_control_toggle_machinima_camera_enabled()
{
	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->machinima_camera_enabled = !player_control_globals->machinima_camera_enabled;
}

void __cdecl player_control_toggle_machinima_camera_use_old_controls()
{
	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->machinima_camera_use_old_controls = !player_control_globals->machinima_camera_use_old_controls;
}

void __cdecl player_control_toggle_machinima_camera_debug()
{
	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->machinima_camera_debug = !player_control_globals->machinima_camera_debug;
}

void __cdecl player_control_toggle_player_input(long user_index)
{
	s_player_control_globals* player_control_globals = player_control_globals_get();
	if (!player_control_globals)
		return;

	player_control_globals->input_user_states[user_index].player_input_locked = !player_control_globals->input_user_states[user_index].player_input_locked;
}

//enum e_input_user_index __cdecl player_mapping_get_input_user(long)
long __cdecl player_mapping_get_input_user(long user_index)
{
	return INVOKE(0x00589B00, player_mapping_get_input_user, user_index);
}

short __cdecl player_control_get_zoom_level(long user_index)
{
	return INVOKE(0x005D2D50, player_control_get_zoom_level, user_index);
}

//void __cdecl player_control_suppress_rotate_weapons(enum e_input_user_index)
void __cdecl player_control_suppress_rotate_weapons(long user_index)
{
	INVOKE(0x005D4860, player_control_suppress_rotate_weapons, user_index);
}


