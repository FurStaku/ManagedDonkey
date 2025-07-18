#pragma once

#include "cseries/cseries.hpp"
#include "game/players.hpp"
#include "interface/c_gui_screen_widget.hpp"
#include "networking/online/online_service_record.hpp"

class c_controller_input_message;

struct s_start_menu_breadcrumb
{
	int32 screen_id;
	int32 element_handle;
};
static_assert(sizeof(s_start_menu_breadcrumb) == 0x8);

class c_start_menu_screen_widget :
	public c_gui_screen_widget
{
public:
	c_start_menu_screen_widget(int32 name) :
		c_gui_screen_widget(name)
	{
		DECLFUNC(0x00ADFE60, void, __thiscall, c_start_menu_screen_widget*, int32)(this, name);
	}

	bool __thiscall handle_controller_input_message_(c_controller_input_message* message);
	static bool __cdecl handle_global_start_button_press_(c_controller_input_message* message);
	static bool __cdecl load_start_menu(e_controller_index controller_index, const s_player_identifier* player_identifier, const uns64* player_xuid, const s_service_record_identity* identity, const s_start_menu_breadcrumb* breadcrumbs, int32 breadcrumb_count);

protected:
	s_player_identifier m_owner_player_id;
	s_player_identifier m_target_player_id;
	uns64 m_target_player_xuid;
	s_service_record_identity m_service_record_identity;
	real32 m_old_film_playback_speed;
	c_static_stack<s_start_menu_breadcrumb, 8> m_breadcrumbs;
	int32 m_requested_pane;
	bool m_breadcrumb_to_load_valid;
	s_start_menu_breadcrumb m_breadcrumb_to_load;
	bool m_is_rooted;
	bool m_wants_to_pause_game_time;
};
static_assert(sizeof(c_start_menu_screen_widget) == sizeof(c_gui_screen_widget) + 0x718);

