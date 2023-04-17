#pragma once

#include "cseries/cseries.hpp"

#define MAX_INDEX_WITH_BITS(VALUE) MASK(VALUE)
#define LONG_DESIGNATOR_PRIMARY_INDEX_BITS(SECONDARY_INDEX_BITS, HAS_FLAG) (LONG_BITS - (SECONDARY_INDEX_BITS))

template<long k_secondary_index_bits, bool k_has_flag>
struct c_long_designator
{
	static long const k_primary_index_bits = LONG_DESIGNATOR_PRIMARY_INDEX_BITS(k_secondary_index_bits, k_has_flag);
	static long const k_max_primary_index_with_bits = MAX_INDEX_WITH_BITS(k_primary_index_bits);
	static long const k_max_secondary_index_with_bits = MAX_INDEX_WITH_BITS(k_secondary_index_bits);

public:
	long get_primary_index() const
	{
		return m_value & k_max_primary_index_with_bits;
	}

	long get_secondary_index() const
	{
		return get_secondary_index_internal();
	}

	void set_primary_index(long new_primary_index)
	{
		ASSERT(IN_RANGE_INCLUSIVE(new_primary_index, 0, MAX_INDEX_WITH_BITS(LONG_DESIGNATOR_PRIMARY_INDEX_BITS(k_secondary_index_bits, k_has_flag))));

		set_designator_internal(new_primary_index, get_secondary_index_internal(), get_flag_internal());
	}

	void set_secondary_index(long new_secondary_index)
	{
		ASSERT(IN_RANGE_INCLUSIVE(new_secondary_index, 0, MAX_INDEX_WITH_BITS(LONG_DESIGNATOR_PRIMARY_INDEX_BITS(k_secondary_index_bits, k_has_flag))));

		set_designator_internal(get_primary_index(), new_secondary_index, get_flag_internal());
	}

	long get_secondary_index_internal() const
	{
		return (m_value & (k_max_secondary_index_with_bits << k_primary_index_bits)) >> k_primary_index_bits;
	}

	bool get_flag_internal() const
	{
		return TEST_BIT(m_value, 31); // spoopy value
	}

	void set_designator_internal(long new_primary_index, long new_secondary_index, bool has_flag)
	{
		m_value = new_primary_index & k_max_primary_index_with_bits | (new_secondary_index << k_primary_index_bits);
	}

protected:
	long m_value;
};
static_assert(sizeof(c_long_designator<3, false>) == 0x4);

enum e_tag_resource_fixup_type
{
	_tag_resource_fixup_value = 0,
	_tag_resource_fixup_control_offset,

	_tag_resource_fixup_unknown2,
	_tag_resource_fixup_unknown3,
	_tag_resource_fixup_unknown4,
	_tag_resource_fixup_unknown5,
	_tag_resource_fixup_unknown6,

	k_tag_resource_fixup_type_count
};

struct c_tag_resource_fixup
{
	static long const k_tag_resource_fixup_type_bits = bit_count(k_tag_resource_fixup_type_count);
	static long const k_maximum_resource_fixup_value = MAX_INDEX_WITH_BITS(LONG_DESIGNATOR_PRIMARY_INDEX_BITS(k_tag_resource_fixup_type_bits, false));
	
public:
	dword get_fixup_value() const
	{
		dword fixup_value = designator.get_primary_index();
		ASSERT(IN_RANGE_INCLUSIVE(fixup_value, 0, k_maximum_resource_fixup_value));

		return fixup_value;
	}

	e_tag_resource_fixup_type get_type() const
	{
		return static_cast<e_tag_resource_fixup_type>(designator.get_secondary_index());
	}

	void set_fixup_value(dword fixup_value)
	{
		designator.set_primary_index(static_cast<long>(fixup_value));
	}

	void set_type(e_tag_resource_fixup_type type)
	{
		designator.set_secondary_index(static_cast<long>(type));
	}

protected:
	c_long_designator<k_tag_resource_fixup_type_bits, false> designator;
};
static_assert(sizeof(c_tag_resource_fixup) == sizeof(c_long_designator<3, false>));

