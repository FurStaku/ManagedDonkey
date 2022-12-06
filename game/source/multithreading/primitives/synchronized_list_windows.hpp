#pragma once

const long k_synchronized_list_alignment_bits = 4;

// SINGLE_LIST_ENTRY
struct s_synchronized_list_entry
{
	s_synchronized_list_entry* next;
};
static_assert(sizeof(s_synchronized_list_entry) == 0x4);

// SLIST_HEADER
struct s_synchronized_list_header
{
	union
	{
		unsigned long long alignment;
		struct
		{
			s_synchronized_list_entry next;
			unsigned short depth;
			unsigned short sequence;
		} s;
	};
};
static_assert(sizeof(s_synchronized_list_header) == 0x8);

extern void __cdecl synchronized_list_initialize(s_synchronized_list_header* header);
extern void __cdecl synchronized_list_entry_clear(s_synchronized_list_entry* entry);
extern s_synchronized_list_entry* __cdecl synchronized_list_entry_next(s_synchronized_list_entry* entry);
extern s_synchronized_list_entry* __cdecl synchronized_list_entry_set(s_synchronized_list_entry* entry, s_synchronized_list_entry* next_entry);
extern void __cdecl synchronized_list_push(s_synchronized_list_header* header, s_synchronized_list_entry* entry);
extern void __cdecl synchronized_list_push_multiple(s_synchronized_list_header* header, long entry_count, s_synchronized_list_entry** entries);
extern s_synchronized_list_entry* __cdecl synchronized_list_pop(s_synchronized_list_header* header);
extern s_synchronized_list_entry* __cdecl synchronized_list_flush(s_synchronized_list_header* header);
extern long __cdecl synchronized_list_get_count(struct s_synchronized_list_header* header);

