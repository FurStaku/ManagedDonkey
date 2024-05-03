#include "data_mining/data_mine_usability.hpp"

#include "game/game.hpp"
#include "interface/interface.hpp"
#include "interface/interface_constants.hpp"
#include "text/draw_string.hpp"

#include <climits>

s_persisted_usability_globals g_persisted_usability_globals;

s_persisted_usability_globals::s_persisted_usability_globals() :
	display_mission_segment(false),
	mission_segment_buffer(),
	user_experience_buffer()
{
}

void data_mine_render_mission_segment()
{
	if (g_persisted_usability_globals.display_mission_segment && game_in_progress() && game_is_campaign())
	{
		c_rasterizer_draw_string draw_string{};
		c_font_cache_mt_safe font_cache{};
		short_rectangle2d display_title_safe_pixel_bounds{};
		short_rectangle2d bounds{};

		interface_get_current_display_settings(NULL, NULL, NULL, &display_title_safe_pixel_bounds);

		bounds.x0 = display_title_safe_pixel_bounds.x0;
		bounds.y0 = display_title_safe_pixel_bounds.y1 - 80;
		bounds.x1 = SHRT_MAX;
		bounds.y1 = SHRT_MAX;

		interface_set_bitmap_text_draw_mode(&draw_string, 0, -1, 0, 0, 5, 0);

		draw_string.set_color(global_real_argb_yellow);
		draw_string.set_tab_stops(NULL, 0);
		draw_string.set_bounds(&bounds);
		draw_string.draw(&font_cache, g_persisted_usability_globals.mission_segment_buffer.get_string());
	}
}

