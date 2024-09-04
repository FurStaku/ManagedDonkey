#include "cseries/async_xoverlapped_memory.hpp"

void* __cdecl overlapped_malloc_tracked(dword size, char const* file, long line)
{
	return INVOKE(0x0066D570, overlapped_malloc_tracked, size, file, line);
}

//.text:0066D620 ; c_allocation_base* __cdecl get_overlapped_allocation()

void __cdecl overlapped_memory_dispose()
{
	INVOKE(0x0066D630, overlapped_memory_dispose);
}

//.text:0066D650 ; void __cdecl overlapped_memory_dump(char const*)

void __cdecl overlapped_memory_initialize()
{
	INVOKE(0x0066D670, overlapped_memory_initialize);
}

