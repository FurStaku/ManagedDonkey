#include "ai/ai_debug.hpp"

#include "interface/interface_constants.hpp"
#include "main/main.hpp"
#include "memory/thread_local.hpp"

void __cdecl ai_debug_render()
{
	//TLS_DATA_GET_VALUE_REFERENCE(ai_globals);
	//TLS_DATA_GET_VALUE_REFERENCE(actor_data);
	//
	//bool flag = ai_render_enabled
	//	&& (ai_render_firing_positions_all_enabled
	//		|| ai_render_lineoffire_enabled
	//		|| ai_render_lineofsight_enabled
	//		|| ai_render_ballistic_lineoffire_enabled
	//		|| ai_debug_selected_actor_unit_index != NONE
	//		&& (ai_debug_selected_actor_index == NONE || ai_render_all_actors_enabled)
	//		|| ai_debug_selected_actor_index != NONE && !ai_render_all_actors_enabled
	//		|| ai_debug_path_enabled
	//		|| ai_render_paths_failed_enabled
	//		|| ai_render_aiming_validity
	//		|| ai_render_all_actors_enabled
	//		|| ai_render_dialogue_enabled
	//		|| ai_render_dialogue_queue_enabled
	//		|| ai_render_dialogue_player_weights_enabled
	//		|| ai_render_speech_enabled
	//		|| ai_print_speech_enabled
	//		|| ai_render_spatial_effects_enabled
	//		|| ai_render_clumps_enabled
	//		|| ai_render_clump_props_enabled
	//		|| ai_render_clump_props_all_enabled
	//		|| ai_render_decisions_enabled
	//		|| ai_render_decisions_all_enabled
	//		|| ai_render_behavior_stack_all_enabled
	//		|| ai_render_stimuli_enabled
	//		|| ai_render_sectors_enabled
	//		|| ai_render_sector_geometry_errors_enabled
	//		|| ai_render_link_specific != NONE
	//		|| ai_render_links_enabled
	//		|| ai_render_user_hints_enabled
	//		|| ai_render_hints_enabled
	//		|| ai_render_object_hints_all_enabled
	//		|| ai_render_object_hints_enabled
	//		|| ai_render_object_properties_enabled
	//		|| ai_render_sector_bsps_enabled
	//		|| ai_render_giant_sector_bsps_enabled
	//		|| ai_render_sector_link_errors_enabled
	//		|| ai_render_intersection_links_enabled
	//		|| ai_render_non_walkable_sectors_enabled
	//		|| ai_render_threshold_links_enabled
	//		|| ai_render_orders_enabled
	//		|| ai_render_suppress_combat_enabled
	//		|| ai_render_objectives_enabled
	//		|| ai_render_strength_enabled
	//		|| ai_debug_tracking_data_enabled
	//		|| ai_debug_perception_data_enabled
	//		|| ai_debug_combat_status_enabled
	//		|| ai_render_tracked_props_all_enabled
	//		|| ai_render_targets_all_enabled
	//		|| ai_render_joint_behaviors_enabled
	//		|| ai_render_flocks_enabled
	//		|| ai_render_command_scripts_enabled
	//		|| ai_render_dialogue_variants_enabled
	//		|| ai_render_vehicle_interest_enabled
	//		|| ai_render_player_battle_vector_enabled);
	//
	//main_set_single_thread_request_flag(2, g_dialogue_debug_enabled | flag);
	//if (!actor_datum_available_to_current_thread() || !ai_globals->__unknown1)
	//	return;
	//
	//short_rectangle2d bounds{};
	//interface_get_current_display_settings(NULL, NULL, NULL, &bounds);
	//global_ai_debug_string_position = bounds.y1 - 20;
	//dword_143C86DD8 = (dword_143C86DD8 + 1) % 1000;
	//if (ai_debug_selected_actor_index != NONE)
	//{
	//	actor_datum* actor = actor_data[ai_debug_selected_actor_index];
	//	ai_debug_selected_actor_unit_index = actor->unit_index;
	//}
	//
	//if (ai_debug)
	//	ai_debug_select_this_actor();
	//
	//if (ai_render_enabled)
	//{
	//	if (ai_render_firing_positions_all_enabled)
	//		ai_debug_render_all_firing_positions();
	//
	//	if (ai_render_lineoffire_enabled)
	//		ai_debug_render_lineoffire();
	//
	//	if (ai_render_lineofsight_enabled)
	//		ai_debug_render_lineofsight();
	//
	//	if (ai_render_ballistic_lineoffire_enabled)
	//		ai_debug_render_ballistic_lineoffire();
	//
	//	if (ai_debug_selected_actor_unit_index != NONE
	//		&& (ai_debug_selected_actor_index == NONE || ai_render_all_actors_enabled))
	//	{
	//		ai_debug_render_squad_members(ai_debug_selected_actor_unit_index);
	//	}
	//
	//	if (ai_debug_selected_actor_index != NONE && !ai_render_all_actors_enabled)
	//		ai_debug_render_actor(ai_debug_selected_actor_index, 1u, 0i64);
	//
	//	if (ai_debug_path_enabled)
	//		ai_debug_render_path();
	//
	//	if (ai_render_paths_failed_enabled)
	//		ai_debug_render_paths_failed();
	//
	//	if (ai_render_all_actors_enabled)
	//		ai_debug_render_all_actors(ai_render_inactive_actors);
	//
	//	if (ai_render_dialogue_enabled)
	//		ai_debug_dialogue();
	//
	//	if (ai_render_dialogue_queue_enabled)
	//		ai_dialogue_render_queue();
	//
	//	if (ai_render_dialogue_player_weights_enabled)
	//		ai_dialogue_render_player_weights();
	//
	//	if (ai_render_speech_enabled || ai_print_speech_enabled)
	//		ai_debug_render_speech();
	//
	//	if (ai_render_spatial_effects_enabled)
	//		ai_debug_render_spatial_effects();
	//
	//	if (ai_render_clumps_enabled || ai_render_clump_props_enabled || ai_render_clump_dialogue || ai_render_clump_props_all_enabled)
	//	{
	//		ai_debug_render_clumps();
	//	}
	//
	//	if (ai_render_decisions_enabled)
	//		ai_debug_render_decisions(0);
	//
	//	if (ai_render_decisions_all_enabled)
	//		ai_debug_render_decisions(1);
	//
	//	if (ai_render_behavior_stack_all_enabled)
	//		ai_debug_render_behavior_stacks_all();
	//
	//	if (ai_render_character_names)
	//		ai_debug_render_character_names();
	//
	//	if (ai_render_stimuli_enabled)
	//		stimuli_debug();
	//
	//	if (ai_render_sectors_enabled)
	//		ai_debug_render_sectors();
	//
	//	if (ai_render_sector_geometry_errors_enabled)
	//		ai_render_sector_geometry_errors();
	//
	//	if (ai_render_link_specific != NONE)
	//		ai_debug_render_link_specific();
	//
	//	if (ai_render_links_enabled)
	//		ai_debug_render_links();
	//
	//	if (ai_render_user_hints_enabled)
	//		ai_render_user_hints();
	//
	//	if (ai_render_hints_enabled)
	//		ai_render_hints();
	//
	//	if (ai_render_object_hints_all_enabled)
	//	{
	//		ai_render_object_hints(0);
	//	}
	//	else if (ai_render_object_hints_enabled)
	//	{
	//		ai_render_object_hints(1);
	//	}
	//
	//	if (ai_render_object_properties_enabled)
	//		ai_render_object_properties();
	//
	//	if (ai_render_sector_bsps_enabled)
	//	{
	//		sector_bsps_debug();
	//	}
	//	else if (ai_render_giant_sector_bsps_enabled)
	//	{
	//		giant_sector_bsps_debug();
	//	}
	//
	//	if (ai_render_sector_link_errors_enabled)
	//		ai_debug_render_sector_link_errors();
	//
	//	if (ai_render_intersection_links_enabled)
	//		ai_debug_render_intersection_links();
	//
	//	if (ai_render_non_walkable_sectors_enabled)
	//		ai_debug_render_non_walkable_sectors();
	//
	//	if (ai_render_threshold_links_enabled)
	//		ai_debug_render_threshold_links();
	//
	//	if (ai_render_objectives_enabled || ai_render_strength_enabled)
	//		ai_debug_render_squads();
	//
	//	if (ai_render_suppress_combat_enabled)
	//		ai_debug_render_suppress_combat();
	//
	//	if (ai_render_ai_iterator != NONE)
	//		ai_debug_render_ai_iterator();
	//
	//	if (ai_render_vehicle_reservations)
	//		ai_debug_render_vehicle_reservations();
	//
	//	if (ai_debug_tracking_data_enabled)
	//		ai_debug_tracking_data();
	//
	//	if (ai_debug_perception_data_enabled)
	//		ai_debug_perception_data();
	//
	//	if (ai_debug_combat_status_enabled)
	//		debug_combat_status();
	//
	//	if (ai_render_tracked_props_all_enabled)
	//		ai_debug_render_tracked_props_all();
	//
	//	if (ai_render_targets_all_enabled)
	//		ai_debug_render_targets_all();
	//
	//	if (ai_render_joint_behaviors_enabled)
	//		debug_render_joint_behaviors();
	//
	//	if (ai_render_flocks_enabled)
	//		debug_render_flocks();
	//
	//	if (ai_render_command_scripts_enabled)
	//		render_command_scripts();
	//
	//	if (ai_render_dialogue_variants_enabled)
	//		render_dialogue_variants();
	//
	//	if (ai_render_dynamic_firing_positions)
	//		ai_debug_render_dynamic_firing_positions();
	//
	//	if (!ai_hide_actor_errors)
	//		debug_render_actor_errors();
	//
	//	if (ai_render_vehicle_interest_enabled)
	//		debug_render_vehicle_interest();
	//
	//	if (ai_render_player_battle_vector_enabled)
	//		debug_render_player_battle_vector();
	//
	//	if (ai_render_player_needs_vehicle)
	//		debug_render_player_needs_vehicle();
	//
	//	if (ai_render_mission_critical)
	//		debug_render_mission_critical_ai();
	//}
	//
	//if (g_dialogue_debug_enabled)
	//	ai_dialogue_render_records();
}

