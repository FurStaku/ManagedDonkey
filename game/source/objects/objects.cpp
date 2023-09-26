#include "objects/objects.hpp"

#include "cache/cache_files.hpp"
#include "memory/module.hpp"
#include "memory/thread_local.hpp"
#include "models/model_definitions.hpp"
#include "physics/havok.hpp"
#include "render/render_debug.hpp"

#include <intrin.h>
#include <math.h>

HOOK_DECLARE(0x00B32130, object_render_debug);

bool debug_objects = true;
bool debug_objects_early_movers = false;
bool debug_objects_sound_spheres = false;
bool debug_objects_indices = false;
bool debug_objects_programmer = false;
bool debug_objects_garbage = false;
bool debug_objects_names = false;
bool debug_objects_full_names = false;
bool debug_objects_active_nodes = false;
bool debug_objects_animation_times = false;
bool debug_objects_functions = false;
bool debug_objects_position_velocity = false;
bool debug_objects_origin = false;
bool debug_objects_root_node = false;
bool debug_objects_bounding_spheres = false;
bool debug_objects_attached_bounding_spheres = false;
bool debug_objects_dynamic_render_bounding_spheres = false;
bool debug_objects_model_targets = false;
bool debug_objects_collision_models = false;
bool debug_objects_profile_times = false;
bool debug_objects_water_physics = false;
bool debug_objects_physics_models = false;
bool debug_objects_contact_points = false;
bool debug_objects_constraints = false;
bool debug_objects_vehicle_physics = false;
bool debug_objects_mass = false;
bool debug_objects_pathfinding = false;
bool debug_objects_node_bounds = false;
bool debug_objects_animation = false;

object_header_datum const* __cdecl object_header_get(long object_index)
{
	TLS_DATA_GET_VALUE_REFERENCE(object_header_data);
	return static_cast<object_header_datum*>(datum_try_and_get(*object_header_data, object_index));
}

void* __cdecl object_get_and_verify_type(long object_index, dword object_type_mask)
{
	//ASSERT(game_state_is_locked(), "someone is calling object_get when the game state is locked");

	byte* object = (byte*)object_header_get(object_index)->datum;
	REFERENCE_DECLARE(object + 0x94, c_object_identifier, object_identifier);

	if (!_bittest((long*)&object_type_mask, object_identifier.m_type.get()))
	{
		c_static_string<256> string_builder;
		string_builder.print_line("got an object type we didn't expect (expected one of 0x%08x but got #%d).",
			object_type_mask,
			object_identifier.m_type.get());

		ASSERT(!_bittest((long*)&object_type_mask, object_identifier.m_type.get()), string_builder.get_string());
	}

	return object;
}

e_object_type __cdecl object_get_type(long object_index)
{
	return INVOKE(0x0046DC70, object_get_type, object_index);
}

long __cdecl cluster_get_first_collideable_object(long* datum_index, s_cluster_reference cluster_reference)
{
	return INVOKE(0x00B27EB0, cluster_get_first_collideable_object, datum_index, cluster_reference);
}

long __cdecl cluster_get_first_collideable_object_and_payload(long* datum_index, s_cluster_reference cluster_reference, s_object_cluster_payload const** payload)
{
	return INVOKE(0x00B27EE0, cluster_get_first_collideable_object_and_payload, datum_index, cluster_reference, payload);
}

long __cdecl cluster_get_first_noncollideable_object_and_payload(long* datum_index, s_cluster_reference cluster_reference, s_object_cluster_payload const** payload)
{
	return INVOKE(0x00B27F40, cluster_get_first_noncollideable_object_and_payload, datum_index, cluster_reference, payload);
}

long __cdecl cluster_get_next_collideable_object(long* datum_index)
{
	return INVOKE(0x00B27F70, cluster_get_next_collideable_object, datum_index);
}

long __cdecl cluster_get_next_collideable_object_and_payload(long* datum_index, s_object_cluster_payload const** payload)
{
	return INVOKE(0x00B27FA0, cluster_get_next_collideable_object_and_payload, datum_index, payload);
}

long __cdecl cluster_get_next_noncollideable_object_and_payload(long* datum_index, s_object_cluster_payload const** payload)
{
	return INVOKE(0x00B28000, cluster_get_next_noncollideable_object_and_payload, datum_index, payload);
}

