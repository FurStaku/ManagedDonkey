#include "physics/collision_usage.hpp"

bool collision_log_render_enable = false;
bool collision_log_detailed = false;
bool collision_log_extended = false;
bool collision_log_totals_only = false;
bool collision_log_time = false;
bool global_collision_log_enable = false;
bool global_collision_log_switch_pending = false;
bool global_collision_log_switch_pending_value = false;
short global_current_collision_user_depth = 0;
short global_collision_period_depth = 0;

void collision_log_render()
{
	if (collision_log_render_enable)
	{
		// #TODO: implement
	}
}

