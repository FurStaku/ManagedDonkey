#pragma once

#include "cseries/cseries.hpp"
#include "simulation/simulation.hpp"

struct s_network_message_synchronous_update
{
	struct simulation_update update;
	s_simulation_update_metadata metadata;
	byte __data[0x4];
};
static_assert(sizeof(s_network_message_synchronous_update) == 0x1668);

struct s_network_message_synchronous_playback_control
{
	long type;
	dword identifier;
	long update_number;
};
static_assert(sizeof(s_network_message_synchronous_playback_control) == 0xC);

struct s_network_message_synchronous_actions
{
	long action_number;
	long current_action_number;
	dword_flags user_flags;
	long : 32;
	c_static_array<player_action, 4> actions;
};
static_assert(sizeof(s_network_message_synchronous_actions) == 0x210);

struct s_network_message_synchronous_acknowledge
{
	long current_update_number;
};
static_assert(sizeof(s_network_message_synchronous_acknowledge) == 0x4);

struct s_network_message_synchronous_gamestate
{
	byte message_type;
	dword chunk_offset_next_update_compressed_checksum;
	dword chunk_size;
	dword decompressed_checksum;
#pragma warning(push)
#pragma warning(disable : 4200)
	byte additional_data[];
#pragma warning(pop)
};
static_assert(sizeof(s_network_message_synchronous_gamestate) == 0x10);

struct c_bitstream;

class c_network_message_synchronous_update
{
public:
	static void __cdecl encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, long message_storage_size, void* message_storage);
	static bool __cdecl compare(long, void*, void*);
	static void __cdecl dispose(long, void*);
};

class c_network_message_synchronous_playback_control
{
public:
	static void __cdecl encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, long message_storage_size, void* message_storage);
};

class c_network_message_synchronous_actions
{
public:
	static void __cdecl encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, long message_storage_size, void* message_storage);
	static bool __cdecl compare(long, void*, void*);
	static void __cdecl dispose(long, void*);
};

class c_network_message_synchronous_acknowledge
{
public:
	static void __cdecl encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, long message_storage_size, void* message_storage);
};

class c_network_message_synchronous_gamestate
{
public:
	static void __cdecl encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, long message_storage_size, void* message_storage);
};

struct c_network_message_type_collection;
extern void __cdecl network_message_types_register_simulation_synchronous(c_network_message_type_collection* message_collection);

