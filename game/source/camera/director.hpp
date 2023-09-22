#pragma once

#include "cseries/cseries.hpp"
#include "camera/camera.hpp"
#include "camera/dead_camera.hpp"
#include "camera/first_person_camera.hpp"
#include "camera/flying_camera.hpp"
#include "camera/following_camera.hpp"
#include "camera/observer.hpp"
#include "camera/orbiting_camera.hpp"
#include "camera/static_camera.hpp"
#include "memory/data.hpp"

enum e_director_mode : long
{
	_director_mode_game = 0,
	_director_mode_saved_film,
	_director_mode_observer,
	_director_mode_debug,
	_director_mode_unused,
	_director_mode_editor,

	k_number_of_director_modes
};

extern const char* director_mode_get_name(e_director_mode director_mode);
extern e_director_mode director_mode_from_string(const char* str);

enum e_director_perspective : long
{
	_director_perspective_first_person = 0,
	_director_perspective_third_person,
	_director_perspective_scripted,

	// c_null_camera, (c_authored_camera default)
	_director_perspective_3,

	k_number_of_director_perspectives,
};

struct c_director
{
	virtual e_director_mode get_type();
	virtual void update(real);
	virtual bool should_draw_hud();
	virtual bool should_draw_hud_saved_film();
	virtual bool inhibits_facing();
	virtual bool inhibits_input();
	virtual void handle_deleted_player(long);
	virtual void handle_deleted_object(long);
	virtual bool can_use_camera_mode(e_camera_mode);
	//virtual void select_fallback_target(); // c_observer_director, c_saved_film_director

	byte m_camera[0x4C];

	s_observer_command m_observer_command;
	real m_transition_time;
	long m_user_index;
	long m_output_user_index;
	bool __unknown148;

	byte pad[3];

	e_director_perspective get_perspective();
	bool set_camera_mode_internal(e_camera_mode camera_mode, real transition_time, bool force_update);

	bool set_camera_mode(e_camera_mode camera_mode, real transition_time)
	{
		return set_camera_mode_internal(camera_mode, transition_time, false);
	}

	template<typename t_type = c_camera>
	t_type* get_camera()
	{
		if (!m_camera[0])
			return nullptr;

		return (t_type*)&m_camera;
	}

	bool in_free_camera_mode()
	{
		if (!m_camera[0])
			return false;

		e_camera_mode camera_mode = get_camera()->get_type();
		if (camera_mode == _camera_mode_flying || camera_mode == _camera_mode_scripted)
			return true;

		if (camera_mode == _camera_mode_authored)
			return get_camera()->get_target() == -1;

		return false;
	}
};
static_assert(sizeof(c_director) == 0x14C);

struct s_director_info
{
	e_director_mode director_mode;
	e_director_perspective director_perspective;
	e_camera_mode camera_mode;
};
static_assert(sizeof(s_director_info) == 0xC);

struct s_director_globals
{
	// c_static_array<byte[0x160], 4> directors;
	byte directors[4][0x160];

	s_director_info infos[4];
	real timestep;
	real fade_timer5B4; // in?
	real fade_timer5B8; // out?
	bool debug_force_scripted_camera_disable;
};
static_assert(sizeof(s_director_globals) == 0x5C0);

struct s_observer_gamestate_globals
{
	dword __unknown0;
	dword __unknown4;
	dword __unknown8;
};
static_assert(sizeof(s_observer_gamestate_globals) == 0xC);

template<typename t_type = c_director>
extern t_type* director_get(long user_index);

extern s_director_info* director_get_info(long user_index);
extern e_director_perspective director_get_perspective(long user_index);
extern void director_set_perspective(long user_index, e_director_perspective director_perspective);
extern void director_set_mode(long user_index, e_director_mode director_mode);
extern bool director_get_camera_third_person(long user_index);
extern bool director_in_scripted_camera();
extern void director_toggle(long user_index, e_director_mode director_mode);
extern void director_toggle_perspective(long user_index, e_director_perspective director_perspective);
extern void director_toggle_camera(long user_index, e_camera_mode camera_mode);
extern void __cdecl director_render();

extern void __cdecl director_set_flying_camera_direct(long user_index, real_point3d const* position, vector3d const* forward, vector3d const* up);
extern char const* const k_camera_save_filename;
extern void __cdecl director_save_camera_named(char const* name);
extern void __cdecl director_load_camera_named(char const* name);
extern void __cdecl director_save_camera();
extern void __cdecl director_load_camera();
extern void __cdecl director_debug_camera(bool render);
extern void __cdecl director_script_camera(bool scripted);
extern void __cdecl director_set_camera_mode(long user_index, e_camera_mode camera_mode);

