#pragma once

#include "cseries/cseries.hpp"

struct collision_bsp;
struct large_collision_bsp;
plane3d* bsp3d_get_plane_from_designator_internal(collision_bsp const* bsp, short index, plane3d* out_plane);
plane3d* bsp3d_get_plane_from_designator_internal(large_collision_bsp const* bsp, long index, plane3d* out_plane);

