#include "networking/transport/transport_address.hpp"

#include "cseries/cseries_events.hpp"
#include "game/players.hpp"
#include "memory/module.hpp"
#include "networking/transport/transport_dns_winsock.hpp"
#include "networking/transport/transport_security.hpp"

HOOK_DECLARE(0x0043F660, transport_address_equivalent);
HOOK_DECLARE(0x0043F6F0, transport_address_get_string);
HOOK_DECLARE(0x0043F720, transport_address_ipv4_extract);
HOOK_DECLARE(0x0043F730, transport_address_is_loopback);
HOOK_DECLARE(0x0043F750, transport_address_to_string);
HOOK_DECLARE(0x0043F860, transport_address_valid);
HOOK_DECLARE(0x0043F8D0, transport_get_broadcast_address);
HOOK_DECLARE(0x0043F8F0, transport_get_listen_address);
HOOK_DECLARE(0x0043F910, transport_get_loopback_address);

transport_address::transport_address() :
	ipv4_address(0),
	port(0),
	address_length(0)
{
}

transport_address::transport_address(uns32 _ipv4_address, uns16 _port, int16 _address_length) :
	ipv4_address(_ipv4_address),
	port(_port),
	address_length(_address_length)
{
}

transport_address::transport_address(const s_player_identifier* player_identifier) :
	ipv4_address(0),
	port(0),
	address_length(0)
{
	REFERENCE_DECLARE(player_identifier->identifier + 0, uns32 const, identifier_ipv4_address);
	REFERENCE_DECLARE(player_identifier->identifier + 4, uns16 const, identifier_port);
	REFERENCE_DECLARE(player_identifier->identifier + 6, uns16 const, identifier_flags);
	ipv4_address = identifier_ipv4_address;
	port = identifier_port;
	address_length = sizeof(uns32);
}

bool __cdecl transport_address_equivalent(const transport_address* a, const transport_address* b)
{
	//return INVOKE(0x0043F660, transport_address_equivalent, a, b);

	ASSERT(a != NULL);
	ASSERT(b != NULL);

	int16 address_length = a->address_length <= b->address_length ? a->address_length : b->address_length;
	return a->address_length > 0 && a->address_length == b->address_length && csmemcmp(a, b, address_length) == 0 && a->port == b->port;
}

const char* __cdecl transport_address_get_string(const transport_address* address)
{
	//return INVOKE(0x0043F6F0, transport_address_get_string, address);

	static char string[256]{};
	transport_address_to_string(address, nullptr, string, 256, false, true);

	return string;
}

void __cdecl transport_address_ipv4_build(transport_address* address, uns32 ip_address, uns16 port)
{
	ASSERT(address);

	address->address_length = sizeof(uns32);
	address->ipv4_address = ip_address;
	address->port = port;
}

uns32 __cdecl transport_address_ipv4_extract(const transport_address* address)
{
	//return INVOKE(0x0043F720, transport_address_ipv4_extract, address);

	ASSERT(address);

	return address->ipv4_address;
}

bool __cdecl transport_address_is_loopback(const transport_address* address)
{
	//return INVOKE(0x0043F730, transport_address_is_loopback, address);

	ASSERT(address);

	return address->address_length == sizeof(uns32) && address->ipv4_address == 0x7F000001;
}

