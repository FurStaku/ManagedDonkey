#pragma once

#include "cseries/cseries.hpp"
#include "memory/data.hpp"

#define OBSERVER_SIGNATURE 'rad!'

struct s_focus_and_distance
{
	real_point3d focus;
	real distance;
};
static_assert(sizeof(s_focus_and_distance) == 0x10);

struct s_observer_depth_of_field
{
	long flags;
	real near_focal_plane_distance;
	real far_focal_plane_distance;
	real focal_depth;
	real blur_amount;
};
static_assert(sizeof(s_observer_depth_of_field) == 0x14);

struct s_observer_command
{
	dword_flags flags;

	union
	{
		struct
		{
			real_point3d focus_position;
			vector3d focus_offset;
			real_point2d crosshair_location;
			real focus_distance;
			real field_of_view;
			vector3d forward;
			vector3d up;
		};

		real parameters[16];
	};

	vector3d focus_velocity;
	real_matrix4x3 focus_space;

	long relative_space_identifier;

	real_point3d safe_position;
	real timer;

	long collision_ignore_objects[2];
	long collision_ignore_objects_count;

	real_point3d pill_base;
	real pill_height;
	real pill_width;

	union
	{
		struct
		{
			byte position_flags;
			byte focus_offset_flags;
			byte view_offset_flags;
			byte distance_flags;
			byte field_of_view_flags;
			byte orientation_flags;
		};

		byte parameter_flags[6];
	};

	union
	{
		struct
		{
			real position_timer;
			real focus_offset_timer;
			real view_offset_timer;
			real distance_timer;
			real field_of_view_timer;
			real orientation_timer;
		};

		real parameter_timers[6];
	};

	s_observer_depth_of_field depth_of_field;
};
static_assert(sizeof(s_observer_command) == 0xEC);

struct s_observer_result
{
	real_point3d position;
	s_location location;
	vector3d velocity;
	vector3d rotation;
	vector3d forward;
	vector3d up;
	real horizontal_field_of_view;
	s_observer_depth_of_field depth_of_field;
	real aspect_ratio;
	vector2d view_offset;
	real magic_crosshair_offset;
	real vertical_field_of_view;
	real field_of_view_scale;
};
static_assert(sizeof(s_observer_result) == 0x70);

struct s_observer_derivative
{
	union
	{
		struct
		{
			vector3d focus_position;
			vector3d focus_offset;
			vector2d view_offset;
			real focus_distance;
			real field_of_view;
			vector3d rotation;
		};

		real n[13];
	};
};

struct s_observer
{
	long header_signature;
	s_observer_command* pending_command;
	s_observer_command last_command;
	bool updated_for_frame;
	bool first_command;
	bool is_relative;
	bool variable_up;
	real geometry_anticipation_buffer_scale;
	real geometry_anticipation_buffer_scale_velocity;
	long collision_ignore_object_a;
	long collision_ignore_object_b;
	bool result_valid;
	s_observer_result result;

	union
	{
		struct
		{
			real_point3d focus_position;
			vector3d focus_offset;
			vector2d view_offset;
			real focus_distance;
			real horizontal_field_of_view;
			vector3d forward;
			vector3d up;
		};

		real positions[16];
	};

	real_matrix4x3 focus_space;

	s_observer_derivative velocities;
	s_observer_derivative accelerations;
	real a[13];
	real b[13];
	real c[13];
	real d[13];
	real e[13];
	real f[13];
	s_observer_derivative displacements;

	long trailer_signature;
};
static_assert(sizeof(s_observer) == 0x3C8);

struct s_observer_globals
{
	real dtime;
	s_observer observers[4];
	bool first_call;
	bool bsp_lightmap_block_requested_for_next_tick;
	bool full_block_requested_for_next_tick;
};
static_assert(sizeof(s_observer_globals) == 0xF28);

extern real& g_observer_wave_height;
extern real& g_camera_speed;

extern bool g_debug_observer_render;

struct s_collision_test_flags;

