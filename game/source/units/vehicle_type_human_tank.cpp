#include "units/vehicle_type_human_tank.hpp"

void c_vehicle_type_human_tank::adjust_gravity(long vehicle_index, vector3d* gravity_acceleration)
{
	INVOKE_CLASS_MEMBER(0x00BC77F0, c_vehicle_type_human_tank, adjust_gravity, vehicle_index, gravity_acceleration);
}

//.text:00BC7840 ; 

bool c_vehicle_type_human_tank::compute_function_value(long vehicle_index, long function, real* magnitude, bool* force_active)
{
	return INVOKE_CLASS_MEMBER(0x00BC78A0, c_vehicle_type_human_tank, compute_function_value, vehicle_index, function, magnitude, force_active);
}

void c_vehicle_type_human_tank::compute_tread_speeds(long vehicle_index, real* left_tread_speed, real* right_tread_speed)
{
	INVOKE_CLASS_MEMBER(0x00BC7C20, c_vehicle_type_human_tank, compute_tread_speeds, vehicle_index, left_tread_speed, right_tread_speed);
}

void c_vehicle_type_human_tank::create_effects(long vehicle_index)
{
	//INVOKE_CLASS_MEMBER(0x00BC7CE0, c_vehicle_type_human_tank, create_effects, vehicle_index);
}

void c_vehicle_type_human_tank::deplete_function_variables(long vehicle_index)
{
	INVOKE_CLASS_MEMBER(0x00BC7CF0, c_vehicle_type_human_tank, deplete_function_variables, vehicle_index);

	//vehicle_engine_deplete_function_variables(&m_engine);
}

bool c_vehicle_type_human_tank::effected_by_vehicle_ceiling(long vehicle_index)
{
	return INVOKE_CLASS_MEMBER(0x00BC7D00, c_vehicle_type_human_tank, effected_by_vehicle_ceiling, vehicle_index);

	//return false;
}

s_vehicle_engine* const c_vehicle_type_human_tank::get_engine(long vehicle_index)
{
	//return INVOKE_CLASS_MEMBER(0x00BC7D10, c_vehicle_type_human_tank, get_engine, vehicle_index);

	return &m_engine;
}

bool c_vehicle_type_human_tank::is_stopped(long vehicle_index)
{
	return INVOKE_CLASS_MEMBER(0x00BC7D20, c_vehicle_type_human_tank, is_stopped, vehicle_index);

	//return m_stop_counter.calculate_fraction(vehicle_index) == 1.0f;
}

bool c_vehicle_type_human_tank::kills_riders_at_terminal_velocity(long vehicle_index)
{
	return INVOKE_CLASS_MEMBER(0x00BC7D50, c_vehicle_type_human_tank, kills_riders_at_terminal_velocity, vehicle_index);

	//return true;
}

bool c_vehicle_type_human_tank::physics_disabled(long vehicle_index)
{
	return INVOKE_CLASS_MEMBER(0x00BC7D60, c_vehicle_type_human_tank, physics_disabled, vehicle_index);

	//return false;
}

void __cdecl c_vehicle_type_human_tank::process_animation_channels(long vehicle_index, void(__cdecl* callback)(long, render_model_definition const*, c_animation_channel*, real, real, real, void*), void* user_data, c_animation_channel* channel, bool find_animations)
{
	INVOKE(0x00BC7D70, c_vehicle_type_human_tank::process_animation_channels, vehicle_index, callback, user_data, channel, find_animations);
}

void c_vehicle_type_human_tank::reset(long vehicle_index)
{
	INVOKE_CLASS_MEMBER(0x00BC7D80, c_vehicle_type_human_tank, reset, vehicle_index);

	//vehicle_engine_reset(&m_engine);
	//m_ground_speed_animation_id.m_subgraph = NONE;
	//m_ground_speed_animation_id.m_index = NONE;
	//m_stop_counter.reset();
}

bool c_vehicle_type_human_tank::should_override_deactivation(long vehicle_index)
{
	return INVOKE_CLASS_MEMBER(0x00BC7DB0, c_vehicle_type_human_tank, should_override_deactivation, vehicle_index);
}

void c_vehicle_type_human_tank::update_control(long vehicle_index)
{
	INVOKE_CLASS_MEMBER(0x00BC7E30, c_vehicle_type_human_tank, update_control, vehicle_index);
}

void c_vehicle_type_human_tank::update_physics(long vehicle_index, s_havok_vehicle_physics_instance* instance)
{
	INVOKE_CLASS_MEMBER(0x00BC8430, c_vehicle_type_human_tank, update_physics, vehicle_index, instance);
}

bool c_vehicle_type_human_tank::vector_is_upsides_down(long vehicle_index, vector3d const* vector)
{
	return INVOKE_CLASS_MEMBER(0x00BC8750, c_vehicle_type_human_tank, vector_is_upsides_down, vehicle_index, vector);

	//return vector->k < 0.0f;
}

