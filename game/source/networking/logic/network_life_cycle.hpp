#pragma once

#include "cseries/cseries.hpp"
#include "networking/logic/life_cycle/life_cycle_manager.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_none.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_pre_game.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_start_game.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_in_game.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_end_game_write_stats.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_leaving.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_joining.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_matchmaking_start.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_matchmaking_find_match_client.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_matchmaking_find_match.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_matchmaking_find_and_assemble_match.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_matchmaking_assemble_match.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_matchmaking_select_host.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_matchmaking_arbitration.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_matchmaking_prepare_map.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_in_match.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_end_match_write_stats.hpp"
#include "networking/logic/life_cycle/life_cycle_handler_post_match.hpp"

class c_network_observer;
class c_network_session;
class c_network_session_manager;
struct s_life_cycle_matchmaking_progress;
struct s_matchmaking_gather_party_properties;
struct s_matchmaking_search_party_properties;

struct s_network_life_cycle_globals
{
	s_network_life_cycle_globals();

	bool initialized;
	byte pad[0x7];
	c_life_cycle_state_manager life_cycle_state_manager;
	c_life_cycle_state_handler_none life_cycle_state_handler_none;
	c_life_cycle_state_handler_pre_game life_cycle_state_handler_pre_game;
	c_life_cycle_state_handler_start_game life_cycle_state_handler_start_game;
	c_life_cycle_state_handler_in_game life_cycle_state_handler_in_game;
	c_life_cycle_state_handler_end_game_write_stats life_cycle_state_handler_end_game_write_stats;
	c_life_cycle_state_handler_leaving life_cycle_state_handler_leaving;
	c_life_cycle_state_handler_joining life_cycle_state_handler_joining;
	c_life_cycle_state_handler_matchmaking_start life_cycle_state_handler_matchmaking_start;
	c_life_cycle_state_handler_matchmaking_find_match_client life_cycle_state_handler_matchmaking_find_match_client;
	c_life_cycle_state_handler_matchmaking_find_match life_cycle_state_handler_matchmaking_find_match;
	c_life_cycle_state_handler_matchmaking_find_and_assemble_match life_cycle_state_handler_matchmaking_find_and_assemble_match;
	c_life_cycle_state_handler_matchmaking_assemble_match life_cycle_state_handler_matchmaking_assemble_match;
	c_life_cycle_state_handler_matchmaking_select_host life_cycle_state_handler_matchmaking_select_host;
	c_life_cycle_state_handler_matchmaking_arbitration life_cycle_state_handler_matchmaking_arbitration;
	c_life_cycle_state_handler_matchmaking_prepare_map life_cycle_state_handler_matchmaking_prepare_map;
	c_life_cycle_state_handler_in_match life_cycle_state_handler_in_match;
	c_life_cycle_state_handler_end_match_write_stats life_cycle_state_handler_end_match_write_stats;
	c_life_cycle_state_handler_post_match life_cycle_state_handler_post_match;
};
static_assert(sizeof(s_network_life_cycle_globals) == 0x3D538);
static_assert(0x00000 == OFFSETOF(s_network_life_cycle_globals, initialized));
static_assert(0x00001 == OFFSETOF(s_network_life_cycle_globals, pad));
static_assert(0x00008 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_manager));
static_assert(0x09998 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_none));
static_assert(0x099C0 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_pre_game));
static_assert(0x099F8 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_start_game));
static_assert(0x09A20 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_in_game));
static_assert(0x09A60 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_end_game_write_stats));
static_assert(0x09A90 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_leaving));
static_assert(0x09AC0 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_joining));
static_assert(0x09AF8 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_matchmaking_start));
static_assert(0x09B40 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_matchmaking_find_match_client));
static_assert(0x09B70 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_matchmaking_find_match));
static_assert(0x235D8 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_matchmaking_find_and_assemble_match));
static_assert(0x3D138 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_matchmaking_assemble_match));
static_assert(0x3D260 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_matchmaking_select_host));
static_assert(0x3D290 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_matchmaking_arbitration));
static_assert(0x3D450 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_matchmaking_prepare_map));
static_assert(0x3D488 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_in_match));
static_assert(0x3D4C8 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_end_match_write_stats));
static_assert(0x3D4F8 == OFFSETOF(s_network_life_cycle_globals, life_cycle_state_handler_post_match));

