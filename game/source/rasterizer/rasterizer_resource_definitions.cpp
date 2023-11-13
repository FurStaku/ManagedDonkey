#include "rasterizer/rasterizer_resource_definitions.hpp"

#include "cseries/cseries.hpp"
#include "rasterizer/rasterizer_shader_definitions.hpp"
#include "rasterizer/rasterizer.hpp"

REFERENCE_DECLARE_2D_ARRAY(0x016954F8, D3DVERTEXELEMENT9, c_vertex_declaration_table::lighting_vertex_decls, k_number_of_lighting_vertex_types, 64);
REFERENCE_DECLARE_2D_ARRAY(0x01695CF8, D3DVERTEXELEMENT9, c_vertex_declaration_table::transfer_vertex_decls, k_number_of_transfer_vertex_types, 64);
REFERENCE_DECLARE_2D_ARRAY(0x016964F8, D3DVERTEXELEMENT9, c_vertex_declaration_table::other_vertex_decls, 4, 64);
REFERENCE_DECLARE_2D_ARRAY(0x01918738, D3DVERTEXELEMENT9, c_vertex_declaration_table::base_vertex_decls, k_number_of_vertex_types, 64);
REFERENCE_DECLARE_3D_ARRAY(0x05215C40, IDirect3DVertexDeclaration9*, c_vertex_declaration_table::m_vertex_declarations, k_number_of_vertex_types, k_number_of_lighting_vertex_types, k_number_of_transfer_vertex_types);

IDirect3DVertexDeclaration9* c_vertex_declaration_table::get_d3d_vertex_declaration(e_vertex_type base_vertex_type, e_lighting_vertex_types lighting_vertex_type, e_transfer_vector_vertex_types transfer_vertex_type)
{
    //return INVOKE(0x00A72130, get_d3d_vertex_declaration, base_vertex_type, lighting_vertex_type, transfer_vertex_type);

    ASSERT(base_vertex_type >= _vertex_type_world && base_vertex_type < k_number_of_vertex_types);
    ASSERT(lighting_vertex_type >= _lighting_vertex_type_unknown0 && lighting_vertex_type < k_number_of_lighting_vertex_types);
    ASSERT(transfer_vertex_type >= _transfer_vector_vertex_type_unknown0 && transfer_vertex_type < k_number_of_transfer_vertex_types);

    return m_vertex_declarations[base_vertex_type][lighting_vertex_type][transfer_vertex_type];
}

IDirect3DVertexDeclaration9* c_vertex_declaration_table::get_d3d_vertex_declaration_by_entry_point(e_vertex_type base_vertex_type, e_transfer_vector_vertex_types transfer_vertex_type, long entry_point)
{
    //return INVOKE(0x00A72150, get_d3d_vertex_declaration_by_entry_point, base_vertex_type, transfer_vertex_type, entry_point);

    switch (entry_point)
    {
    case _entry_point_static_per_pixel:
    case _entry_point_lightmap_debug_mode:
    {
        return get_d3d_vertex_declaration(base_vertex_type, _lighting_vertex_type_unknown2, _transfer_vector_vertex_type_unknown0);
    }
    case _entry_point_static_per_vertex:
    {
        return get_d3d_vertex_declaration(base_vertex_type, _lighting_vertex_type_unknown3, _transfer_vector_vertex_type_unknown0);
    }
    case _entry_point_static_prt_ambient:
    case _entry_point_static_prt_linear:
    case _entry_point_static_prt_quadratic:
    case _entry_point_active_camo:
    {
        return get_d3d_vertex_declaration(base_vertex_type, _lighting_vertex_type_unknown0, transfer_vertex_type);
    }
    case _entry_point_vertex_color_lighting:
    {
        return get_d3d_vertex_declaration(base_vertex_type, _lighting_vertex_type_unknown1, _transfer_vector_vertex_type_unknown0);
    }
    }

    return get_d3d_vertex_declaration(base_vertex_type, _lighting_vertex_type_unknown0, _transfer_vector_vertex_type_unknown0);
}

bool __cdecl c_vertex_declaration_table::set(e_vertex_type base_vertex_type, e_transfer_vector_vertex_types transfer_vertex_type, long entry_point)
{
    return INVOKE(0x00A729B0, set, base_vertex_type, transfer_vertex_type, entry_point);

    //return c_rasterizer::set_vertex_declaration(get_d3d_vertex_declaration_by_entry_point(base_vertex_type, transfer_vertex_type, entry_point));
}