void __cdecl object_delete(long object_index)
{
	INVOKE(0x00B2CD10, object_delete, object_index);
}

bool __cdecl object_function_get_function_value(long object_index, s_object_function_definition const* function, long object_definition_index, real* out_function_magnitude, bool* deterministic)
{
	return INVOKE(0x00B2DA20, object_function_get_function_value, object_index, function, object_definition_index, out_function_magnitude, deterministic);
}

bool __cdecl object_get_function_value(long object_index, long function_name, long object_definition_index, real* out_function_magnitude)
{
	return INVOKE(0x00B2E030, object_get_function_value, object_index, function_name, object_definition_index, out_function_magnitude);
}

short __cdecl object_get_markers_by_string_id(long object_index, string_id marker_name, object_marker* markers, short maximum_marker_count)
{
	return INVOKE(0x00B2E3C0, object_get_markers_by_string_id, object_index, marker_name, markers, maximum_marker_count);
}

real_matrix4x3* __cdecl object_get_node_matrix(long object_index, short node_index)
{
	return INVOKE(0x00B2E450, object_get_node_matrix, object_index, node_index);
}

void __cdecl object_get_orientation(long object_index, vector3d* forward, vector3d* up)
{
	INVOKE(0x00B2E490, object_get_orientation, object_index, forward, up);
}

real_point3d* __cdecl object_get_origin(long object_index, real_point3d* origin)
{
	return INVOKE(0x00B2E5A0, object_get_origin, object_index, origin);
}

long __cdecl object_get_ultimate_parent(long object_index)
{
	return INVOKE(0x00B2EAB0, object_get_ultimate_parent, object_index);
}

void __cdecl object_get_velocities(long object_index, vector3d* linear_velocity, vector3d* angular_velocity)
{
	INVOKE(0x00B2EB30, object_get_velocities, object_index, linear_velocity, angular_velocity);
}

real_matrix4x3* __cdecl object_get_world_matrix(long object_index, real_matrix4x3* matrix)
{
	return INVOKE(0x00B2EC60, object_get_world_matrix, object_index, matrix);
}

long c_object_iterator_base::get_index()
{
	return m_index;
}

void __cdecl c_object_iterator_base::object_iterator_begin_internal(dword_flags type_flags, dword header_mask, dword match_flags, long object_index)
{
	DECLFUNC(0x00B2F4B0, void, __thiscall, c_object_iterator_base*, dword_flags, dword, dword, long)(this, type_flags, header_mask, match_flags, object_index);
}

bool __cdecl c_object_iterator_base::object_iterator_next_internal()
{
	return DECLFUNC(0x00B2F500, bool, __thiscall, c_object_iterator_base*)(this);
}

bool __cdecl c_object_iterator_base::object_iterator_next_with_match_flags_internal()
{
	return DECLFUNC(0x00B2F5A0, bool, __thiscall, c_object_iterator_base*)(this);
}

object_datum* __cdecl c_object_iterator_base::get_datum_internal()
{
	return m_datum;
}

bool __cdecl object_load_scenario_placement_matrices(long object_index)
{
	return INVOKE(0x00B2F890, object_load_scenario_placement_matrices, object_index);
}

long __cdecl object_new(object_placement_data* placement_data)
{
	return INVOKE(0x00B30440, object_new, placement_data);
}

void __cdecl object_placement_data_new(object_placement_data* placement_data, long object_definition_index, long object_datum_index, s_damage_owner const* damage_owner)
{
	INVOKE(0x00B31590, object_placement_data_new, placement_data, object_definition_index, object_datum_index, damage_owner);
}

void __cdecl object_placement_data_set_location(object_placement_data* data, struct s_location const* location)
{
	INVOKE(0x00B31750, object_placement_data_set_location, data, location);
}

void __cdecl object_postprocess_node_matrices(long object_index)
{
	INVOKE(0x00B31770, object_postprocess_node_matrices, object_index);
}

void __cdecl object_pre_delete_recursive(long object_index, bool a2)
{
	INVOKE(0x00B31810, object_pre_delete_recursive, object_index, a2);
}

