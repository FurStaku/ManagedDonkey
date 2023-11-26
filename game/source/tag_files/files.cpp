#include "tag_files/files.hpp"

#include <string.h>

file_reference_info* file_reference_get_info(s_file_reference* info)
{
	ASSERT(info);
	ASSERT(info->signature == FILE_REFERENCE_SIGNATURE);
	//ASSERT(VALID_BITS(info->flags, NUMBER_OF_REFERENCE_INFO_FLAGS));
	ASSERT(info->location >= NONE && info->location < NUMBER_OF_FILE_REFERENCE_LOCATIONS);

	return info;
}

bool __cdecl datastore_read(char const* file_name, char const* field_name, long length, void* destination)
{
	ASSERT(NULL != file_name);
	ASSERT(NULL != field_name);

	ASSERT('\\0' != file_name[0]);
	ASSERT('\\0' != field_name[0]);

	ASSERT(length <= DATASTORE_MAX_DATA_SIZE);
	ASSERT(strlen(field_name) < DATASTORE_MAX_FIELD_NAME_SIZE);

	return INVOKE(0x00527BC0, datastore_read, file_name, field_name, length, destination);
}

bool __cdecl datastore_write(char const* file_name, char const* field_name, long length, void const* source)
{
	ASSERT(NULL != file_name);
	ASSERT(NULL != field_name);

	ASSERT('\\0' != file_name[0]);
	ASSERT('\\0' != field_name[0]);

	ASSERT(length <= DATASTORE_MAX_DATA_SIZE);
	ASSERT(strlen(field_name) < DATASTORE_MAX_FIELD_NAME_SIZE);

	return INVOKE(0x00527D20, datastore_write, file_name, field_name, length, source);
}

void __cdecl directory_create_or_delete_contents(char const* directory)
{
	INVOKE(0x00527F30, directory_create_or_delete_contents, directory);
}

bool __cdecl file_create_parent_directories_if_not_present(struct s_file_reference const* info)
{
	return INVOKE(0x00527FF0, file_create_parent_directories_if_not_present, info);
}

bool __cdecl file_is_readable(s_file_reference* reference, unsigned long* error)
{
	return INVOKE(0x00528210, file_is_readable, reference, error);
}

//00528240

void __cdecl file_printf(s_file_reference* reference, char const* format, ...)
{
	va_list list;
	va_start(list, format);
	file_vprintf(reference, format, list);
	va_end(list);

	//INVOKE(0x00528270, file_printf, reference, format, ...);
}

bool __cdecl file_read_into_buffer(s_file_reference* reference, void* buffer, dword buffer_length)
{
	return INVOKE(0x005282D0, file_read_into_buffer, reference, buffer, buffer_length);
}

void* __cdecl file_read_into_memory(s_file_reference* reference, dword* out_size)
{
	return INVOKE(0x00528320, file_read_into_memory, reference, out_size);
}

void* __cdecl file_read_into_memory_with_null_padding(s_file_reference* reference, dword* out_size, dword pad_size)
{
	return INVOKE(0x00528350, file_read_into_memory_with_null_padding, reference, out_size, pad_size);
}

s_file_reference* __cdecl file_reference_add_directory(s_file_reference* reference, char const* directory)
{
	return INVOKE(0x00528410, file_reference_add_directory, reference, directory);
}

s_file_reference* __cdecl file_reference_add_directory_wide(s_file_reference* reference, wchar_t const* directory)
{
	return INVOKE(0x00528490, file_reference_add_directory_wide, reference, directory);
}

s_file_reference* __cdecl file_reference_agnostic_create(s_file_reference* info, short location)
{
	ASSERT(info);
	ASSERT(location >= NONE && location < NUMBER_OF_FILE_REFERENCE_LOCATIONS);

	csmemset(info, 0, sizeof(s_file_reference));
	info->signature = FILE_REFERENCE_SIGNATURE;
	info->location = location;

	return info;

	//return INVOKE(0x00528500, file_reference_agnostic_create, reference, location);
}

s_file_reference* __cdecl file_reference_copy(s_file_reference* info, s_file_reference const* other)
{
	csmemcpy(info, other, sizeof(file_reference_info));
	return info;

	//return INVOKE(0x00528530, file_reference_copy, info, other);
}

s_file_reference* __cdecl file_reference_create_from_path(s_file_reference* reference, char const* path, bool a3)
{
	return INVOKE(0x00528550, file_reference_create_from_path, reference, path, a3);
}

s_file_reference* __cdecl file_reference_create_from_path_wide(s_file_reference* reference, wchar_t const* path, bool a3)
{
	return INVOKE(0x005285B0, file_reference_create_from_path_wide, reference, path, a3);
}

wchar_t* __cdecl file_reference_get_fullpath_wide(s_file_reference const* reference, wchar_t* out_full_path, long full_path_length)
{
	return INVOKE(0x005285F0, file_reference_get_fullpath_wide, reference, out_full_path, full_path_length);
}

char* __cdecl file_reference_get_fullpath(s_file_reference const* reference, char* out_full_path, long full_path_length)
{
	return INVOKE(0x00528630, file_reference_get_fullpath, reference, out_full_path, full_path_length);
}

short __cdecl file_reference_get_location(s_file_reference const* reference)
{
	return INVOKE(0x00528690, file_reference_get_location, reference);
}

char* file_reference_get_name(s_file_reference const* reference, dword_flags flags, char* out_name, long name_length)
{
	return INVOKE(0x005286A0, file_reference_get_name, reference, flags, out_name, name_length);
}

wchar_t* file_reference_get_name_wide(s_file_reference const* reference, dword_flags flags, wchar_t* out_name, long name_length)
{
	return INVOKE(0x005286E0, file_reference_get_name_wide, reference, flags, out_name, name_length);
}

char const* __cdecl file_reference_get_path_for_debugging(s_file_reference const* reference)
{
	return INVOKE(0x005287C0, file_reference_get_path_for_debugging, reference);
}

s_file_reference* __cdecl file_reference_remove_directory(s_file_reference* reference)
{
	return INVOKE(0x005287D0, file_reference_remove_directory, reference);
}

s_file_reference* __cdecl file_reference_remove_name(s_file_reference* reference)
{
	return INVOKE(0x00528820, file_reference_remove_name, reference);
}

s_file_reference* __cdecl file_reference_set_name(s_file_reference* reference, char const* name)
{
	return INVOKE(0x00528880, file_reference_set_name, reference, name);
}

s_file_reference* __cdecl file_reference_set_name_wide(s_file_reference* reference, wchar_t const* name)
{
	return INVOKE(0x005288B0, file_reference_set_name_wide, reference, name);
}

bool __cdecl file_references_equal(s_file_reference const* reference_a, s_file_reference const* reference_b)
{
	return INVOKE(0x00528930, file_references_equal, reference_a, reference_b);
}

void __cdecl file_trim(s_file_reference* reference, long size)
{
	INVOKE(0x005289A0, file_trim, reference, size);
}

void __cdecl file_vprintf(s_file_reference* reference, char const* format, char* list)
{
	INVOKE(0x00528A90, file_printf, reference, format, list);
}

long __cdecl find_files(unsigned long flags, s_file_reference const* directory, long maximum_count, s_file_reference* references)
{
	return INVOKE(0x00528AF0, find_files, flags, directory, maximum_count, references);
}

