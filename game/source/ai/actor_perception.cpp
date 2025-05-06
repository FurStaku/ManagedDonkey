#include "ai/actor_perception.hpp"

#include "ai/actors.hpp"
#include "ai/ai_debug.hpp"
#include "memory/thread_local.hpp"
#include "render/render_debug.hpp"

void debug_render_vehicle_interest()
{
	actor_iterator actor_iter{};
	actor_iterator_new(&actor_iter, true);
	while (actor_datum* actor = actor_iterator_next(&actor_iter))
	{
		if (actor->player.player_index_interested != NONE)
		{
			ai_player_state& ai_player = g_ai_players[actor->player.player_index_interested];
			if (ai_player.player_index != NONE)
			{
				player_datum* player = DATUM_GET(player_data, player_datum, ai_player.player_index);
				if (player->unit_index != NONE)
				{
					unit_datum* unit = UNIT_GET(player->unit_index);

					real_argb_color const* color = actor->player.player_interested_ticks <= game_seconds_to_ticks_round(2.0f) ? global_real_argb_yellow : global_real_argb_red;

					render_debug_line(true, &actor->input.position.head_position, &unit->object.bounding_sphere_center, color);

					ai_debug_drawstack_setup(&actor->input.position.head_position);
					render_debug_string_at_point(ai_debug_drawstack(), c_string_builder("uninterested ticks: %i", actor->player.player_uninterested_ticks).get_string(), color);
					render_debug_string_at_point(ai_debug_drawstack(), c_string_builder("interested ticks: %i", actor->player.player_interested_ticks).get_string(), color);
				}
			}
		}
	}
}

