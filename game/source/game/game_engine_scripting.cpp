#include "game/game_engine_scripting.hpp"

#include "cseries/cseries.hpp"
#include "game/game.hpp"
#include "game/game_engine.hpp"
#include "game/game_engine_team.hpp"

void __cdecl game_engine_game_won(short team)
{
	if (!game_is_authoritative())
		return;

	if (game_engine_has_teams())
	{
		if (VALID_INDEX(team, 8))
		{
			game_engine_end_round_with_winner(team, true, _game_engine_end_condition_game_end_scripting);
		}
		else
		{
			c_console::write_line("invalid team index #%ld passed to game_engine_game_won");
		}
	}
	else
	{
		c_console::write_line("game_engine_game_won: not a team game!");
	}
}