#include "dialogs/edit_text.hpp"

#include "input/input.hpp"

#include <string.h>

#define valid_edit_text(edit) ((edit) && (edit)->text && (edit)->text_length > 0 && short(strlen((edit)->text)) <= (edit)->text_length)

void __cdecl edit_text_new(edit_text* edit)
{
	ASSERT(valid_edit_text(edit));

	edit_text_selection_reset(edit);
}

void __cdecl edit_text_fix_selection(edit_text* edit)
{
	short text_len = short(strlen(edit->text));

	if (edit->cursor_selection_index <= 0)
		edit->cursor_selection_index = 0;

	short text_len11 = text_len;
	if (edit->cursor_selection_index < text_len)
		text_len11 = edit->cursor_selection_index;

	word selection_index8 = edit->selection_index8;
	bool v8 = edit->selection_index8 <= NONE;
	edit->cursor_selection_index = text_len;

	short v5 = NONE;
	if (!v8)
		v5 = selection_index8;
	if (v5 < text_len)
	{
		text_len = NONE;
		if (selection_index8 > NONE)
			text_len = selection_index8;
	}

	edit->selection_index8 = text_len;
	if (text_len11 == text_len)
		edit->selection_index8 = NONE;
}

void __cdecl edit_text_selection_reset(edit_text* edit)
{
	ASSERT(valid_edit_text(edit));

	edit_text_fix_selection(edit);
	edit->cursor_selection_index = static_cast<word>(strlen(edit->text));
	edit->selection_index8 = NONE;
}

byte __cdecl edit_text_get_selection_indices(edit_text* edit, short* out_selection_index0, short* out_selection_index1)
{
	ASSERT(valid_edit_text(edit));

	edit_text_fix_selection(edit);

	if (edit->selection_index8 == NONE)
		return 0;

	*out_selection_index0 = (edit->selection_index8 <= edit->cursor_selection_index) ? edit->selection_index8 : edit->cursor_selection_index;
	*out_selection_index1 = (edit->selection_index8 <= edit->cursor_selection_index) ? edit->cursor_selection_index : edit->selection_index8;

	return 1;
}

void __cdecl edit_text_handle_key(edit_text* edit, s_key_state const* key)
{
	ASSERT(valid_edit_text(edit));

	// #TODO: implement

	edit_text_fix_selection(edit);

	e_key_code key_code = key->key_code;
	if (key->key_type == _key_type_down && key_code == _key_code_backspace)
	{
		edit->text[edit->cursor_selection_index - 1] = 0;
	}
}