bool __cdecl object_predict(long object_index, bool low)
{
	return INVOKE(0x00B31890, object_predict, object_index, low);
}

bool __cdecl object_predict_all(long object_index)
{
	//return INVOKE(0x00B31910, object_predict_all, object_index);

	return object_predict(object_index, false);
}

bool __cdecl object_predict_low(long object_index)
{
	//return INVOKE(0x00B31930, object_predict_low, object_index);

	return object_predict(object_index, true);
}

void object_prepare_axis_vectors(long object_index, vector3d* forward, vector3d* up)
{
	INVOKE(0x00B31950, object_prepare_axis_vectors, object_index, forward, up);
}

//.text:00B31B80 ; void __cdecl object_queue_render_thread_message(long, enum e_object_render_thread_message_type, short)

void __cdecl object_reconnect_to_map(long object_index, bool a2, s_location const* location)
{
	INVOKE(0x00B31BD0, object_reconnect_to_map, object_index, a2, location);
}

void __cdecl object_reconnect_to_physics(long object_index)
{
	INVOKE(0x00B31E20, object_reconnect_to_physics, object_index);
}

void __cdecl object_register_scenario_object(long object_index)
{
	INVOKE(0x00B31E80, object_register_scenario_object, object_index);
}

void __cdecl object_reinitialize_from_placement(long object_index, object_placement_data* data, bool at_rest)
{
	INVOKE(0x00B31EF0, object_reinitialize_from_placement, object_index, data, at_rest);
}

//.text:00B320A0
//.text:00B32100

void __cdecl object_render_debug(long object_index)
{
	if (TEST_BIT(_object_mask_sound_scenery, object_get_type(object_index)) && !debug_objects_sound_spheres)
		return;

	object_render_debug_internal(object_index);
}

//.text:00B32140

void __cdecl object_reset(long object_index)
{
	INVOKE(0x00B32160, object_reset, object_index);
}

void __cdecl object_reset_interpolation(long object_index)
{
	INVOKE(0x00B321A0, object_reset_interpolation, object_index);
}

//.text:00B321F0
//.text:00B32400
//.text:00B324A0 ; object_reverse_compute_node_orientations_from_matrices, 2 args
//.text:00B32540 ; object_reverse_compute_node_orientations_from_matrices, 5 args

void __cdecl object_set_always_active(long object_index, bool always_active)
{
	INVOKE(0x00B32730, object_set_always_active, object_index, always_active);
}

void __cdecl object_set_at_rest(long object_index, bool at_rest)
{
	INVOKE(0x00B327F0, object_set_at_rest, object_index, at_rest);
}

bool __cdecl object_set_base_change_color_by_index(long object_index, long color_index, real_rgb_color const* color)
{
	return INVOKE(0x00B328F0, object_set_base_change_color_by_index, object_index, color_index, color);
}

//.text:00B329A0
//.text:00B329E0

void __cdecl object_set_custom_animations_hold_on_last_frame(bool custom_animations_hold_on_last_frame)
{
	INVOKE(0x00B32A70, object_set_custom_animations_hold_on_last_frame, custom_animations_hold_on_last_frame);
}

void __cdecl object_set_custom_animations_prevent_lipsync_head_movement(bool custom_animations_prevent_lipsync_head_movement)
{
	INVOKE(0x00B32AA0, object_set_custom_animations_prevent_lipsync_head_movement, custom_animations_prevent_lipsync_head_movement);
}

//.text:00B32AD0
//.text:00B32B80
//.text:00B32C20 ; object_set_garbage

void __cdecl object_set_hidden(long object_index, bool hidden)
{
	INVOKE(0x00B32D50, object_set_hidden, object_index, hidden);
}

void __cdecl object_set_in_limbo(long object_index, bool deactivate)
{
	INVOKE(0x00B32E20, object_set_in_limbo, object_index, deactivate);
}

//.text:00B32EE0
//.text:00B32F20 ; object_set_initial_change_colors
//.text:00B33290 ; object_set_invalid_for_recycling
//.text:00B332F0
//.text:00B333F0 ; object_set_model_state_property
//.text:00B33410 ; object_set_model_state_property_per_region

