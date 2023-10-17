#pragma once

#include "cseries/cseries.hpp"

struct s_persisted_usability_globals
{
	s_persisted_usability_globals();

	bool display_mission_segment;
	c_static_string<256> mission_segment_buffer;
	c_static_string<256> user_experience_buffer;
};
static_assert(sizeof(s_persisted_usability_globals) == 0x201);

extern void data_mine_render_mission_segment();

