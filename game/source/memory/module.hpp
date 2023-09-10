#pragma once

#include "cseries/cseries.hpp"
#include "memory/member_to_static.hpp"

#define HOOK_DECLARE_CALL_WITH_ADDRESS(ADDR, ADDR2, NAME) static c_hook_call STRCONCAT(NAME##_hook,__LINE__)(ADDR, { .address = ADDR2 })
#define HOOK_DECLARE_CALL(ADDR, NAME) static c_hook_call STRCONCAT(NAME##_hook,__LINE__)(ADDR, { .pointer = NAME })
#define HOOK_DECLARE(ADDR, NAME) static c_hook NAME##_hook(ADDR, { .pointer = NAME })
#define HOOK_DECLARE_CLASS(ADDR, CLASS, NAME) static c_hook CLASS##_##NAME##_hook(ADDR, { .pointer = CLASS::NAME })
#define HOOK_DECLARE_CLASS_MEMBER(ADDR, CLASS, NAME) static c_hook CLASS##_##NAME##_hook(ADDR, { .pointer = member_to_static_function(&CLASS##::##NAME) })

#define HOOK_INVOKE(RESULT, NAME, ...) \
{ \
	NAME##_hook.apply(true); \
	RESULT reinterpret_cast<decltype(&NAME)>(NAME##_hook.get_original())(__VA_ARGS__); \
	NAME##_hook.apply(false); \
}

#define HOOK_INVOKE_CLASS(RESULT, CLASS, NAME, TYPE, ...) \
{ \
	CLASS##_##NAME##_hook.apply(true); \
	RESULT reinterpret_cast<TYPE>(CLASS##_##NAME##_hook.get_original())(__VA_ARGS__); \
	CLASS##_##NAME##_hook.apply(false); \
}

#define HOOK_INVOKE_CLASS_MEMBER(RESULT, CLASS, NAME, ...) \
{ \
    CLASS##_##NAME##_hook.apply(true); \
    RESULT (this->*static_to_member_t<decltype(&CLASS##::##NAME)>{ .address = CLASS##_##NAME##_hook.get_original() }.function)(__VA_ARGS__); \
    CLASS##_##NAME##_hook.apply(false); \
}

#define DATA_PATCH_DECLARE(ADDR, NAME, ...) static c_data_patch STRCONCAT(NAME##_patch,__LINE__)(ADDR, NUMBEROF(__VA_ARGS__), __VA_ARGS__)
#define DATA_PATCH_DECLARE2(ADDR, NAME, SIZE, ...) static c_data_patch STRCONCAT(NAME##_patch,__LINE__)(ADDR, SIZE, __VA_ARGS__)

union module_address
{
	dword address;
	byte* data;
	void* pointer;
};

extern module_address global_module;
extern dword global_address_get(dword rva);

extern void set_donkey_module(void* _module);
extern void* get_donkey_module();

extern void apply_all_hooks(bool revert);
extern void apply_all_patches(bool revert);

class c_hook
{
public:
	c_hook(dword address, module_address const function, bool remove_base = true);

	bool apply(bool revert);

	dword get_address()
	{
		return m_addr.address;
	}

	dword get_original()
	{
		return m_orig.address;
	}

private:
	module_address m_addr;
	module_address m_orig;
};

class c_hook_call
{
#pragma pack(push, 1)
	struct call_instruction
	{
		byte opcode;
		dword offset;
	};
	static_assert(sizeof(call_instruction) == 0x5);
#pragma pack(pop)

public:
	c_hook_call(dword address, module_address const function, bool remove_base = true);

	bool apply(bool revert);

	dword get_address()
	{
		return m_addr.address;
	}

private:
	module_address m_addr;
	call_instruction const m_call;
	call_instruction m_call_original;
};

class c_data_patch
{
public:
	c_data_patch(dword address, long patch_size, byte const(&patch)[], bool remove_base = true);

	bool apply(bool revert);

private:
	module_address m_addr;
	byte const* m_bytes;
	byte* m_bytes_original;
	long m_byte_count;
};

class c_data_patch_array
{
public:
	template<long k_address_count, long k_patch_size>
	c_data_patch_array(dword const(&_addresses)[k_address_count], byte const(&patch)[k_patch_size]);

	template<long k_patch_size>
	c_data_patch_array(dword address, byte const(&patch)[k_patch_size]);

	~c_data_patch_array();

	bool apply(bool revert);

private:
	long address_count;
	long byte_count;

	const dword* addresses;

	const byte* bytes;
	byte** bytes_original;
};

extern void buffer_as_byte_string(byte* buffer, dword buffer_size, char* out_string, long out_string_size);

template<typename t_type, long k_string_size>
void type_as_byte_string(t_type* type, char(&out_string)[k_string_size])
{
	buffer_as_byte_string((byte*)type, sizeof(t_type), out_string, k_string_size);
}

bool patch_pointer(module_address address, const void* pointer);

