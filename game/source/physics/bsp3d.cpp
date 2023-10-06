#include "physics/bsp3d.hpp"

#include "structures/structure_bsp_definitions.hpp"

#include <climits>

plane3d* bsp3d_get_plane_from_designator_internal(collision_bsp const* bsp, short index, plane3d* out_plane)
{
	plane3d* plane = &bsp->planes[index & SHRT_MAX];
	if ((index & 0x8000) != 0)
	{
		out_plane->normal.i = -plane->normal.i;
		out_plane->normal.j = -plane->normal.j;
		out_plane->normal.k = -plane->normal.k;
		out_plane->distance = -plane->distance;
	}
	else
	{
		*out_plane = *plane;
	}

	return out_plane;
}

plane3d* bsp3d_get_plane_from_designator_internal(large_collision_bsp const* bsp, long index, plane3d* out_plane)
{
	plane3d* plane = &bsp->planes[index & LONG_MAX];
	if (index >= 0)
	{
		*out_plane = *plane;
	}
	else
	{
		out_plane->normal.i = -plane->normal.i;
		out_plane->normal.j = -plane->normal.j;
		out_plane->normal.k = -plane->normal.k;
		out_plane->distance = -plane->distance;
	}

	return out_plane;
}

