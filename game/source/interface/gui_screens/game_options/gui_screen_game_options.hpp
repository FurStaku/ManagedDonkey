#pragma once

#include "game/game_engine_variant.hpp"
#include "interface/c_gui_screen_widget.hpp"
#include "interface/user_interface_data.hpp"
#include "interface/user_interface_messages.hpp"
#include "main/global_preferences.hpp"
#include "multithreading/synchronized_value.hpp"
#include "networking/online/online_guide_pc.hpp"
#include "networking/tools/network_blf.hpp"

class c_virtual_keyboard_task;

struct s_game_options_history_stack_node
{
	e_game_engine_category template_category;
	e_game_engine_category interface_category;
	int32 focused_element_handle;
};
static_assert(sizeof(s_game_options_history_stack_node) == 0xC);

class c_game_options_category_datasource :
	public c_gui_ordered_data
{
public:
	//virtual ~c_game_options_category_datasource();
	//virtual void get_column_names(int32*, int32);
	//virtual bool get_element(int32, void*, int32);
	//virtual bool get_string_id_value(int32, int32, int32*);

protected:
	//virtual int32 get_current_item_count_internal();

public:
	//c_game_options_category_datasource(const c_game_options_category_datasource&);
	//c_game_options_category_datasource(e_game_engine_category, e_game_engine_category, const c_game_variant*);
	//c_game_options_category_datasource& operator=(const c_game_options_category_datasource&);

private:
	const c_game_variant* m_edit_variant;
	e_game_engine_category m_template_category;
	e_game_engine_category m_interface_category;
};

class c_game_options_parameter_datasource :
	public c_gui_ordered_data
{
public:
	//virtual ~c_game_options_parameter_datasource();
	//virtual void get_column_names(int32* const column_names, int32* column_count) override;
	//virtual bool get_integer_value(int32 element_handle, int32 value_name, int32* value) override;
	//virtual bool get_string_id_value(int32 element_handle, int32 value_name, int32* value) override;
	//virtual int32 get_current_item_count_internal() override;

private:
	e_game_variant_parameter m_parameter;
};
static_assert(sizeof(s_game_options_history_stack_node) == 0xC);

class c_load_game_options_screen_message :
	public c_load_screen_message
{
public:
	//virtual ~c_load_game_options_screen_message();
	//virtual void apply_initial_state(c_gui_screen_widget* screen) const override;

private:
	c_game_variant m_edit_game_variant;
	c_game_variant m_revert_game_variant;
	e_game_engine_category m_template_category;
	e_game_engine_category m_interface_category;
	int32 m_focused_element_handle;
	s_game_options_history_stack_node m_settings_history_stack[16];
	int32 m_history_stack_depth;
	int32 m_layered_position;
};

class c_gui_screen_game_options :
	public c_gui_screen_widget
{
public:
	enum e_asynchronous_operation
	{
		_operation_none = 0,
		_operation_save,
		_operation_save_as_new,
		_operation_rename,
		_operation_revert_changes,

		k_number_of_variant_desired_operations,
	};

	enum e_destructive_action_confirmation_result
	{
		_result_indeterminate = 0,
		_result_confirmation,
		_result_cancellation,
	};

	enum e_variant_save_options_dialog_result
	{
		_save = 0,
		_save_as_new,
		_revert,
		_cancel,

		k_number_of_variant_save_options_dialog_results,

		_invalid_result = NONE,
	};

public:
	//virtual ~c_gui_screen_game_options();
	//virtual void initialize() override;
	//virtual void post_initialize() override;
	//virtual void update(uns32 current_milliseconds) override;
	//virtual bool handle_controller_input_message(const c_controller_input_message* message) override;
	//virtual void initialize_datasource();
	//virtual bool handle_list_item_chosen(const c_controller_input_message* message, int32 list_name, c_gui_list_item_widget* list_item_widget, c_gui_data* datasource);
	//virtual bool handle_dialog_result(const c_dialog_result_message* message);

private:
	c_game_variant m_edit_game_variant;
	c_game_variant m_revert_game_variant;
	e_game_variant_parameter m_editing_parameter;
	s_game_options_history_stack_node m_settings_history_stack[16];
	int32 m_setting_stack_depth;
	int32 m_layered_position;
	e_asynchronous_operation m_asynchronous_operation;
	e_variant_save_options_dialog_result m_confirmation_action;
	e_destructive_action_confirmation_result m_confirmation_result;
	s_blffile_game_variant m_variant_on_disk;
	e_controller_index m_asynchronous_operation_controller;
	c_virtual_keyboard_task* m_keyboard_task;
	wchar_t m_virtual_keyboard_results_buffer[256];
	c_string_verify_task m_string_verify_task;
	wchar_t m_saved_game_name_buffer[128];
	wchar_t m_saved_game_description_buffer[128];
	s_gui_game_setup_storage::s_multiplayer_settings m_multiplayer_setup;
	int32 m_create_new_variant_task;
	int32 m_write_new_variant_task;
	int32 m_delete_edit_variant_task;
	int32 m_write_variant_task;
	c_synchronized_long m_async_success;
	c_synchronized_long m_async_complete;
	c_synchronized_long m_content_item_index;
	uns32 m_progress_dialog_start_time_milliseconds;
};
static_assert(sizeof(c_gui_screen_game_options) == 0x11758);
static_assert(sizeof(c_gui_screen_game_options) == sizeof(c_gui_screen_widget) + 0xFCB8);

