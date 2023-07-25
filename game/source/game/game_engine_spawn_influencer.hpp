#pragma once

#include "tag_files/tag_groups.hpp"

struct s_dead_player_info
{
	long player_index;
	dword time;
	real_point3d position;
};
static_assert(sizeof(s_dead_player_info) == 0x14);

struct s_netgame_goal_influencer
{
	long type;
	long object_index;
};
static_assert(sizeof(s_netgame_goal_influencer) == 0x8);

struct s_netgame_goal_spawn_influence
{
	real full_weight_radius; // wu
	real fall_off_radius; // wu
	real upper_cylinder_height; // wu
	real lower_cylinder_height; // wu
	real weight;
};
static_assert(sizeof(s_netgame_goal_spawn_influence) == 0x14);

struct s_player_spawn_influence
{
	real full_weight_radius; // wu
	real fall_off_radius; // wu
	real upper_height; // wu
	real lower_height; // wu
	real weight;
};
static_assert(sizeof(s_player_spawn_influence) == 0x14);

struct s_weapon_spawn_influence
{
	c_typed_tag_reference<WEAPON_TAG> weapon;
	real full_weight_range;
	real fall_off_range;
	real fall_off_cone_radius;
	real weight;

	void update_reference_names();
};
static_assert(sizeof(s_weapon_spawn_influence) == 0x20);

struct s_vehicle_spawn_influence
{
	c_typed_tag_reference<VEHICLE_TAG> vehicle;
	real pill_radius;
	real lead_time;
	real minimum_velocity;
	real weight;

	void update_reference_names();
};
static_assert(sizeof(s_vehicle_spawn_influence) == 0x20);

struct s_projectile_spawn_influence
{
	c_typed_tag_reference<PROJECTILE_TAG> projectile;
	real lead_time;
	real collision_cylinder_radius;
	real weight;

	void update_reference_names();
};
static_assert(sizeof(s_projectile_spawn_influence) == 0x1C);

struct s_equipment_spawn_influence
{
	c_typed_tag_reference<EQUIPMENT_TAG> equipment;
	real weight;

	void update_reference_names();
};
static_assert(sizeof(s_equipment_spawn_influence) == 0x14);

