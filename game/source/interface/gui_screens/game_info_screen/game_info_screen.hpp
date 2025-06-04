#pragma once

#include "interface/c_gui_screen_widget.hpp"

class c_gui_game_info_screen :
	public c_gui_screen_widget
{
public:
	c_gui_game_info_screen(int32 name) :
		c_gui_screen_widget(name)
	{
		DECLFUNC(0x00ADE090, c_gui_game_info_screen*, __thiscall, c_gui_game_info_screen*, int32)(this, name);
	}
};
static_assert(sizeof(c_gui_game_info_screen) == sizeof(c_gui_screen_widget));