#pragma once

#include "cseries/cseries.hpp"

struct s_scenario_editor_folder
{
	long parent_folder; // long_block_index

	c_static_string<k_tag_long_string_length> name;
};
static_assert(sizeof(s_scenario_editor_folder) == 0x104);

