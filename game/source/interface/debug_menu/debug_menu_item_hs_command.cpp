#include "interface/debug_menu/debug_menu_item_hs_command.hpp"

#include "interface/debug_menu/debug_menu_main.hpp"
#include "main/console.hpp"

#include <string.h>

void c_debug_menu_item_hs_command::notify_selected()
{
	if (m_command)
	{
		//hs_compile_and_evaluate(_event_level_message, "debug_menu", m_command, true);
		console_process_command(m_command, true);
	}
}

real_argb_color const* c_debug_menu_item_hs_command::get_enabled_color()
{
	return debug_real_argb_tv_orange;
}

c_debug_menu_item_hs_command::c_debug_menu_item_hs_command(c_debug_menu* menu, char const* name, char const* command) :
	c_debug_menu_item_numbered(menu, name, NULL)
{
	ASSERT(name != NULL && command != NULL && menu != NULL);

	long command_length = strlen(command) + 1;
	ASSERT(command_length > 0);

	m_command = static_cast<char*>(debug_menu_malloc(command_length));
	if (m_command)
		csstrnzcpy(m_command, command, command_length);
}

