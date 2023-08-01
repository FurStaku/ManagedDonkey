#pragma once

#include "cseries/cseries.hpp"
#include "objects/object_definitions.hpp"
#include "tag_files/tag_groups.hpp"

enum e_item_definition_flags
{
	_item_definition_flag_always_maintains_z_up_bit = 0,
	_item_definition_flag_destroyed_by_explosions_bit,
	_item_definition_flag_unaffected_by_gravity_bit,
	_item_definition_flag_crate_style_collision_filter_bit,

	k_item_definition_flags
};

struct s_predicted_bitmaps;
struct _item_definition
{
	static tag const k_group_tag = ITEM_TAG;

	_object_definition object;

	// $$$ ITEM $$$

	c_flags<e_item_definition_flags, dword_flags, k_item_definition_flags> flags;
	short old_message_index;
	short sort_order;
	real old_multiplayer_on_ground_scale;
	real old_campaign_on_ground_scale;


	// NEW hud messages
	// everything you need to display stuff

	c_string_id pickup_message;
	c_string_id swap_message;
	c_string_id pickup_message_dual;
	c_string_id swap_message_dual;
	c_string_id picked_up_msg;
	c_string_id switch_to_msg;
	c_string_id switch_to_from_ai_msg;
	c_string_id notify_empty_msg;
	c_typed_tag_reference<SOUND_TAG> collision_sound;
	c_typed_tag_block<s_predicted_bitmaps> predicted_bitmaps;
	c_typed_tag_reference<DAMAGE_EFFECT_TAG> detonation_damage_effect;
	real_bounds detonation_delay; // seconds
	c_typed_tag_reference<EFFECT_TAG> detonating_effect;
	c_typed_tag_reference<EFFECT_TAG> detonation_effect;


	// Item scale settings
	// because grenades look better as coconuts. 0==1

	real single_player_ground;
	real multiplayer_ground;
	real small_unit_armed;
	real small_unit_stowed;
	real medium_unit_armed;
	real medium_unit_stowed;
	real player_unit_armed;
	real player_unit_stowed;
	real large_unit_armed;
	real large_unit_stowed;


	// Damping settings
	// how much do we damp the velocity when the item is in contact with a slow

	// ~30 == complete damping, 0 == defaults
	real grounded_angular_damping;

	// ~30 == complete damping, 0 == defaults
	real grounded_linear_damping;

	void update_reference_names();
};
static_assert(sizeof(_item_definition) == 0x1D4);

struct s_predicted_bitmaps
{
	c_typed_tag_reference<BITMAP_TAG> bitmap;

	void update_reference_names();
};
static_assert(sizeof(s_predicted_bitmaps) == sizeof(s_tag_reference));

