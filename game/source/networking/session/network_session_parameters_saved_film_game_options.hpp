#pragma once

#include "game/game_options.hpp"
#include "networking/session/network_session_parameters_chunked.hpp"
#include "networking/session/network_session_parameters_generic.hpp"

struct s_network_session_parameter_saved_film_game_options
{
	long length_in_ticks;
	long start_ticks;
	game_options options;
};
static_assert(sizeof(s_network_session_parameter_saved_film_game_options) == 0x24B50);

struct c_network_session_parameter_saved_film_game_options :
	public c_network_session_parameter_chunked<s_network_session_parameter_saved_film_game_options, 34816>
{
};
static_assert(sizeof(c_network_session_parameter_saved_film_game_options) == 0x5A740);
