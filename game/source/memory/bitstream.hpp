#pragma once

#include "cseries/cseries.hpp"
#include "networking/transport/transport_security.hpp"

enum e_bitstream_state
{
	_bitstream_state_initial = 0,
	_bitstream_state_writing,
	_bitstream_state_write_finished,
	_bitstream_state_reading,
	_bitstream_state_read_only_for_consistency,
	_bitstream_state_read_finished,

	k_bitstream_state_count
};

long const k_bitstream_maximum_position_stack_size = 4;

struct c_bitstream
{
	struct s_bitstream_data
	{
		long current_memory_bit_position;
		long current_stream_bit_position;
		qword window;
		long window_bits_used;
		byte* next_data;
	};

protected:
	byte* m_data;
	byte* m_data_max;

	long m_data_size_bytes;
	long m_data_size_alignment;

	c_enum<e_bitstream_state, long, _bitstream_state_initial, k_bitstream_state_count> m_state;

	// possibly part of `s_bitstream_data`
	bool __unknown14;

	s_bitstream_data m_bitstream_data;

	long m_position_stack_depth;

	// why is this between `m_position_stack_depth` and `m_position_stack`, is `m_position_stack_depth` actually a qword?
	dword __unknown34;

	s_bitstream_data m_position_stack[k_bitstream_maximum_position_stack_size];

	dword __unknown98;
	dword __unknown9C;

public:
	c_bitstream() :
		m_data(0),
		m_data_max(0),
		m_data_size_bytes(0)
	{
		reset(_bitstream_state_initial);
	}

	c_bitstream(byte* data, long data_length) :
		m_data_size_alignment(1)
	{
		set_data(data, data_length);
	}

	// functions as they appear in memory

	void __cdecl read_raw_data(char const* name, void* value, long size_in_bits);
	long __cdecl read_signed_integer(char const* name, long size_in_bits);
	void __cdecl write_bool(char const* name, bool value);
	void __cdecl write_integer(char const* name, dword value, long size_in_bits);
	void __cdecl write_raw_data(char const* name, void const* value, long size_in_bits);
	void __cdecl write_signed_integer(char const* name, long value, long size_in_bits);
	qword __cdecl read_qword(char const* name, long size_in_bits);
	void __cdecl write_qword(char const* name, qword value, long size_in_bits);

	void __cdecl append(c_bitstream const* stream);
	bool __cdecl begin_consistency_check();
	void __cdecl begin_reading();
	void __cdecl begin_writing(long data_size_alignment);
	void __cdecl data_is_untrusted(bool is_untrusted);
	void __cdecl discard_remaining_data();

private:
	void __cdecl encode_qword_to_memory(qword value, long size_in_bits);

public:
	bool __cdecl overflowed() const;
	bool __cdecl error_occurred() const;

	bool __cdecl reading() const;
	bool __cdecl writing() const;

	void __cdecl finish_consistency_check();
	void __cdecl finish_reading();
	void __cdecl finish_writing(long* out_bits_remaining);

	long __cdecl get_current_stream_bit_position();
	long __cdecl get_space_used_in_bits();
	byte const* __cdecl get_data(long* data_length) const;
	void __cdecl push_position();
	void __cdecl pop_position(bool pop);

private:
	qword __cdecl read_accumulator_from_memory(long a1);

public:
	bool __cdecl read_bool(char const* name);
	void __cdecl read_bits_internal(void* data, long size_in_bits);
	dword __cdecl read_integer(char const* name, long size_in_bits);
	void __cdecl read_identifier(char const* identifier);
	void __cdecl read_point3d(char const* name, int32_point3d* point, long axis_encoding_size_in_bits);
	real __cdecl read_quantized_real(char const* name, real min_value, real max_value, long size_in_bits, bool exact_midpoint, bool exact_endpoints);
	qword __cdecl read_qword_internal(long size_in_bits);
	void __cdecl read_secure_address(char const* name, s_transport_secure_address* address);
	void __cdecl read_string(char const* name, char* _string, long max_string_size);
	void __cdecl read_string_utf8(char const* name, char* char_string, long max_string_size);
	void __cdecl read_string_wchar(char const* name, wchar_t* _string, long max_string_size);
	void __cdecl read_vector(char const* name, vector3d* vector, real min_value, real max_value, long step_count_size_in_bits, long size_in_bits);

	template<typename t_enum, long size_in_bits>
	t_enum __cdecl read_enum(char const* name)
	{
		return static_cast<t_enum>(read_integer(name, size_in_bits));
	}

private:
	void __cdecl reset(long state);

public:
	void __cdecl set_data(byte* data, long data_length);
	void __cdecl skip(long bits_to_skip);
	bool __cdecl would_overflow(long size_in_bits) const;
	void __cdecl write_accumulator_to_memory(qword a1, long a2);
	void __cdecl write_bits_internal(void const* data, long size_in_bits);
	void __cdecl write_identifier(char const* identifier);
	void __cdecl write_point3d(char const* name, int32_point3d const* point, long axis_encoding_size_in_bits);
	void __cdecl write_quantized_real(char const* name, real* value, real min_value, real max_value, long size_in_bits, bool exact_midpoint, bool exact_endpoints);
	void __cdecl write_qword_internal(qword value, long size_in_bits);
	void __cdecl write_secure_address(char const* name, s_transport_secure_address const* address);
	void __cdecl write_string(char const* name, char const* _string, long max_string_size);
	void __cdecl write_string_utf8(char const* name, utf8 const* _string, long max_string_size);
	void __cdecl write_string_wchar(char const* name, wchar_t const* _string, long max_string_size);

	template<typename t_enum, long size_in_bits>
	void __cdecl write_enum(char const* name, t_enum value)
	{
		write_integer(name, value, size_in_bits);
	}

};
static_assert(sizeof(c_bitstream) == 0xA0);

