#include "interface/user_interface_utilities.hpp"

#include "cseries/cseries.hpp"
#include "interface/c_gui_widget.hpp"
#include "math/color_math.hpp"

void tint_widget_to_change_color(c_gui_widget* widget, long color_list_index, bool team_game)
{
	INVOKE(0x00AA4C80, tint_widget_to_change_color, widget, color_list_index, team_game);
}

void tint_widget_to_change_argb_color(c_gui_widget* widget, argb_color color)
{
	real_argb_color real_color{};
	pixel32_to_real_argb_color(color, &real_color);

	// c_gui_widget::modulate_tint_color
	DECLFUNC(0x00AB9D70, void, __thiscall, c_gui_widget*, real_argb_color*)(widget, &real_color);
}

