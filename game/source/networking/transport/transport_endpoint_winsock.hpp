#pragma once

#include "cseries/cseries.hpp"

#include <winsock.h>

enum e_transport_type
{
	_transport_type_udp = 0,
	_transport_type_vdp,
	_transport_type_tcp,
	_transport_type_unix,

	k_transport_type_count
};

enum e_transport_endpoint_option
{
	// SO_REUSEADDR
	_transport_endpoint_option_reuse_address,

	// SO_LINGER
	_transport_endpoint_option_linger,

	// SO_BROADCAST
	_transport_endpoint_option_broadcast,

	// SO_SNDBUF
	_transport_endpoint_option_send_buffer_size,

	// SO_RCVBUF
	_transport_endpoint_option_receive_buffer_size,

	// 0x4001
	_transport_endpoint_option_unknown5,

	k_transport_endpoint_option_count
};

enum e_transport_endpoint_flags
{
	_transport_endpoint_connected_bit = 0,

	_transport_endpoint_listening_bit,

	_transport_endpoint_unknown2_bit,

	// = TEST_BIT(flags, _transport_endpoint_unknown2_bit)
	_transport_endpoint_readable_bit, 

	_transport_endpoint_blocking_bit,

	_transport_endpoint_unknown5_bit,


	// reach?

	_transport_endpoint_unknown6_bit,

	_transport_endpoint_unknown7_bit,

	_transport_endpoint_pending_deletion_bit,

	_transport_endpoint_unknown9_bit
};

struct transport_endpoint
{
	SOCKET socket;
	c_enum<e_transport_type, long, _transport_type_udp, k_transport_type_count> type;

	// e_transport_endpoint_flags
	dword_flags flags;
};

struct transport_address;

extern long __cdecl get_platform_socket_option(e_transport_endpoint_option option);
extern transport_endpoint* __cdecl transport_endpoint_accept(transport_endpoint* listening_endpoint);
extern bool __cdecl transport_endpoint_async_connect(transport_endpoint* endpoint, transport_address const* address);
extern bool __cdecl transport_endpoint_async_is_connected(transport_endpoint* endpoint, bool* is_connected);
extern bool __cdecl transport_endpoint_bind(transport_endpoint* endpoint, transport_address* address);
extern bool __cdecl transport_endpoint_connect(transport_endpoint* endpoint, transport_address const* address);
extern transport_endpoint* __cdecl transport_endpoint_create(e_transport_type type);
extern bool __cdecl transport_endpoint_create_socket(transport_endpoint* endpoint, transport_address const* address);
extern void __cdecl transport_endpoint_delete(transport_endpoint* endpoint);
extern void __cdecl transport_endpoint_disconnect(transport_endpoint* endpoint);
extern long __cdecl transport_endpoint_get_option_value(transport_endpoint* endpoint, e_transport_endpoint_option option);
extern bool __cdecl transport_endpoint_get_socket_address(transport_address const* address, long* socket_address_size, byte* const socket_address);
extern bool __cdecl transport_endpoint_get_transport_address(long socket_address_length, byte const* const socket_address, transport_address* address);
extern e_transport_type __cdecl transport_endpoint_get_type(transport_endpoint* endpoint);
extern bool __cdecl transport_endpoint_listen(transport_endpoint* endpoint);
extern short __cdecl transport_endpoint_read(transport_endpoint* endpoint, void* buffer, short length);
extern short __cdecl transport_endpoint_read_from(transport_endpoint* endpoint, void* buffer, short length, transport_address* source);
extern bool __cdecl transport_endpoint_readable(transport_endpoint* endpoint);
extern bool __cdecl transport_endpoint_reject(transport_endpoint* listening_endpoint);
extern bool __cdecl transport_endpoint_set_blocking(transport_endpoint* endpoint, bool blocking);
extern bool __cdecl transport_endpoint_set_option_value(transport_endpoint* endpoint, e_transport_endpoint_option option, long value);
extern void __cdecl transport_endpoint_setup(transport_endpoint* endpoint, e_transport_type type);
extern bool __cdecl transport_endpoint_test(transport_endpoint* endpoint, transport_address const* address);
extern short __cdecl transport_endpoint_write(transport_endpoint* endpoint, void const* buffer, short length);
extern short __cdecl transport_endpoint_write_to(transport_endpoint* endpoint, void const* buffer, short length, transport_address const* destination);
extern bool __cdecl transport_endpoint_writeable(transport_endpoint* endpoint);
extern bool __cdecl transport_get_endpoint_address(transport_endpoint* endpoint, transport_address* address);
extern bool __cdecl transport_endpoint_connected(transport_endpoint* endpoint);

