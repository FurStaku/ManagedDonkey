#include "objects/object_scripting.hpp"

//.text:00B95750 ; 
//.text:00B95770 ; 
//.text:00B95780 ; void __cdecl __tls_set_g_object_scripting_state_allocator(void*)
//.text:00B957A0 ; 
//.text:00B957E0 ; 
//.text:00B95810 ; 
//.text:00B95840 ; long __cdecl object_at_marker(long, long)
//.text:00B95920 ; void __cdecl object_scripting_clear_all_cinematic_function_variables(long)
//.text:00B95990 ; void __cdecl object_scripting_clear_cinematic_function_variable(long, long)

void __cdecl object_scripting_dispose()
{
	INVOKE(0x00B959F0, object_scripting_dispose);
}

void __cdecl object_scripting_dispose_from_old_map()
{
	INVOKE(0x00B95A10, object_scripting_dispose_from_old_map);
}

//.text:00B95A30 ; void __cdecl object_scripting_dynamic_simulation_disable(long, bool)
//.text:00B95AA0 ; bool __cdecl object_scripting_get_cinematic_function_variable(long, long, real*)
//.text:00B95B00 ; bool __cdecl object_scripting_get_cinematic_function_variable(long, long, real*, long*)
//.text:00B95BF0 ; double __cdecl object_scripting_get_health(long) // real __cdecl object_scripting_get_health(long)
//.text:00B95C40 ; long __cdecl object_scripting_get_parent(long)
//.text:00B95C80 ; double __cdecl object_scripting_get_shield(long) // real __cdecl object_scripting_get_shield(long)

void __cdecl object_scripting_initialize()
{
	INVOKE(0x00B95CD0, object_scripting_initialize);
}

void __cdecl object_scripting_initialize_for_new_map()
{
	INVOKE(0x00B95D30, object_scripting_initialize_for_new_map);
}

//.text:00B95DA0 ; 
//.text:00B95DF0 ; 
//.text:00B95E10 ; function sets `object->object.brittle_collision_damage_timer`
//.text:00B95E90 ; void __cdecl object_scripting_set_deleted_when_deactivated(long)
//.text:00B95ED0 ; void __cdecl object_scripting_set_function_variable(long, long, real, real)
//.text:00B96030 ; function sets `object->object.environment_interpenetration_ticks`
//.text:00B960D0 ; void __cdecl object_scripting_set_phantom_power(long, bool)
//.text:00B96120 ; void __cdecl object_scripting_set_physics(long, bool)
//.text:00B96170 ; void __cdecl object_scripting_set_shield_effect(long, real, real)
//.text:00B96270 ; void __cdecl object_scripting_set_velocity2(long, real, real, real)
//.text:00B963A0 ; void __cdecl object_scripting_set_velocity(long, real)
//.text:00B964C0 ; void __cdecl object_scripting_wake_physics(long)
//.text:00B964E0 ; void __cdecl objects_scripting_attach(long, long, long, long)
//.text:00B96570 ; void __cdecl objects_scripting_detach(long, long)
//.text:00B965C0 ; void __cdecl objects_scripting_set_scale(long, real, short)
//.text:00B96670 ; 

