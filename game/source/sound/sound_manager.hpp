#pragma once

#include "cseries/cseries.hpp"

#define MAXIMUM_SOUND_SOURCES 196
#define NUMBER_OF_SOUND_SAMPLE_RATES 3

tag const k_sound_listener_header_signature = 'lshd';
tag const k_sound_listener_footer_signature = 'lsft';
long const k_number_of_sound_manager_listeners = 4;

struct s_sound_listener
{
	tag header_signature;
	s_location location;
	bool valid;
	bool __unknown9;
	byte __unknownA;
	byte __unknownB;
	real_matrix4x3 matrix;
	vector3d vector;
	tag footer_signature;
};
static_assert(sizeof(s_sound_listener) == 0x50);

struct s_sound_manager_reverb
{
	real __unknown0;
	real __unknown4;
	long __unknown8;
	real __unknownC;
	real __unknown10;
	real __unknown14;
	real __unknown18;
};
static_assert(sizeof(s_sound_manager_reverb) == 0x1C);

struct s_platform_sound_status
{
	byte __data0[0x60];
};
static_assert(sizeof(s_platform_sound_status) == 0x60);

struct s_sound_manager_globals
{
	s_platform_sound_status sound_status;

	c_static_flags<MAXIMUM_SOUND_SOURCES> used_sources;
	c_static_flags<MAXIMUM_SOUND_SOURCES> available_sources;

	bool fully_initialized;
	bool __unknown99;
	bool game_active;

	byte pause_state;
	bool idling;
	bool recursion_lock;

	byte __unknown9E;
	byte __unknown9F;
	byte __unknownA0;

	dword system_time;
	dword render_time;

	c_static_array<s_sound_listener, k_number_of_sound_manager_listeners> listeners;

	byte __data1EC[0x40];
	byte __data22C[0x4];

	c_static_array<s_sound_manager_reverb, 2> manager_reverbs;

	long __unknown268;

	real delta_time;

	long __unknown27C;
	real __unknown270;
	real __unknown274;
	real __unknown278;
	long __unknown28C;
	real __unknown280;
	real __unknown284;
	long __unknown288;
	long __unknown29C;
	real __unknown290;
	real __unknown294;
	real __unknown298;

	struct
	{
		long active_ducker;
		real active_ducker_time;
		long last_ducker;
		real inactive_time;
	} ducker;

	short channel_count;
	short __unknown2B2;
	real __unknown2B4;
};
static_assert(sizeof(s_sound_manager_globals) == 0x2B8);

extern bool debug_sound_class_totals;
extern bool debug_sound_timing;
extern bool debug_duckers;
extern bool debug_sound_listeners;
extern bool debug_sound;
extern bool debug_sound_manager_channels;

extern s_sound_listener const* __cdecl sound_manager_get_listener(long listener_index);

extern void __cdecl sound_debug_render();

