#pragma once

#include "tag_files/tag_groups.hpp"

struct real_block
{
	real32 value;
};
static_assert(sizeof(real_block) == sizeof(real32));

struct function_definition_data
{
	int8 function_type;
	uns8 flags;
	int8 function[2];
	rgb_color color[4];
	c_typed_tag_block<real_block> values;
};
static_assert(sizeof(function_definition_data) == 0x20);

struct mapping_function
{
	c_typed_tag_data<function_definition_data> data;
};
static_assert(sizeof(mapping_function) == sizeof(s_tag_data));

class c_function_definition :
	public mapping_function
{
};
static_assert(sizeof(c_function_definition) == sizeof(mapping_function));

