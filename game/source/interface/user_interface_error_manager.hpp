#pragma once

#include "cseries/cseries.hpp"
#include "shell/shell.hpp"
#include "text/unicode.hpp"

enum e_gui_alert_flags
{
	_gui_alert_flag_allow_auto_dismissal_bit = 0,
	_gui_alert_flag_show_spinner_bit,

	k_gui_alert_flags
};

enum e_gui_error_category
{
	_gui_error_category_default = 0,
	_gui_error_category_networking,
	_gui_error_category_storage,
	_gui_error_category_controller,

	k_gui_error_category_count
};

enum e_gui_error_icon
{
	_gui_error_icon_default_alert = 0,
	_gui_error_icon_downloading,
	_gui_error_icon_paused,
	_gui_error_icon_uploading,
	_gui_error_icon_completed,

	k_gui_error_icon_count
};

struct s_gui_alert_description
{
	c_string_id error_name;
	c_flags<e_gui_alert_flags, byte, k_gui_alert_flags> flags;
	c_enum<e_gui_error_category, byte, _gui_error_category_default, k_gui_error_category_count> error_category;
	c_enum<e_gui_error_icon, byte, _gui_error_icon_default_alert, k_gui_error_icon_count> error_icon;
	byte pad0[1];
	c_string_id title;
	c_string_id message;
};
static_assert(sizeof(s_gui_alert_description) == 0x10);

struct c_gui_queued_error
{
public:
	c_gui_queued_error();

	void set(s_gui_alert_description const* alert_description, wchar_t const* custom_title, wchar_t const* custom_message, e_controller_index controller_index, long posted_time, bool requires_resolution, bool blocking);
	bool match(e_controller_index controller_index, long error_name, wchar_t const* custom_message) const;
	bool is_valid() const;
	void clear();
	bool get_resolved() const;
	void set_resolved(bool resolved);
	long get_error_name() const;
	e_gui_error_category get_error_category() const;
	bool get_auto_dismissable() const;
	bool get_requires_resolution() const;
	bool get_blocking() const;
	long get_posted_time() const;
	void set_posted_time(long posted_time);
	wchar_t const* get_custom_title() const;
	wchar_t const* get_custom_message() const;
	e_controller_index get_controller_index() const;

protected:
	bool m_is_valid;
	bool m_requires_resolution;
	bool m_auto_dismissable;
	bool m_show_spinner;
	c_string_id m_error_name;
	c_enum<e_gui_error_category, long, _gui_error_category_default, k_gui_error_category_count> m_error_category;
	c_enum<e_gui_error_icon, long, _gui_error_icon_default_alert, k_gui_error_icon_count> m_error_icon;
	long m_posted_time;
	c_string_id m_title;
	c_string_id m_message;
	c_enum<e_controller_index, long, _controller_index0, k_number_of_controllers> m_controller_index;
	c_static_wchar_string<256> m_custom_title;
	c_static_wchar_string<256> m_custom_message;
	bool m_blocking;
};
static_assert(sizeof(c_gui_queued_error) == 0x424);

struct c_gui_error_manager
{
public:
	c_gui_error_manager();

	bool any_error_active_for_controller(e_controller_index controller_index);
	bool any_error_active_for_window(e_window_index window_index);
	void clear_all_errors();
	void clear_error(long error_name, e_controller_index controller_index);
	void clear_error_with_custom_message(long error_name, e_controller_index controller_index, wchar_t const* custom_message);
	void dismiss_auto_dismissable_errors(e_controller_index controller_index);
	void dispose_from_old_map();
	c_gui_queued_error const* get_error(e_controller_index controller_index, long error_name, wchar_t const* custom_message) const;
	void initialize();
	void initialize_for_new_map();
	void post_error(long error_name, e_controller_index controller_index, bool requires_resolution);
	void post_error_with_custom_message(long error_name, wchar_t const* custom_message, e_controller_index controller_index, bool requires_resolution);
	void post_toast(long error_name);
	void post_toast_with_custom_message(long error_name, wchar_t const* custom_title, wchar_t const* custom_message);
	void resolve_error(long error_name, e_controller_index controller_index);
	void resolve_error_with_custom_message(long error_name, e_controller_index controller_index, wchar_t const* custom_message);
	void update(dword);
	
private:
	enum e_alert_display_mode
	{
		_alert_display_mode_unknown0 = 0, // none?
		_alert_display_mode_toast,
		_alert_display_mode_in_render_window,

		k_alert_display_mode_count
	};

	void clean_out_error_queue();
	c_gui_queued_error const* get_current_for_user(e_controller_index controller_index);
	c_gui_queued_error const* get_current_for_window(e_window_index window_index);
	e_alert_display_mode get_error_display_mode(e_controller_index* controller_index);
	void post_error_with_custom_message(long error_name, wchar_t const* custom_title, wchar_t const* custom_message, e_controller_index controller_index, bool requires_resolution, bool blocking);
	void sort_queue();

protected:
	c_static_array<c_gui_queued_error, 32> m_errors;
	c_enum<e_alert_display_mode, long, _alert_display_mode_unknown0, k_alert_display_mode_count> m_display_mode;
	bool __unknown8484;
};
static_assert(sizeof(c_gui_error_manager) == 0x8488);

extern c_gui_error_manager& g_gui_error_manager;

extern int __cdecl queued_error_sort_proc(void const* a, void const* b);
extern c_gui_error_manager* __cdecl user_interface_error_manager_get();