extern const char* k_life_cycle_state_descriptions[k_life_cycle_state_count]; // const char*(&k_life_cycle_state_descriptions)[k_life_cycle_state_count];
extern s_network_life_cycle_globals& life_cycle_globals;

extern bool __cdecl network_life_cycle_can_change_network_files();
extern bool __cdecl network_life_cycle_desires_qos_reply_block_for_group();
extern void __cdecl network_life_cycle_disconnect_sessions();
extern void __cdecl network_life_cycle_display_state_strings();
extern void __cdecl network_life_cycle_dispose();
extern void __cdecl network_life_cycle_end();
extern bool __cdecl network_life_cycle_game_ending();
extern bool __cdecl network_life_cycle_game_is_in_progress();
extern c_network_session* __cdecl network_life_cycle_get_group_session_for_join();
extern bool __cdecl network_life_cycle_get_matchmaking_gather_party_properties(s_matchmaking_gather_party_properties* gather_party_properties_out);
extern void __cdecl network_life_cycle_get_matchmaking_progress(s_life_cycle_matchmaking_progress* progress_out);
extern bool __cdecl network_life_cycle_get_matchmaking_search_party_properties(s_matchmaking_search_party_properties* search_party_properties_out);
extern bool __cdecl network_life_cycle_get_observer(c_network_observer** observer);
extern c_network_session* __cdecl network_life_cycle_get_squad_session_for_join();
extern e_life_cycle_state __cdecl network_life_cycle_get_state();
extern const char* __cdecl network_life_cycle_get_state_description();
extern c_network_session* __cdecl network_life_cycle_get_target_session_for_join();
extern bool __cdecl network_life_cycle_in_group_session(c_network_session** session);
extern bool __cdecl network_life_cycle_in_interactive_session(c_network_session** session);
extern bool __cdecl network_life_cycle_in_session(c_network_session** session);
extern bool __cdecl network_life_cycle_in_squad_session(c_network_session** session);
extern bool __cdecl network_life_cycle_in_system_link_advertisable_session(c_network_session** session);
extern bool __cdecl network_life_cycle_in_target_session(c_network_session** session);
extern bool __cdecl network_life_cycle_initialize(c_network_observer* observer, c_network_session_manager* session_manager, c_network_session* squad_session_one, c_network_session* squad_session_two, c_network_session* group_session);
extern bool __cdecl network_life_cycle_map_load_pending();
extern void __cdecl network_life_cycle_notify_core_load();
extern void __cdecl network_life_cycle_notify_lost_connection();
extern void __cdecl network_life_cycle_notify_out_of_sync(bool determinism_failure);
extern void __cdecl network_life_cycle_notify_qos_reply_block_set_for_group();
extern void __cdecl network_life_cycle_notify_session_disbandment_and_host_assumption(const c_network_session* session);
extern void __cdecl network_life_cycle_pause(const char* state_string, bool enabled);
extern bool __cdecl network_life_cycle_post_match_rematch_join_in_progress();
extern void __cdecl network_life_cycle_prepare_for_squad_join();
extern void __cdecl network_life_cycle_request_leave(bool leave_and_disconnect);
extern bool __cdecl network_life_cycle_set_pre_game_state();
extern bool __cdecl network_life_cycle_squad_is_offline();
extern bool __cdecl network_life_cycle_squad_local_peer_is_host();
extern bool __cdecl network_life_cycle_squad_local_peer_is_leader();
extern void __cdecl network_life_cycle_swap_squad_sessions();
extern void __cdecl network_life_cycle_swap_target_and_group_sessions();
extern void __cdecl network_life_cycle_update();