char* __cdecl transport_address_to_string(const transport_address* address, const s_transport_secure_address* secure_address, char* string, int16 maximum_string_length, bool include_port, bool include_extra)
{
	//return INVOKE(0x0043F750, transport_address_to_string, address, secure_address, string, maximum_string_length, include_port, include_extra);

	ASSERT(address);
	ASSERT(string);
	ASSERT(maximum_string_length > 0);

	char secure_address_string[256]{};
	s_transport_secure_identifier secure_identifier_from_address;
	s_transport_secure_address secure_address_from_address;

	csstrnzcpy(string, "", maximum_string_length);
	switch (address->address_length)
	{
	case 4:
	{
		csnzprintf(string, maximum_string_length, "%hd.%hd.%hd.%hd",
			address->ina.bytes[3],
			address->ina.bytes[2],
			address->ina.bytes[1],
			address->ina.bytes[0]);

		if (include_port)
			csnzappendf(string, maximum_string_length, ":%hd", address->port);

		if (include_extra)
		{
			if (secure_address)
			{
				transport_secure_address_to_string(secure_address, secure_address_string, 256, false, false);
				csstrnzcat(string, secure_address_string, maximum_string_length);
			}
			else if (transport_secure_identifier_retrieve(address, 0, &secure_identifier_from_address, &secure_address_from_address))
			{
				transport_secure_address_to_string(&secure_address_from_address, secure_address_string, 256, false, false);
				csstrnzcat(string, secure_address_string, maximum_string_length);
				csnzappendf(string, maximum_string_length, "[%s]", transport_secure_identifier_get_string(&secure_identifier_from_address));
			}
			else
			{
				csnzappendf(string, maximum_string_length, " (insecure)");
			}
		}
	}
	break;
	case 16:
	{
		csnzprintf(string, maximum_string_length, "%04X.%04X.%04X.%04X.%04X.%04X.%04X.%04X",
			address->ina6.words[0],
			address->ina6.words[1],
			address->ina6.words[2],
			address->ina6.words[3],
			address->ina6.words[4],
			address->ina6.words[5],
			address->ina6.words[6],
			address->ina6.words[7]);

		if (include_port)
			csnzappendf(string, maximum_string_length, ":%hd", address->port);
	}
	break;
	case 0xFFFF:
	{
		csstrnzcpy(string, address->str, maximum_string_length);
	}
	break;
	case 0:
	{
		csstrnzcpy(string, "NULL_ADDRESS", maximum_string_length);
	}
	break;
	}

	return string;
}

bool __cdecl transport_address_valid(const transport_address* address)
{
	//return INVOKE(0x0043F860, transport_address_valid, address);

	bool result = false;
	if (address)
	{
		switch (address->address_length)
		{
		case 0xFFFFFFFF:
		{
			result = address->ipv4_address != 0;
		}
		break;
		case 4:
		{
			result = address->ipv4_address != 0;
			if (!result)
				event(_event_warning, "networking:transport:transport_address_valid: the IPV4 address is NOT valid");
		}
		break;
		case 16:
		{
			for (int32 i = 0; i < 8; ++i)
			{
				if (address->ina6.words[i])
				{
					result = true;
					break;
				}
			}
			if (!result)
				event(_event_warning, "networking:transport:transport_address_valid: the IPV6 address is NOT valid");
		}
		break;
		}
	}

	return result;
}

void __cdecl transport_get_broadcast_address(transport_address* address, uns16 port)
{
	//INVOKE(0x0043F8D0, transport_get_broadcast_address, address, port);

	ASSERT(address);

	address->address_length = sizeof(uns32);
	address->ipv4_address = 0xFFFFFFFF;
	address->port = port;
}

void __cdecl transport_get_listen_address(transport_address* address, uns16 port)
{
	//INVOKE(0x0043F8F0, transport_get_listen_address, address, port);

	ASSERT(address);

	address->address_length = sizeof(uns32);
	address->ipv4_address = 0;
	address->port = port;
}

void __cdecl transport_get_loopback_address(transport_address* address, uns16 port)
{
	//INVOKE(0x0043F910, transport_get_loopback_address, address, port);

	ASSERT(address);

	address->address_length = sizeof(uns32);
	address->ipv4_address = 0x7F000001;
	address->port = port;
}

void transport_address_from_string(const wchar_t* str, transport_address& address)
{
	uns8 ip_addr[4]{};
	if (swscanf_s(str, L"%hhd.%hhd.%hhd.%hhd:%hd", &ip_addr[3], &ip_addr[2], &ip_addr[1], &ip_addr[0], &address.port))
	{
		address.ina.bytes[0] = ip_addr[0];
		address.ina.bytes[1] = ip_addr[1];
		address.ina.bytes[2] = ip_addr[2];
		address.ina.bytes[3] = ip_addr[3];

		address.address_length = sizeof(address.ina);
	}
}

void transport_address_from_string(const char* str, transport_address& address)
{
	uns8 ip_addr[4]{};
	if (sscanf_s(str, "%hhd.%hhd.%hhd.%hhd:%hd", &ip_addr[3], &ip_addr[2], &ip_addr[1], &ip_addr[0], &address.port))
	{
		address.ina.bytes[0] = ip_addr[0];
		address.ina.bytes[1] = ip_addr[1];
		address.ina.bytes[2] = ip_addr[2];
		address.ina.bytes[3] = ip_addr[3];

		address.address_length = sizeof(address.ina);
	}
}

void transport_address_from_host(const char* name, transport_address& address)
{
	dns_result result{};
	csstrnzcpy(result.name, name, sizeof(result.name));
	if (transport_dns_name_to_address(&result))
	{
		address = result.address[0];
	}
}