void __cdecl object_set_object_index_for_name_index(short name_index, long object_index)
{
	INVOKE(0x00B334F0, object_set_object_index_for_name_index, name_index, object_index);
}

void __cdecl object_set_position(long object_index, real_point3d const* desired_position, vector3d const* desired_forward, vector3d const* desired_up, s_location const* location)
{
	//INVOKE(0x00B33530, object_set_position, object_index, desired_position, desired_forward, desired_up, location);

	object_set_position_direct(object_index, desired_position, desired_forward, desired_up, location, false);
}

void __cdecl object_set_position_direct(long object_index, real_point3d const* desired_position, vector3d const* desired_forward, vector3d const* desired_up, s_location const* location, bool in_editor)
{
	INVOKE(0x00B33550, object_set_position_direct, object_index, desired_position, desired_forward, desired_up, location, in_editor);
}

void __cdecl object_set_position_in_editor(long object_index, real_point3d const* desired_position, vector3d const* desired_forward, vector3d const* desired_up, s_location const* location, bool at_rest)
{
	//INVOKE(0x00B33600, object_set_position_in_editor, object_index, desired_position, desired_forward, desired_up, location, at_rest);
	
	object_set_position_direct(object_index, desired_position, desired_forward, desired_up, location, true);
	object_load_scenario_placement_matrices(object_index);
	if (at_rest && TEST_BIT(_object_mask_editor_placeable_objects, object_get_type(object_index)))
		object_set_at_rest(object_index, false);
}

void __cdecl object_set_position_in_sandbox_editor(long object_index, real_point3d const* desired_position, vector3d const* desired_forward, vector3d const* desired_up, s_location const* location)
{
	//INVOKE(0x00B33670, object_set_position_in_sandbox_editor, object_index, desired_position, desired_forward, desired_up, location);

	object_set_position_direct(object_index, desired_position, desired_forward, desired_up, location, true);
}

bool __cdecl object_set_position_internal(long object_index, real_point3d const* desired_position, vector3d const* desired_forward, vector3d const* desired_up, s_location const* location, bool compute_node_matrices, bool set_havok_object_position, bool in_editor, bool disconnected)
{
	return INVOKE(0x00B33690, object_set_position_internal, object_index, desired_position, desired_forward, desired_up, location, compute_node_matrices, set_havok_object_position, in_editor, disconnected);
}

void* __cdecl object_try_and_get_and_verify_type(long object_index, dword object_type_mask)
{
	return INVOKE(0x00B34490, object_try_and_get_and_verify_type, object_index, object_type_mask);
}

void __cdecl object_debug_teleport(long object_index, real_point3d const* position)
{
	if (void* object = object_try_and_get_and_verify_type(object_index, 0xFFFFFFFF))
	{
		dword_flags flags = reinterpret_cast<dword_flags*>(object)[1];

		havok_can_modify_state_allow();
		if (TEST_BIT(flags, 7))
			object_set_in_limbo(object_index, false);
		object_set_position_internal(object_index, position, nullptr, nullptr, nullptr, false, true, false, true);
		havok_can_modify_state_disallow();
	}
	else
	{
		c_console::write_line("Failed to get a valid object in %s.", __FUNCTION__);
	}
}

void __cdecl object_get_debug_name(long object_index, bool full_name, c_static_string<256>* name)
{
	byte* object = static_cast<byte*>(object_get_and_verify_type(object_index, NONE));

	if (!object)
	{
		name->print("Unknown");
		return;
	}

	REFERENCE_DECLARE(object, long, object_definition_index);
	REFERENCE_DECLARE(object + 0x9C, short, name_index);
	REFERENCE_DECLARE(object + 0xBA, char, model_variant_index);

	name->clear();
	if (name_index != NONE)
	{
		s_scenario* scenario = global_scenario_get();
		scenario_object_name& object_name = scenario->object_names[name_index];

		name->append_print("%s|n", object_name.name.get_string());
	}

	tag group_tag = tag_get_group_tag(object_definition_index);
	char const* group_tag_name = tag_group_get_name(group_tag);
	char const* tag_name = tag_get_name(object_definition_index);

	if (!full_name)
		tag_name = tag_name_strip_path(tag_get_name(object_definition_index));

	name->append_print("%s.%s|n", tag_name, group_tag_name);

	if (model_variant_index == NONE)
	{
		name->append("[default]|n");
	}
	else
	{
		_object_definition* object_definition = static_cast<_object_definition*>(tag_get(OBJECT_TAG, object_definition_index));

		s_model_definition* model_definition = nullptr;
		if (object_definition->model.index != NONE)
			model_definition = object_definition->model.cast_to<s_model_definition>();

		//if (model_definition && model_variant_index < 128 && model_variant_index < model_definition)
		//{
		//
		//}
		//else
		//{
		//	name->append_print("[invalid! %d]|n", model_variant_index);
		//}
	}
}

