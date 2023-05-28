#pragma once

#include "cseries/cseries.hpp"

struct s_player_identifier;
struct transport_address
{
	transport_address();
	transport_address(dword _ipv4_address, word _port, short _address_length);
	transport_address(s_player_identifier const* player_identifier);

	union
	{
		dword ipv4_address;

		// in_addr
		// address_length == 0x4
		union
		{
			byte bytes[4];
			word words[2];
		} ina;

		// in6_addr
		// address_length == 0x10
		union
		{
			byte bytes[16];
			word words[8];
		} ina6;

		// address_length == 0xFFFF
		char const* str;
	};

	word port;
	short address_length;
};
static_assert(sizeof(transport_address) == 0x14);

struct s_transport_secure_address;

extern bool __cdecl transport_address_equivalent(transport_address const* a, transport_address const* b);
extern char const* __cdecl transport_address_get_string(transport_address const* address);
extern void __cdecl transport_address_ipv4_build(transport_address* address, dword ip_address, word port);
extern dword __cdecl transport_address_ipv4_extract(transport_address const* address);
extern bool __cdecl transport_address_is_loopback(transport_address const* address);
extern char* __cdecl transport_address_to_string(transport_address const* address, s_transport_secure_address const* secure_address, char* _string, short maximum_string_length, bool include_port, bool include_extra);
extern bool __cdecl transport_address_valid(transport_address const* address);
extern void __cdecl transport_get_broadcast_address(transport_address* address, word port);
extern void __cdecl transport_get_listen_address(transport_address* address, word port);
extern void __cdecl transport_get_loopback_address(transport_address* address, word port);

extern void transport_address_from_string(wchar_t const* str, transport_address& address);
extern void transport_address_from_string(char const* str, transport_address& address);
extern void transport_address_from_host(char const* hostname, transport_address& address);

