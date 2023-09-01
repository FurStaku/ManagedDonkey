#pragma once

#include "cseries/cseries.hpp"

struct s_tag_resource_access_datum
{
	long resource_handle;
	void* resource_data;
};
static_assert(sizeof(s_tag_resource_access_datum) == 0x8);

struct c_tag_resource_cache_file_access_cache
{
public:
	bool __cdecl cached_resource_available(long resource_handle)
	{
		if (resource_handle == NONE)
			return false;

		s_tag_resource_access_datum* cached_resource = m_cached_access_datums[resource_handle];
		if (!cached_resource)
			return false;

		//ASSERT(cached_resource->resource_handle == resource_handle || cached_resource->resource_handle == NONE);

		return cached_resource->resource_handle != NONE && cached_resource->resource_data;
	}

	void* __cdecl get_cached_resource_data(long resource_handle)
	{
		ASSERT(resource_handle != NONE);

		s_tag_resource_access_datum* cached_resource = m_cached_access_datums[DATUM_INDEX_TO_ABSOLUTE_INDEX(resource_handle)];
		//ASSERT(cached_resource->resource_handle == resource_handle);
		//ASSERT(cached_resource->resource_data);

		return cached_resource;
	}

	// m_handles[interop->descriptor]
	c_wrapped_array<qword> __unknown0;

	c_wrapped_array<s_tag_resource_access_datum> m_cached_access_datums;
	c_wrapped_array<dword> m_cached_resource_handles;
	c_wrapped_array<void> __unknown18;

	c_allocation_base* m_allocator;
	byte __data24[0x14];
};
static_assert(sizeof(c_tag_resource_cache_file_access_cache) == 0x38);

