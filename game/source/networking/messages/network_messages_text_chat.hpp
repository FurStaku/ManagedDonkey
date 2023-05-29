#pragma once

#include "networking/transport/transport_security.hpp"
#include "text/unicode.hpp"

struct s_network_message_text_chat_payload
{
	// _text_chat_metadata_broadcast = 1
	long metadata;

	bool source_is_server;
	s_transport_secure_address source_player;

	c_static_array<s_transport_secure_address, 16> destination_players;
	long destination_player_count;

	union
	{
		wchar_t text_buffer[122];
		c_static_wchar_string<122> text;
	};
};
static_assert(sizeof(s_network_message_text_chat_payload) == 0x210 /* 0x188 */);

struct s_network_message_text_chat
{
	s_transport_secure_identifier session_id;
	long routed_players;
	s_network_message_text_chat_payload payload;
};
static_assert(sizeof(s_network_message_text_chat) == 0x224 /* 0x194 */);

struct c_bitstream;
class c_network_message_text_chat
{
public:
	static void encode(c_bitstream* packet, long message_storage_size, void const* message_storage);
	static bool decode(c_bitstream* packet, long message_storage_size, void* message_storage);
};

struct c_network_message_type_collection;
extern void __cdecl network_message_types_register_text_chat(c_network_message_type_collection* message_collection);

