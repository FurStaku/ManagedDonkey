#include "physics/havok_utilities.hpp"

#include "cseries/cseries.hpp"

hkMoppCode* __cdecl mopp_code_data_get_mopp_code(s_tag_data* data, long offset)
{
	//ASSERT(suppress_errors || offset + mopp_code->getCodeSize() <= data->size);
	//ASSERT(suppress_errors || mopp_code->m_data.m_data == reinterpret_cast<hkUint8*>(mopp_code + 1));

	return INVOKE(0x00717BF0, mopp_code_data_get_mopp_code, data, offset);
}

long __cdecl mopp_code_get_tag_data_size(hkMoppCode const* mopp_code)
{
	ASSERT(mopp_code != NULL);

	return INVOKE(0x00717CA0, mopp_code_get_tag_data_size, mopp_code);
}

