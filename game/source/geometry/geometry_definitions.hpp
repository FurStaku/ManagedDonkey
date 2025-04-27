#pragma once

#include "cache/cache_files.hpp"
#include "cseries/cseries.hpp"
#include "tag_files/tag_groups.hpp"

struct s_mesh
{
	s_tag_block parts;
	s_tag_block subparts;
	uint16 vertex_buffer_indices[8];
	int16 index_buffer_index;
	int16 index_buffer_tessellation;
	uint8 mesh_flags;
	char rigid_node_index;
	char vertex_type;
	char prt_vertex_type;
	char index_buffer_type;
	uint8 BAASDFIR[3];
	s_tag_block instance_bucket;
	s_tag_block water_indices_start;
};
static_assert(sizeof(s_mesh) == 0x4C);

struct s_compression_info
{
	uint16 compression_flags;
	uint8 JOJOBOMO[2];

	// WARNING

	// The following fields are mislabeled for legacy reasons.The actual order is:
	// position_bounds.x0 position_bounds.x1 position_bounds.y0
	// position_bounds.y1 position_bounds.z0 position_bounds.z1
	// 
	// texcoord_bounds.x0 texcoord_bounds.x1
	// texcoord_bounds.y0 texcoord_bounds.y1
	// 
	real_point3d position_bounds[2];
	real_point3d texcoord_bounds[2];
};
static_assert(sizeof(s_compression_info) == 0x34);

struct s_positioning
{
	real_plane3d plane;
	real_point3d position;
	real32 radius;
	char node_indices[4];
	real32 node_weights[4];
};
static_assert(sizeof(s_positioning) == 0x34);

struct s_render_geometry_user_data_header
{
	char data_type;
	char data_count;
	int16 data_size;
};
static_assert(sizeof(s_render_geometry_user_data_header) == 0x4);

struct s_render_geometry_user_data
{
	s_render_geometry_user_data_header user_data_header;
	s_tag_data user_data;
};
static_assert(sizeof(s_render_geometry_user_data) == 0x18);

struct s_per_mesh_raw_data
{
	s_tag_block raw_vertices;
	s_tag_block raw_indices;
	s_tag_block raw_water_data;
	int16 parameterized_texture_width;
	int16 parameterized_texture_height;
	uint32 flags;
};
static_assert(sizeof(s_per_mesh_raw_data) == 0x2C);

struct s_per_mesh_mopp
{
	s_tag_data mopp_code;
	s_tag_block mopp_reorder_table;
};
static_assert(sizeof(s_per_mesh_mopp) == 0x20);

struct s_per_mesh_node_map
{
	s_tag_block node_map;
};
static_assert(sizeof(s_per_mesh_node_map) == 0xC);

struct s_per_mesh_subpart_visibility
{
	s_tag_block bounding_sphere;
};
static_assert(sizeof(s_per_mesh_subpart_visibility) == 0xC);

struct s_per_mesh_prt_data
{
	s_tag_data mesh_pca_data;
	s_tag_block per_instance_prt_data;
};
static_assert(sizeof(s_per_mesh_prt_data) == 0x20);

struct s_per_instance_lightmap_texcoords
{
	s_tag_block texture_coordinates;
	int16 vertex_buffer_index;
	uint8 HTJIAHA[2];
};
static_assert(sizeof(s_per_instance_lightmap_texcoords) == 0x10);

struct s_render_geometry_api_resource
{
	s_tag_block pc_vertex_buffers;
	s_tag_block pc_index_buffers;
	s_tag_block xenon_vertex_buffers;
	s_tag_block xenon_index_buffers;
};
static_assert(sizeof(s_render_geometry_api_resource) == 0x30);

struct s_render_geometry
{
	uint32 runtime_flags;
	c_typed_tag_block<s_mesh> meshes;
	c_typed_tag_block<s_compression_info> compression_info;
	c_typed_tag_block<s_positioning> part_sorting_position;
	c_typed_tag_block<s_render_geometry_user_data> user_data;
	c_typed_tag_block<s_per_mesh_raw_data> per_mesh_temporary;
	c_typed_tag_block<s_per_mesh_mopp> per_mesh_mopp;
	c_typed_tag_block<s_per_mesh_node_map> per_mesh_node_map;
	c_typed_tag_block<s_per_mesh_subpart_visibility> per_mesh_subpart_visibility;
	c_typed_tag_block<s_per_mesh_prt_data> per_mesh_prt_data;
	c_typed_tag_block<s_per_instance_lightmap_texcoords> per_instance_lightmap_texcoords;
	c_typed_tag_resource<s_render_geometry_api_resource> api_resource;
};
static_assert(sizeof(s_render_geometry) == 0x84);

//extern bool mesh_has_subpart_mopp(s_render_geometry const* render_geometry, int32 mesh_index);
extern bool mesh_has_subpart_mopp(s_render_geometry* render_geometry, int32 mesh_index);

