#pragma once

#include "interface/gui_selected_items.hpp"

enum e_hopper_category_id;

struct s_hopper_information
{
	wchar_t name[32];
	uns16 hopper_identifier;
	e_hopper_category_id category_identifier;
	uns8 presence_hopper_identifier;
	int32 image_index;
	bool is_visible;
	bool is_playable;
	bool is_ranked;
	bool has_xp_penalty;
};
static_assert(sizeof(s_hopper_information) == 0x54);
static_assert(0x00 == OFFSETOF(s_hopper_information, name));
static_assert(0x40 == OFFSETOF(s_hopper_information, hopper_identifier));
static_assert(0x44 == OFFSETOF(s_hopper_information, category_identifier));
static_assert(0x48 == OFFSETOF(s_hopper_information, presence_hopper_identifier));
static_assert(0x4C == OFFSETOF(s_hopper_information, image_index));
static_assert(0x50 == OFFSETOF(s_hopper_information, is_visible));
static_assert(0x51 == OFFSETOF(s_hopper_information, is_playable));
static_assert(0x52 == OFFSETOF(s_hopper_information, is_ranked));
static_assert(0x53 == OFFSETOF(s_hopper_information, has_xp_penalty));

class c_gui_hopper_selected_item :
	public c_gui_selected_item
{
public:

//protected:
	s_hopper_information m_hopper_information;
};
static_assert(sizeof(c_gui_hopper_selected_item) == sizeof(c_gui_selected_item) + 0x58);
static_assert(0x190 == OFFSETOF(c_gui_hopper_selected_item, m_hopper_information));