void __cdecl object_render_debug_internal(long object_index)
{
	object_header_datum const* object_header = object_header_get(object_index);
	byte* object = static_cast<byte*>(object_get_and_verify_type(object_index, NONE));

	REFERENCE_DECLARE(object, long, object_definition_index);
	_object_definition* object_definition = static_cast<_object_definition*>(tag_get(OBJECT_TAG, object_definition_index));

	c_static_string<4096> string;

	if (debug_objects_indices)
		string.append_print("%d (%#x)|n", object_index, object_index);

	if (debug_objects_programmer)
	{
		REFERENCE_DECLARE(object + 4, dword_flags, object_flags);

		string.append_print("header flags: %04x|n", object_header->flags);
		string.append_print("datum flags: %08x|n", object_flags);
	}

	if (debug_objects_garbage)
	{
		REFERENCE_DECLARE(object + 0x127, byte_flags, recycling_flags);
		REFERENCE_DECLARE(object + 0x12C, long, recycling_time);

		if (TEST_BIT(recycling_flags, 0))
		{
			string.append("never-garbage|n");
		}
		else if (TEST_BIT(recycling_flags, 1))
		{
			if (game_time_get() >= recycling_time)
			{
				string.append("garbage|n");
			}
			else
			{
				string.append_print("garbage in %d|n", recycling_time - game_time_get());
			}
		}
	}

	if (debug_objects_names)
	{
		c_static_string<256> name;
		object_get_debug_name(object_index, debug_objects_full_names, &name);
		string.append_print("%s", name.get_string());
	}

	if (debug_objects_active_nodes)
	{
		//debug_objects_animation_times
	}

	if (debug_objects_functions)
	{
		for (s_object_function_definition& function : object_definition->functions)
		{
			real function_magnitude = 0.0f;
			bool deterministic = false;

			bool import_function_value = object_get_function_value(object_index, function.import_name.get_value(), object_definition_index, &function_magnitude);
			string.append_print("%s: %s %.2f->", function.import_name.get_string(), import_function_value ? "ON" : "OFF", function_magnitude);

			bool export_function_value = object_function_get_function_value(object_index, &function, object_definition_index, &function_magnitude, &deterministic);
			string.append_print("%s: %s %.2f|n", function.export_name.get_string(), export_function_value ? "ON" : "OFF", function_magnitude);
		}
	}

	if (debug_objects_position_velocity)
	{
		REFERENCE_DECLARE(object + 0x2C, real, bounding_sphere_radius);

		real_matrix4x3 matrix{};
		vector3d linear_velocity{};

		object_get_world_matrix(object_index, &matrix);
		object_get_velocities(object_index, &linear_velocity, nullptr);

		render_debug_matrix(true, &matrix, bounding_sphere_radius);
		render_debug_vector(true, &matrix.center, &linear_velocity,1.0f, global_real_argb_yellow);
	}

	if (debug_objects_origin)
	{
		real a1 = 0.1f;
		real a2 = 0.4f;
		real seconds = game_ticks_to_seconds(real(game_time_get()));
		real angle = real(seconds * TWO_PI) / 3.0f;
		real cos_angle = cosf(angle);
		real radius = (((cos_angle + 1.0f) * a2) * 0.5f) + a1;

		real_point3d origin{};
		object_get_origin(object_index, &origin);
		render_debug_sphere(true, &origin, radius, global_real_argb_purple);
	}

	if (debug_objects_root_node)
	{
		REFERENCE_DECLARE(object + 0x2C, real, bounding_sphere_radius);

		real_matrix4x3* root_node_matrix = object_get_node_matrix(object_index, 0);
		render_debug_matrix(true, root_node_matrix, bounding_sphere_radius);
	}

	if (debug_objects_bounding_spheres)
	{
		long parent_object_index = object_get_ultimate_parent(object_index);
		object_header_datum const* parent_object_header = object_header_get(parent_object_index);
		byte* parent_object = static_cast<byte*>(object_get_and_verify_type(parent_object_index, NONE));

		REFERENCE_DECLARE(object + 0x20, real_point3d, bounding_sphere_center);
		REFERENCE_DECLARE(object + 0x2C, real, bounding_sphere_radius);

		render_debug_sphere(true, &bounding_sphere_center, bounding_sphere_radius > 0.0f ? bounding_sphere_radius : 0.25f, global_real_argb_blue);

		if (debug_objects_attached_bounding_spheres)
		{
			REFERENCE_DECLARE(object + 0x30, real_point3d, attached_bounds_center);
			REFERENCE_DECLARE(object + 0x3C, real, attached_bounds_radius);

			render_debug_point(true, &attached_bounds_center, 0.1f, global_real_argb_blue);
			render_debug_sphere(true, &attached_bounds_center, attached_bounds_radius, global_real_argb_blue);
		}
	}

	if (debug_objects_dynamic_render_bounding_spheres)
	{

	}

	s_model_definition* model_definition = nullptr;
	if (object_definition->model.index != NONE)
		model_definition = object_definition->model.cast_to<s_model_definition>();

	if (debug_objects_model_targets && model_definition)
	{
		for (s_model_target& target : model_definition->targets)
		{
			object_marker markers[2]{};
			short marker_count = object_get_markers_by_string_id(object_index, target.marker_name.get_value(), markers, NUMBEROF(markers));
			switch (marker_count)
			{
			case 1:
			{
				render_debug_vector(true, &markers[0].node_matrix.center, &markers[0].node_matrix.matrix.forward, target.size, global_real_argb_darkgreen);

				if (target.cone_angle <= 3.1414928f)
					render_debug_cone_outline(true, &markers[0].node_matrix.center, &markers[0].node_matrix.matrix.forward, target.size, target.cone_angle, global_real_argb_darkgreen);
				else
					render_debug_sphere(true, &markers[0].node_matrix.center, target.size, global_real_argb_darkgreen);
			}
			break;
			case 2:
			{
				vector3d height{};
				vector_from_points3d(&markers[0].node_matrix.center, &markers[1].node_matrix.center, &height);
				render_debug_pill(true, &markers[0].node_matrix.center, &height, target.size, global_real_argb_darkgreen);
			}
			break;
			}
		}
	}

	//collision_model_instance instance{};
	//if (debug_objects_collision_models && collision_model_instance_new(&instance, object_index))
	//{
	//
	//}

	if (debug_objects_early_movers && object_definition->flags.test(_object_definition_flag_early_mover_bit))
	{
		char const* early_mover_string = "early mover";
		if (object_definition->flags.test(_object_definition_flag_early_mover_localized_physics_bit))
			early_mover_string = "early mover + localized physics";

		real_matrix4x3* root_node_matrix = object_get_node_matrix(object_index, 0);
		render_debug_string_at_point(&root_node_matrix->center, early_mover_string, global_real_argb_darkgreen);
	}

	//real object_cpu_times[2];
	//if (debug_objects_profile_times && object_profile_query_object_instance_cpu_times(object_index, &object_cpu_times))
	//{
	//
	//}

	REFERENCE_DECLARE(object + 0xA0, long, havok_component_index);
	if (havok_component_index == NONE)
	{

	}
	else
	{
		//debug_objects_water_physics
		//debug_objects_physics_models
		//debug_objects_contact_points
		//debug_objects_constraints
		//debug_objects_vehicle_physics
		//debug_objects_mass
	}

	if (debug_objects_pathfinding)
	{

	}

	if (!string.is_empty())
	{
		real_matrix4x3* root_node_matrix = object_get_node_matrix(object_index, 0);
		render_debug_string_at_point(&root_node_matrix->center, string.get_string(), global_real_argb_green);
	}

	if (debug_objects_node_bounds)
	{

	}

	if (debug_objects_animation)
	{

	}
}

