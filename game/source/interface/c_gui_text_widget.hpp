#pragma once

#include "interface/c_gui_widget.hpp"
#include "interface/user_interface_text.hpp"
#include "shell/shell.hpp"

enum e_text_widget_definition_flags
{
	_text_widget_definition_flag_left_justify_bit = k_core_widget_definition_flags,
	_text_widget_definition_flag_right_justify_bit,
	_text_widget_definition_flag_scrollable_bit,
	_text_widget_definition_flag_uppercase_bit,
	_text_widget_definition_flag_string_from_exported_text_bit,
	_text_widget_definition_flag_string_from_exported_string_id_bit,
	_text_widget_definition_flag_string_from_exported_global_string_id_bit,
	_text_widget_definition_flag_string_from_exported_integer_bit,
	_text_widget_definition_flag_string_from_list_item_label_bit,
	_text_widget_definition_flag_use_brackets_to_indicate_focus_bit,
	_text_widget_definition_flag_large_text_buffer_255_chars_bit,
	_text_widget_definition_flag_extra_large_text_buffer_bit,
	_text_widget_definition_flag_single_drop_shadow_bit,
	_text_widget_definition_flag_no_drop_shadow_bit,
	_text_widget_definition_flag_allow_list_item_to_override_animation_skin_bit,
	_text_widget_definition_flag_do_not_wrap_text_bit,

	k_text_widget_definition_flags
};

struct s_text_widget_definition : s_core_widget_definition
{
	c_string_id value_override_list;
	c_string_id value_identifier;
	c_string_id text_color_preset;
	c_enum<e_interface_font, short, _interface_font_terminal, k_interface_font_count> custom_font;
	byte : 8;
	byte : 8;
};
static_assert(sizeof(s_text_widget_definition) == sizeof(s_core_widget_definition) + 0x10);

struct s_runtime_text_widget_definition : s_runtime_core_widget_definition
{
	c_string_id value_override_list;
	c_string_id value_identifier;
	real_argb_color text_color_preset;
	c_enum<e_interface_font, long, _interface_font_terminal, k_interface_font_count> custom_font;
};
static_assert(sizeof(s_runtime_text_widget_definition) == sizeof(s_runtime_core_widget_definition) + 0x1C);

struct c_gui_screen_widget;
struct c_gui_text_widget : public c_gui_widget
{
	struct s_text_source_data
	{
		long type;
		c_string_id id;
		long __unknown8;
	};
	static_assert(sizeof(s_text_source_data) == 0xC);

public:

	c_user_interface_text* __cdecl get_text_internal();
	dword __cdecl get_text_buffer_size() const;
	void __cdecl set_text(wchar_t const* text);
	void __cdecl set_text_from_string_id(c_gui_screen_widget* screen, long id);
	wchar_t const* __cdecl get_text();

protected:
	real __unknownDC;
	s_text_source_data text_source_data;
	s_runtime_text_widget_definition m_core_definition;
	long __unknown13C;
};
static_assert(sizeof(c_gui_text_widget) == sizeof(c_gui_widget) + 0x64);

template<long k_maximum_count>
struct c_sized_user_interface_text : public c_user_interface_text
{
protected:
	c_static_wchar_string<k_maximum_count> m_string1;
	c_static_wchar_string<k_maximum_count> m_string2;
	dword m_unknown3;
};
static_assert(sizeof(c_sized_user_interface_text<48>) == 0x120);
static_assert(sizeof(c_sized_user_interface_text<256>) == 0x460);
static_assert(sizeof(c_sized_user_interface_text<1024>) == 0x1060);

template<long k_text_buffer_size>
struct c_gui_sized_text_widget : public c_gui_text_widget
{
protected:
	c_sized_user_interface_text<k_text_buffer_size> m_text_buffer;
};
static_assert(sizeof(c_gui_sized_text_widget<48>) == 0x260);
static_assert(sizeof(c_gui_sized_text_widget<256>) == 0x5A0);
static_assert(sizeof(c_gui_sized_text_widget<1024>) == 0x11A0);

