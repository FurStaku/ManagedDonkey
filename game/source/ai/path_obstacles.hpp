#pragma once

#include "ai/sector.hpp"
#include "cseries/cseries.hpp"

#define MAXIMUM_DISC_COUNT 256

struct disc
{
	int16 flags;
	int16 obstacle_index;
	int32 object_index;
	real_point2d center;
	real32 radius;

	// debug only?
	//real32 z;
};
static_assert(sizeof(struct disc) == 0x14);

struct obstacles
{
	int16 obstacle_count;
	int16 disc_count;
	int16 disc_optional_count;
	int16 high_threshold_disc_count;
	int16 medium_threshold_disc_count;
	disc discs[MAXIMUM_DISC_COUNT];
};
static_assert(sizeof(struct obstacles) == 0x140C);

extern struct disc const* __cdecl obstacles_get_disc(struct obstacles const* obstacles, int16 disc_index);
extern void __cdecl obstacles_new(struct obstacles* obstacles);

extern void render_debug_obstacles(struct obstacles const* obstacles, real32 radius);

