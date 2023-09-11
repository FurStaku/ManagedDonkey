#include "networking/delivery/network_link.hpp"

#include "memory/bitstream.hpp"
#include "memory/module.hpp"
#include "networking/network_memory.hpp"
#include "networking/transport/transport.hpp"
#include "networking/transport/transport_address.hpp"

bool __cdecl c_network_link::adjust_packet_size(bool game_data, long voice_data_length, long* game_data_length) const
{
	//return DECLFUNC(0x0043B5E0, bool, __cdecl, bool, long, long*)(game_data, voice_data_length, game_data_length);

	ASSERT(game_data_length);
	ASSERT(voice_data_length > 0 || *game_data_length > 0);

	if (game_data)
	{
		long maximum_payload = transport_get_packet_maximum_payload(0);

		ASSERT(voice_data_length == 0);
		ASSERT((maximum_payload % 8) == 0);

		if (*game_data_length > 8)
			*game_data_length -= *game_data_length % 8;

		if (*game_data_length > maximum_payload)
			*game_data_length = maximum_payload;
	}
	else
	{
		long maximum_payload = transport_get_packet_maximum_payload(1);
		long payload_length = maximum_payload - (voice_data_length + 2) - (maximum_payload - (voice_data_length + 2)) % 8;

		if (payload_length < 0)
		{
			c_console::write_line("networking:link: requested in-channel VDP packet (%d bytes voice, %d bytes data) exceeds maximum payload (%d bytes), impossible to send", voice_data_length, *game_data_length, maximum_payload);
			return false;
		}
		else
		{
			if (*game_data_length > 8)
				*game_data_length -= *game_data_length % 8;

			if (*game_data_length > payload_length)
				*game_data_length = payload_length;
		}
	}

	return true;
}

void __cdecl c_network_link::attach_out_of_band(c_network_out_of_band_consumer* out_of_band)
{
	m_out_of_band = out_of_band;
}

bool c_network_link::create_endpoint(e_transport_type type, word port, bool set_broadcast_option, transport_endpoint** out_endpoint)
{
	return DECLFUNC(0x0043B6F0, bool, __cdecl, e_transport_type, word, bool, transport_endpoint**)(type, port, set_broadcast_option, out_endpoint);

	//transport_endpoint* endpoint = transport_endpoint_create(type);
	//if (!endpoint)
	//{
	//	c_console::write_line("networking:link: create_endpoint[%d] - unable to create endpoint!", type);
	//	return false;
	//}
	//
	//transport_address address;
	//transport_get_listen_address(&address, port);
	//
	//if (!transport_endpoint_bind(endpoint, &address) || !transport_endpoint_set_blocking(endpoint, false) || (set_broadcast_option && !transport_endpoint_set_option_value(endpoint, _transport_endpoint_option_broadcast, true)))
	//{
	//	c_console::write_line("networking:link: create_endpoint(%d) - unable to setup endpoint!", type);
	//	transport_endpoint_delete(endpoint);
	//	return false;
	//}
	//
	//*out_endpoint = endpoint;
	//return true;
}

bool __cdecl c_network_link::create_endpoints()
{
	//return DECLFUNC(0x0043B7C0, bool, __thiscall, c_network_link*)(this);

	bool result = false;

	word broadcast_port = k_broadcast_port;
	while (true)
	{
		g_broadcast_port = broadcast_port;

		result = create_endpoint(_transport_type_udp, broadcast_port, true, &m_endpoint);
		if (result)
			break;

		if (m_endpoint)
		{
			destroy_endpoints();
			m_endpoint = nullptr;
		}

		if (++broadcast_port - k_broadcast_port >= k_broadcast_port_alt_ammount)
		{
			g_broadcast_port = k_broadcast_port;
			return result;
		}
	}

	return result;
}

bool c_network_link::decode_packet(long data_buffer_size, byte const* data_buffer, s_link_packet* packet) const
{
	return DECLFUNC(0x0043B820, bool, __thiscall, c_network_link const*, long, byte const*, s_link_packet*)(this, data_buffer_size, data_buffer, packet);
}

void __cdecl c_network_link::destroy_endpoints()
{
	//DECLFUNC(0x0043B940, void, __thiscall, c_network_link*)(this);

	if (m_endpoint)
	{
		transport_endpoint_delete(m_endpoint);
		m_endpoint = 0;
	}
}

c_network_channel* __cdecl c_network_link::get_associated_channel(transport_address const* address) const
{
	return DECLFUNC(0x0043BA40, c_network_channel*, __cdecl, transport_address const*)(address);
}

bool __cdecl c_network_link::physical_link_available()
{
	//INVOKE(0x0043BBB0, c_network_link::physical_link_available);

	return transport_available();
}

void __cdecl c_network_link::send_out_of_band(c_bitstream const* game_data, transport_address const* address, long* out_size_on_wire)
{
	ASSERT(game_data);
	ASSERT(address);

	DECLFUNC(0x0043C250, void, __thiscall, c_network_link*, c_bitstream const*, transport_address const*, long*)(this, game_data, address, out_size_on_wire);
}
