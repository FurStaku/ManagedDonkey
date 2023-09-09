#pragma once

#include "cseries/cseries.hpp"

struct s_simulation_projectile_attached_event_data
{
	bool attached_to_object;
	long node_index;
	long position_encoding_type;
	real_point3d node_position;
	s_location location;
};
static_assert(sizeof(s_simulation_projectile_attached_event_data) == 0x1C);

struct s_simulation_projectile_detonate_event_data
{
	long projectile_definition_index;
	real_point3d position;
	vector3d forward;
	real damage_scale;
	byte projectile_effect_flag;
	bool collided_with_invalid_material;
	long material_index;
	s_location location;
	vector3d hit_normal;
	long absolute_player_index;

	// padding?
	byte __data[0x4];
};
static_assert(sizeof(s_simulation_projectile_detonate_event_data) == 0x40);

struct s_simulation_projectile_impact_effect_event_data
{
	long projectile_definition_index;
	real material_effect_scale;
	real material_effect_error;
	vector3d impact_direction_normal;
	real_point3d position;
	vector3d collision_plane_normal;
	long material_index;
	bool from_impact;
};
static_assert(sizeof(s_simulation_projectile_impact_effect_event_data) == 0x38);

struct s_simulation_projectile_object_impact_effect_event_data : s_simulation_projectile_impact_effect_event_data
{
	bool detonation_timer_started;
	long collision_node_index;
	long position_encoding_type;
};
static_assert(sizeof(s_simulation_projectile_object_impact_effect_event_data) == 0x44);

struct s_simulation_projectile_supercombine_request_event_data
{
	long projectile_definition_index;
};
static_assert(sizeof(s_simulation_projectile_supercombine_request_event_data) == 0x4);

