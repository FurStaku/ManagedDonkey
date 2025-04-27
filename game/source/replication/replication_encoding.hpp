#pragma once

#include "cseries/cseries.hpp"
#include "game/aim_target.hpp"
#include "units/units.hpp"

struct s_player_prediction
{
	int32 predicted_entity_index;
	int32 predicted_gamestate_index;
	uint8 control_context_identifier;
	real_point3d position;
	real_vector3d forward;
	real_vector3d up;
	real_vector3d translational_velocity;
	real_vector3d angular_velocity;
};
static_assert(sizeof(s_player_prediction) == 0x48);

enum e_aim_assist_targeting_result_flags
{
	_aim_assist_targeting_result_only_lead_vector_valid_bit = 0,
	_aim_assist_targeting_result_lead_vector_valid_bit,
	_aim_assist_targeting_result_unknown_bit2,

	k_aim_assist_targeting_result_flags
};

struct s_player_predicted_aim_assist
{
	c_aim_target_predicted predicted_aim_assist;
	real32 primary_autoaim_level;
	real32 secondary_autoaim_level;
	real_vector3d lead_vector;

	c_flags<e_aim_assist_targeting_result_flags, uint8, k_aim_assist_targeting_result_flags> flags;
};
static_assert(sizeof(s_player_predicted_aim_assist) == 0x24);

struct s_player_motion
{
	uint32 control_context;
	uint8 control_context_identifier;
	real_euler_angles2d aiming_angles;
	real_point2d throttle;
	uint16 motion_flags;
	s_unit_weapon_set weapon_set;
	uint16 zoom_level;

	// 0: primary, 1: secondary
	bool primary_predicted_fire[2];

	// 0: primary, 1: secondary
	bool secondary_predicted_fire[2];

	bool motion_sensor_velocity_threshold_exceeded;
	bool __unknown25;
	bool predicted_aim_assist_exists;
	s_player_predicted_aim_assist aim_assist;
};
static_assert(sizeof(s_player_motion) == 0x4C);

struct c_bitstream;

extern bool __cdecl player_motion_compare(s_player_motion const* player_motion_a, s_player_motion* player_motion_b);
extern bool __cdecl player_motion_decode(c_bitstream* packet, s_player_motion* player_motion);
extern void __cdecl player_motion_encode(c_bitstream* packet, s_player_motion const* player_motion);
extern int32 __cdecl player_motion_minimum_required_bits();
extern bool __cdecl player_motion_valid(s_player_motion const* player_motion);
extern bool __cdecl player_prediction_compare_identical(s_player_prediction const* player_prediction_a, s_player_prediction const* player_prediction_b);
extern bool __cdecl player_prediction_decode(c_bitstream* packet, s_player_prediction* player_prediction, bool replicated);
extern void __cdecl player_prediction_encode(c_bitstream* packet, s_player_prediction const* player_prediction, bool replicated);
extern int32 __cdecl player_prediction_minimum_required_bits();
extern bool __cdecl player_prediction_valid(s_player_prediction const* player_prediction);
extern void __cdecl predicted_aim_assist_clear(s_player_predicted_aim_assist* aim_assist);
extern bool __cdecl predicted_aim_assist_compare(s_player_predicted_aim_assist const* aim_assist_a, s_player_predicted_aim_assist* aim_assist_b);
extern bool __cdecl predicted_aim_assist_decode(c_bitstream* packet, s_player_predicted_aim_assist* aim_assist, int32 encoding_precision);
extern void __cdecl predicted_aim_assist_encode(c_bitstream* packet, s_player_predicted_aim_assist const* aim_assist, bool a3, int32 encoding_precision);

