#pragma once

#include "cseries/cseries.hpp"
#include "shell/shell.hpp"

struct s_network_message_connect_request
{
	dword channel_identifier;
	dword_flags flags;
};
static_assert(sizeof(s_network_message_connect_request) == 0x8);

struct s_network_message_connect_refuse
{
	dword remote_identifier;
	long reason;
};
static_assert(sizeof(s_network_message_connect_refuse) == 0x8);

struct s_network_message_connect_establish
{
	dword identifier;
	dword remote_identifier;
};
static_assert(sizeof(s_network_message_connect_establish) == 0x8);

struct s_network_message_connect_closed
{
	dword remote_identifier;
	dword identifier;
	c_enum<e_network_channel_closure_reason, long, _network_channel_reason_none, k_network_channel_reason_count> reason;
};
static_assert(sizeof(s_network_message_connect_closed) == 0xC);

struct c_bitstream;

class c_network_message_connect_request
{
public:
	static void __cdecl encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, long message_storage_size, void* message_storage);
};

class c_network_message_connect_refuse
{
public:
	static void __cdecl encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, long message_storage_size, void* message_storage);
};

class c_network_message_connect_establish
{
public:
	static void __cdecl encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, long message_storage_size, void* message_storage);
};

class c_network_message_connect_closed
{
public:
	static void __cdecl encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool __cdecl decode(c_bitstream* packet, long message_storage_size, void* message_storage);
};

struct c_network_message_type_collection;
extern void __cdecl network_message_types_register_connect(c_network_message_type_collection* message_collection);

