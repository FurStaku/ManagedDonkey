#pragma once

#include "cseries/cseries.hpp"
#include "memory/data.hpp"

struct c_light_volume_location : s_datum_header
{
	byte __data[0x2A];
};
static_assert(sizeof(c_light_volume_location) == 0x2C);

struct c_light_volume : s_datum_header
{
	byte __data[0x32];
};
static_assert(sizeof(c_light_volume) == 0x34);

struct c_light_volume_system : s_datum_header
{
	byte __data[0x2A];
};
static_assert(sizeof(c_light_volume_system) == 0x2C);

