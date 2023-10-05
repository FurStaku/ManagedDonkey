#pragma once

#include "ai/behavior.hpp"
#include "cseries/cseries.hpp"
#include "tag_files/tag_groups.hpp"

enum e_combat_status
{
	_combat_status_latch_at_idle = 0,
	_combat_status_latch_at_alert,
	_combat_status_latch_at_combat,

	k_combat_status_count
};

enum e_style_attitude
{
	_style_attitude_normal = 0,
	_style_attitude_timid,
	_style_attitude_aggressive,

	k_style_attitude_count
};

enum e_style_control_flags
{
	_style_control_flag_new_behaviors_default_to_on_bit = 0,

	k_style_control_flags
};

struct special_movement_definition;
struct style_behavior_name;
struct style_palette_entry
{
	c_static_string<k_tag_string_length> name;

	// Combat status decay options
	// 
	// Controls how combat status is allowed to be automatically reduced in the absence of combat stimuli.
	// 'Latch at X' means that once the level of x is attained (and/or surpassed) the combat status never falls below it.
	// Not applicable when style is applied to a character tag.
	c_enum<e_combat_status, short, _combat_status_latch_at_idle, k_combat_status_count> combat_status_decay_options;

	// Atittude
	// 
	// Indicates general stance for style.
	// This tells us which of the property blocks in the character definition to reference (e.g. timid defense properties).
	// Not applicable when style is applied to a character tag.
	c_enum<e_style_attitude, short, _style_attitude_normal, k_style_attitude_count> atittude;

	// Style Behavior Control
	// 
	// Check the appropriate box to turn on/off the given behavior
	c_flags<e_style_control_flags, dword, k_style_control_flags> style_control;

	c_static_flags<k_behavior_count> behaviors;

	c_typed_tag_block<special_movement_definition> special_movement;
	c_typed_tag_block<style_behavior_name> behavior_list;
};
static_assert(sizeof(style_palette_entry) == 0x5C);

enum e_special_movement_flags
{
	_special_movement_flag_jump_bit = 0,
	_special_movement_flag_climb_bit,
	_special_movement_flag_vault_bit,
	_special_movement_flag_mount_bit,
	_special_movement_flag_hoist_bit,
	_special_movement_flag_wall_jump_bit,
	_special_movement_flag_na_bit,
	_special_movement_flag_rail_bit,
	_special_movement_flag_seam_bit,
	_special_movement_flag_door_bit,

	k_special_movement_flags
};

struct special_movement_definition
{
	c_flags<e_special_movement_flags, dword, k_special_movement_flags> special_movement1;
};
static_assert(sizeof(special_movement_definition) == sizeof(dword));

struct style_behavior_name
{
	c_static_string<k_tag_string_length> behavior_name;
};
static_assert(sizeof(style_behavior_name) == sizeof(c_static_string<k_tag_string_length>));

extern long __cdecl style_get_by_name(char const* name);

