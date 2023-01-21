#pragma once

const long k_number_of_global_shaders = 10;

struct IDirect3DPixelShader9;
struct IDirect3DVertexShader9;
struct s_rasterizer_global_shader_globals
{
	IDirect3DPixelShader9* pixel_shaders[k_number_of_global_shaders];
	IDirect3DVertexShader9* vertex_shaders[k_number_of_global_shaders];
	bool initialized;
};
static_assert(sizeof(s_rasterizer_global_shader_globals) == 0x54);

extern s_rasterizer_global_shader_globals& g_rasterizer_global_shader_globals;

