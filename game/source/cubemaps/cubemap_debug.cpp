#include "cubemaps/cubemap_debug.hpp"

#include "cseries/cseries.hpp"
#include "game/player_mapping.hpp"
#include "objects/objects.hpp"
#include "render/render_debug.hpp"
#include "render/render_objects_static_lighting.hpp"
#include "scenario/scenario_cubemap_definitions.hpp"

bool c_cubemap_debug::g_render = false;

void c_cubemap_debug::render()
{
    if (g_render)
        render_user_cubemap_samples(0);
}

void c_cubemap_debug::render_user_cubemap_samples(long user_index)
{
    if (!g_render || user_index == NONE)
        return;

    long object_index = player_mapping_get_unit_by_output_user(user_index);
    render_object_cubemap_samples(object_index);
}

void __cdecl c_cubemap_debug::render_object_cubemap_samples(long object_index)
{
    if (!g_render || object_index == NONE)
        return;

    render_lighting const* object_lighting = object_get_cached_render_lighting(object_index);
    if (!object_lighting)
        return;

    s_structure_cluster_cubemap_info* cubemap_info0 = structure_cluster_try_and_get_cubemap_info(object_lighting->cubemap_sample.__unknown0[0].cluster_reference, object_lighting->cubemap_sample.__unknown0[0].cluster_cubemap_index);
    s_structure_cluster_cubemap_info* cubemap_info1 = structure_cluster_try_and_get_cubemap_info(object_lighting->cubemap_sample.__unknown0[1].cluster_reference, object_lighting->cubemap_sample.__unknown0[1].cluster_cubemap_index);

    real_argb_color color = { 1.0f, { 1.0f, 1.0f, 0.2f } };
    if (cubemap_info0)
        render_debug_sphere(true /* false */, &cubemap_info0->cubemap_position, 10.0f, &color);

    if (cubemap_info1)
    {
        color.color.green = 0.0f;
        render_debug_sphere(true /* false */, &cubemap_info1->cubemap_position, 10.0f, &color);
    }

    if (byte* object = static_cast<byte*>(object_get_and_verify_type(object_index, NONE)))
    {
        color.color.green = object_lighting->cubemap_sample.m_cubemap_sample;

        REFERENCE_DECLARE(object + 0x20, real_point3d, bounding_sphere_center);

        if (cubemap_info0 && color.color.green > 0.0)
            render_debug_line(true /* false */, &cubemap_info0->cubemap_position, &bounding_sphere_center, &color);

        if (cubemap_info1 && color.color.green < 1.0)
            render_debug_line(true /* false */, &bounding_sphere_center, &cubemap_info1->cubemap_position, &color);
    }
}

