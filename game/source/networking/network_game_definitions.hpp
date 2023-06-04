#pragma once

struct c_bitstream;

struct s_player_configuration_from_client;
struct s_network_session_status_data;

bool __cdecl player_configuration_client_decode(c_bitstream* packet, s_player_configuration_from_client* player_from_client, long encoding_type);
void __cdecl player_configuration_client_encode(c_bitstream* packet, s_player_configuration_from_client const* player_from_client, long encoding_type);
bool __cdecl squad_status_decode(c_bitstream* packet, s_network_session_status_data const* status_data);
void __cdecl squad_status_encode(c_bitstream* packet, s_network_session_status_data const* status_data);

