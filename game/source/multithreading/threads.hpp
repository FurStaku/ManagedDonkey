#pragma once

#include "cseries/cseries.hpp"
#include "multithreading/synchronized_value.hpp"

enum e_registered_threads
{
	k_thread_unknown = 0,
	k_thread_main,
	k_thread_render,
	k_thread_async_io,
	k_thread_netdebug,
	k_thread_audio,
	k_thread_profiler,
	k_thread_event_logs,
	k_thread_network_block_detection,
	k_thread_update,

	k_registered_thread_count
};

enum e_thread_priority
{
	_thread_priority_default = 0,
	_thread_priority_idle,
	_thread_priority_lowest,
	_thread_priority_below_normal,
	_thread_priority_normal,
	_thread_priority_above_normal,
	_thread_priority_highest,
	_thread_priority_time_critical,

	k_thread_priority_count
};

enum e_thread_processor
{

};

struct s_thread_assert_arguments
{
	char const* statement;
	char const* file;
	long line;
	bool fatal;
};
static_assert(sizeof(s_thread_assert_arguments) == 0x10);

struct s_thread_definition
{
	char const* name;
	dword processor_index;
	dword stack_size;
	e_thread_priority default_priority;
	dword(*start_routine)(void*);
	void* user_parameter;
};
static_assert(sizeof(s_thread_definition) == 0x18);

struct s_thread_system_globals
{
	void* thread_handle[k_registered_thread_count];
	dword thread_id[k_registered_thread_count];
	void* thread_user_data[k_registered_thread_count];

	//c_interlocked_long thread_should_exit[k_registered_thread_count];
	//c_interlocked_long thread_has_crashed[k_registered_thread_count];
	//c_interlocked_long thread_should_assert[k_registered_thread_count];
	//c_interlocked_long thread_should_crash[k_registered_thread_count];

	c_interlocked_long thread_should_exit[k_registered_thread_count];

	// g_thread_system_initialized
	// why is this here?
	c_interlocked_long initialized;

	c_interlocked_long thread_has_crashed[k_registered_thread_count];
};
static_assert(sizeof(s_thread_system_globals) == 0xCC);

extern c_interlocked_long thread_should_assert[k_registered_thread_count];
extern c_interlocked_long thread_should_crash[k_registered_thread_count];

extern s_thread_definition(&k_registered_thread_definitions)[k_registered_thread_count];
extern s_thread_system_globals& g_thread_globals;

struct _EXCEPTION_POINTERS;
extern void __cdecl SetThreadName(dword thread_id, char const* thread_name);
extern bool __cdecl current_thread_should_exit();
extern void __cdecl current_thread_update_test_functions();
extern void __cdecl destroy_thread_management();
extern dword __cdecl get_main_thread_id();
extern char const* __cdecl get_registered_thread_name(long thread_index);
extern e_thread_processor __cdecl get_registered_thread_processor(e_registered_threads thread_index);
extern char const* __cdecl get_thread_name_from_thread_id(long thread_id);
extern void __cdecl initialize_thread(e_registered_threads thread_index);
extern void __cdecl initialize_thread_management();
extern bool __cdecl is_async_thread();
extern bool __cdecl is_main_thread();
extern bool __cdecl is_render_thread();
extern void __cdecl post_thread_assert_arguments(s_thread_assert_arguments* arguments);
extern void __cdecl register_thread(void* handle, long thread_index, dword thread_id, void* user_data);
extern void __cdecl register_thread_running(long thread_index);
extern void __cdecl set_thread_exception_arguments(_EXCEPTION_POINTERS* exception_pointers);
extern void __cdecl sleep(dword milliseconds);
extern void __cdecl start_thread(e_registered_threads thread_index);
extern void __cdecl stop_thread(e_registered_threads thread_index);
extern bool __cdecl switch_to_thread();
extern int __stdcall thread_execution_crash_handler(_EXCEPTION_POINTERS* exception_pointers, long thread_index);
extern dword __stdcall thread_execution_wrapper(void* parameter);
extern bool __cdecl thread_has_crashed(e_registered_threads thread_index);
extern bool __cdecl thread_is_being_traced(e_registered_threads thread_index);
extern void __cdecl thread_release_locks_and_d3d_device();
extern void __cdecl thread_set_priority(long thread_index, e_thread_priority priority);
extern bool __cdecl thread_system_initialized();
extern void __cdecl unregister_thread(long thread_index);
extern bool __cdecl wait_for_thread_to_exit(long thread_index, dword timeout_in_milliseconds);
extern void __cdecl signal_thread_to_crash(e_registered_threads thread_index);
extern void __cdecl signal_thread_to_assert(e_registered_threads thread_index);

