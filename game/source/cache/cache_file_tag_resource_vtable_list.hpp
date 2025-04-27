#pragma once

#include "cseries/cseries.hpp"

struct s_tag_persistent_identifier
{
	uint32 data[4];
};
static_assert(sizeof(s_tag_persistent_identifier) == 0x10);

struct s_cache_file_tag_resource_vtable
{
	s_tag_persistent_identifier resource_identifier;
	bool(__cdecl* on_load_from_cache_file)(long, void*);
	void(__cdecl* on_dispose_from_cache)(long, void*);
};
static_assert(sizeof(s_cache_file_tag_resource_vtable) == 0x18);

