#pragma once

#include "simulation/simulation.hpp"

struct s_network_message_synchronous_update
{
	struct simulation_update update;
	s_simulation_update_metadata metadata;
};
static_assert(sizeof(s_network_message_synchronous_update) == 0x1668);
static_assert(0x0000 == OFFSETOF(s_network_message_synchronous_update, update));
static_assert(0x1658 == OFFSETOF(s_network_message_synchronous_update, metadata));

struct s_network_message_synchronous_playback_control
{
	e_network_synchronous_playback_control type;
	int32 identifier;
	int32 update_number;
};
static_assert(sizeof(s_network_message_synchronous_playback_control) == 0xC);

struct s_network_message_synchronous_actions
{
	int32 action_number;
	int32 current_update_number;
	uint32 valid_user_mask;
	player_action user_actions[4];
};
static_assert(sizeof(s_network_message_synchronous_actions) == 0x210);

struct s_network_message_synchronous_acknowledge
{
	int32 current_update_number;
};
static_assert(sizeof(s_network_message_synchronous_acknowledge) == 0x4);

struct c_bitstream;

class c_network_message_synchronous_update
{
public:
	static void __cdecl encode(c_bitstream* packet, int32 message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, int32 message_storage_size, void* message_storage);
	static bool __cdecl compare(int32, void*, void*);
	static void __cdecl dispose(int32, void*);
};

class c_network_message_synchronous_playback_control
{
public:
	static void __cdecl encode(c_bitstream* packet, int32 message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, int32 message_storage_size, void* message_storage);
};

class c_network_message_synchronous_actions
{
public:
	static void __cdecl encode(c_bitstream* packet, int32 message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, int32 message_storage_size, void* message_storage);
	static bool __cdecl compare(int32, void*, void*);
	static void __cdecl dispose(int32, void*);
};

class c_network_message_synchronous_acknowledge
{
public:
	static void __cdecl encode(c_bitstream* packet, int32 message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, int32 message_storage_size, void* message_storage);
};

class c_network_message_synchronous_gamestate
{
public:
	static void __cdecl encode(c_bitstream* packet, int32 message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, int32 message_storage_size, void* message_storage);
};

struct c_network_message_type_collection;
extern void __cdecl network_message_types_register_simulation_synchronous(c_network_message_type_collection* message_collection);

