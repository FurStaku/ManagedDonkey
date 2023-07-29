#pragma once

#include "cseries/cseries.hpp"
#include "tag_files/tag_groups.hpp"

struct s_ai_globals_gravemind_definition;
struct s_ai_globals_styles_definition;
struct s_ai_globals_formation_definition;
struct s_ai_globals_squad_template_definition;
struct s_ai_globals_definition
{
	real ai_infantry_on_ai_weapon_damage_scale;
	real ai_vehicle_on_ai_weapon_damage_scale;
	real ai_player_vehicle_on_ai_weapon_damage_scale;
	real danger_broadly_facing;
	real danger_shooting_near;
	real danger_shooting_at;
	real danger_extremely_close;
	real danger_shield_damage;
	real danger_exetended_shield_damage;
	real danger_body_damage;
	real danger_extended_body_damage;
	c_typed_tag_reference<AI_DIALOGUE_GLOBALS_TAG> global_dialogue_tag;
	c_string_id default_mission_dialogue_sound_effect;
	real jump_down;
	real jump_step;
	real jump_crouch;
	real jump_stand;
	real jump_storey;
	real jump_tower;
	real max_jump_down_height_down;
	real max_jump_down_height_step;
	real max_jump_down_height_crouch;
	real max_jump_down_height_stand;
	real max_jump_down_height_storey;	
	real max_jump_down_height_tower;
	real_bounds hoist_step;
	real_bounds hoist_crouch;
	real_bounds hoist_stand;
	real_bounds vault_step;
	real_bounds vault_crouch;

	//PATHFINDING SEARCH RANGES
	// 
	// The maximum ranges to which firing point evaluations will do pathfinding searches. INCREASING THESE VALUES WILL ALMOST CERTAINLY HAVE A NEGATIVE IMPACT ON PERFORMANCE.
	real search_range_infantry;
	real search_range_flying;
	real search_range_vehicle;
	real search_range_giant;
	c_typed_tag_block<s_ai_globals_gravemind_definition> gravemind_properties;
	real scary_target_threhold;
	real scary_weapon_threhold;
	real player_scariness;
	real berserking_actor_scariness;
	real kamikazeing_actor_scariness;
	real invincible_scariness;
	real morph_delay_ranged;
	real morph_delay_tank;
	real morph_delay_stalker;

	// RESURRECTION
	// 
	// A few properties to help define when it is safe for a mission critical character to ressurect.
	real min_death_time;
	real projectile_distance;
	real idle_clump_distance;
	real dangerous_clump_distance;
	c_typed_tag_block<s_ai_globals_styles_definition> global_styles;
	c_typed_tag_block<s_ai_globals_formation_definition> spawn_formations;
	c_typed_tag_block<s_ai_globals_squad_template_definition> squad_templates;

	// CLUMP THROTTLING
	// 
	// Some values to help you control how much guys will throttle when they want to stick with the rest of their squad.
	real stop_dist;
	real resume_dist;
	real min_dist;
	real max_dist;
	real min_scale;

	// SQUAD PATROLLING
	// 
	// Parameters related to squad patrolling.
	real passthrough_chance;
	real search_phase_skip_chance;
	real patrol_transition_timeout;
	real patrol_maneuver_timeout;
	real_bounds patrol_search_firing_point_time;
	real patrol_isolation_distance;
	real patrol_isolation_time;

	// KUNGFU CONROL
	// 
	// These parameters control how the kung - fu circle works(i.e.when tasks have kungfu - count associated with them)
	real kungfu_deactivation_delay;

	void update_reference_names();
};
static_assert(sizeof(s_ai_globals_definition) == 0x144);

struct s_ai_globals_gravemind_definition
{
	real min_retreat_time;
	real ideal_retreat_time;
	real max_retreat_time;
};
static_assert(sizeof(s_ai_globals_gravemind_definition) == 0xC);

struct s_ai_globals_styles_definition
{
	c_typed_tag_reference<STYLE_TAG> style;

	void update_reference_names();
};
static_assert(sizeof(s_ai_globals_styles_definition) == 0x10);

struct s_ai_globals_formation_definition
{
	c_typed_tag_reference<FORMATION_TAG> formation;

	void update_reference_names();
};
static_assert(sizeof(s_ai_globals_formation_definition) == 0x10);

struct s_ai_globals_squad_template_definition
{
	c_typed_tag_reference<SQUAD_TEMPLATE_TAG> squad_template;

	void update_reference_names();
};
static_assert(sizeof(s_ai_globals_squad_template_definition) == 0x10);