extern void __cdecl observer_adopt_global_update_list();
extern void __cdecl observer_apply_camera_effect(long user_index);
extern void __cdecl observer_apply_rotational_displacement(vector3d const* in_vector, vector3d* out_vector1, vector3d* out_vector2);
extern void __cdecl observer_block_for_one_frame();
extern void __cdecl observer_build_result_from_point_and_vectors(s_observer_result* out_result, real_point3d const* position, vector3d const* forward, vector3d const* up);
extern void __cdecl observer_clear(s_observer* observer);
extern void __cdecl observer_clear_all();
extern void __cdecl observer_clear_global_update_list();
extern s_collision_test_flags __cdecl observer_collision_flags_get(long user_index);
extern bool __cdecl sub_611B90(long user_index, real_point3d* point_a, real_point3d* point_b, vector3d* vector, real scale, long first_ignore_object_index, long second_ignore_object_index, real* collision_scale);
extern bool __cdecl sub_611C30(long user_index, real_point3d* point_a, real_point3d* point_b, long first_ignore_object_index, long second_ignore_object_index, real* collision_scale);
extern void __cdecl observer_command_clear(s_observer_command* command);
extern void __cdecl observer_command_get_collision_ignore_objects(long user_index, s_observer_command const* command, long* out_first_ignore_object_index, long* out_second_ignore_object_index);
extern bool __cdecl observer_command_has_finished(long user_index);
extern void __cdecl observer_compute_result(long user_index, s_focus_and_distance* focus_and_distance);
extern void __cdecl observer_compute_view_offset_matrix(long user_index, real_matrix4x3* view_offset_matrix);
extern void __cdecl observer_dispose();
extern void __cdecl observer_dispose_from_old_map();
extern void __cdecl observer_dispose_from_old_structure_bsp(dword old_structure_bsp_mask);
extern void __cdecl observer_game_tick();
extern s_observer* __cdecl observer_get(long user_index);
extern s_observer_result const* observer_get_camera(long user_index);
extern real __cdecl observer_get_max_wave_height();
extern real __cdecl observer_get_near_plane_farthest_distance(real horizontal_fov, real vertical_fov);
extern s_observer_globals* observer_globals_get();
extern void __cdecl observer_initialize();
extern void __cdecl observer_initialize_after_load_saved_game(long flags);
extern void __cdecl observer_initialize_before_saved_game(long flags);
extern void __cdecl observer_initialize_for_new_map();
extern void __cdecl observer_initialize_for_new_structure_bsp(dword new_structure_bsp_mask);
extern void __cdecl observer_initialize_for_saved_game(long flags);
extern void __cdecl observer_obsolete_position(long user_index);
extern void __cdecl observer_pass_time(long user_index);
extern void __cdecl observer_perform_collision(long user_index, s_focus_and_distance const* focus_and_distance, real world_seconds_elapsed);
extern void __cdecl observer_post_global_update_list();
extern void __cdecl observer_result_clear(s_observer_result* result);
extern void __cdecl observer_result_compute_parameters(s_observer_result* result);
extern void __cdecl observer_result_set_position(long user_index, real_point3d const* position, real distance, vector3d const* forward);
extern bool __cdecl observer_result_valid(long user_index);
extern void __cdecl observer_rotational_displacement(vector3d const* forward0, vector3d const* up0, vector3d const* forward1, vector3d const* up1, vector3d* displacement);
extern void __cdecl observer_set_camera(long user_index, s_observer_command* command);
extern real __cdecl observer_suggested_field_of_view();
extern real __cdecl observer_suggested_field_of_view_change_time();
extern s_observer_result const* __cdecl observer_try_and_get_camera(long user_index);
extern void __cdecl observer_update(real world_seconds_elapsed);
extern void __cdecl observer_update_accelerations(long user_index);
extern void __cdecl observer_update_command(long user_index);
extern void __cdecl observer_update_displacements(long user_index);
extern void __cdecl observer_update_polynomial(long user_index);
extern void __cdecl observer_update_positions(long user_index);
extern void __cdecl observer_update_velocities(long user_index);
extern bool __cdecl observer_valid_camera_command(s_observer_command* command);
extern void __cdecl observer_validate_camera_command(s_observer_command* command);
extern bool __cdecl valid_field_of_view(real field_of_view);
extern bool __cdecl valid_focus_distance(real focus_distance);
extern bool __cdecl valid_timer(real timer);
extern bool __cdecl valid_world_real(real world_real);
extern bool __cdecl valid_world_real_point3d(real_point3d* world_real_point);
extern void __cdecl debug_render_observer();

