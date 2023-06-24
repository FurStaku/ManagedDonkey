#include "game/game_engine_variant.hpp"

#include "game/game_engine.hpp"
#include "game/game_options.hpp"
#include "memory/byte_swapping.hpp"

char const* k_game_engine_variant_names[k_game_engine_type_count] =
{
	"base",
	"ctf",
	"slayer",
	"oddball",
	"king",
	"sandbox",
	"vip",
	"juggernaut",
	"territories",
	"assault",
	"infection"
};

const char* game_engine_variant_get_name(long game_engine_index)
{
	if (game_engine_index < _game_engine_base_variant || game_engine_index >= k_game_engine_type_count)
		return "<invalid 'game_engine_index'>";

	return k_game_engine_variant_names[game_engine_index];
}

void c_game_engine_base_variant::encode_to_mcc(c_bitstream* packet) const
{
	m_metadata.encode_to_mcc(packet);

	bool built_in = get_built_in();

	packet->write_bool("variant-built-in", built_in);

	get_miscellaneous_options()->encode_to_mcc(packet);
	get_respawn_options()->encode_to_mcc(packet);
	get_social_options()->encode_to_mcc(packet);
	get_map_override_options()->encode_to_mcc(packet);

	short team_scoring_method = get_team_scoring_method();

	packet->write_integer("team-scoring-method", team_scoring_method, 3);
}

void c_game_engine_base_variant::decode_from_mcc(c_bitstream* packet)
{
	initialize();
	m_metadata.decode_from_mcc(packet);

	bool built_in = packet->read_bool("variant-built-in");

	get_miscellaneous_options_writeable()->decode_from_mcc(packet);
	get_respawn_options_writeable()->decode_from_mcc(packet);
	get_social_options_writeable()->decode_from_mcc(packet);
	get_map_override_options_writeable()->decode_from_mcc(packet);

	short team_scoring_method = static_cast<short>(packet->read_integer("team-scoring-method", 3));

	set_built_in(built_in);

	set_team_scoring_method(team_scoring_method);
}

void c_game_engine_base_variant::byteswap()
{
	m_metadata.byteswap();
	m_miscellaneous_options.byteswap();
	m_respawn_options.byteswap();
	m_social_options.byteswap();
	m_map_override_options.byteswap();
	bswap_word_inplace(m_flags);
	bswap_word_inplace(m_team_scoring_method);
}

void c_game_engine_base_variant::set(c_game_engine_base_variant const* variant, bool force)
{
	ASSERT(variant != NULL);

	set_name(variant->get_name());
	set_description(variant->get_description());
	m_miscellaneous_options.set(variant->get_miscellaneous_options(), force);
	m_respawn_options.set(variant->get_respawn_options(), force);
	m_social_options.set(variant->get_social_options(), force);
	m_map_override_options.set(variant->get_map_override_options(), force);
	set_team_scoring_method(variant->get_team_scoring_method());
}

//void c_game_engine_base_variant::set(s_game_engine_base_variant_definition const* definition, bool force)
//{
//}

void c_game_engine_base_variant::get_game_engine_name(c_static_wchar_string<1024>* out_game_engine_name) const
{
	game_engine_get_multiplayer_string(get_game_engine_name_string_id(), out_game_engine_name);
}

void c_game_engine_base_variant::get_game_engine_description(c_static_wchar_string<1024>* game_engine_description) const
{
	game_engine_get_multiplayer_string(get_game_engine_default_description_string_id(), game_engine_description);
}

char const* c_game_engine_base_variant::get_name() const
{
	return m_name;
}

void c_game_engine_base_variant::set_name(char const* name)
{
	csstrnzcpy(m_name, name, 32);
}

char const* c_game_engine_base_variant::get_description() const
{
	return m_metadata.description;
}

void c_game_engine_base_variant::set_description(char const* description)
{
	csstrnzcpy(m_metadata.description, description, 128);
}

c_game_engine_miscellaneous_options* c_game_engine_base_variant::get_miscellaneous_options_writeable()
{
	return &m_miscellaneous_options;
}

c_game_engine_miscellaneous_options const* c_game_engine_base_variant::get_miscellaneous_options() const
{
	return &m_miscellaneous_options;
}

c_game_engine_respawn_options* c_game_engine_base_variant::get_respawn_options_writeable()
{
	return &m_respawn_options;
}

c_game_engine_respawn_options const* c_game_engine_base_variant::get_respawn_options() const
{
	return &m_respawn_options;
}

c_game_engine_social_options* c_game_engine_base_variant::get_social_options_writeable()
{
	return &m_social_options;
}

c_game_engine_social_options const* c_game_engine_base_variant::get_social_options() const
{
	return &m_social_options;
}

c_game_engine_map_override_options* c_game_engine_base_variant::get_map_override_options_writeable()
{
	return &m_map_override_options;
}

c_game_engine_map_override_options const* c_game_engine_base_variant::get_map_override_options() const
{
	return &m_map_override_options;
}

bool c_game_engine_base_variant::get_built_in() const
{
	return m_flags.test(_base_variant_flags_built_in);
}

void c_game_engine_base_variant::set_built_in(bool built_in)
{
	m_flags.set(_base_variant_flags_built_in, built_in);
}

short c_game_engine_base_variant::get_team_scoring_method() const
{
	return m_team_scoring_method;
}

void c_game_engine_base_variant::set_team_scoring_method(short team_scoring_method)
{
	m_team_scoring_method = team_scoring_method;
}

c_game_variant* __cdecl build_default_game_variant(c_game_variant* game_variant, e_game_engine_type game_engine_index)
{
	return INVOKE(0x005721C0, build_default_game_variant, game_variant, game_engine_index);
}

bool __cdecl game_engine_tag_defined_variant_get_built_in_variant(e_game_engine_type game_engine_index, long variant_index, c_game_variant* game_variant)
{
	return INVOKE(0x00572270, game_engine_tag_defined_variant_get_built_in_variant, game_engine_index, variant_index, game_variant);
}

void __cdecl game_engine_variant_describe_invalidity(c_game_variant const* game_variant)
{
	INVOKE(0x00572830, game_engine_variant_describe_invalidity, game_variant);
}

bool __cdecl game_engine_variant_is_valid(c_game_variant const* game_variant)
{
	return INVOKE(0x005728B0, game_engine_variant_is_valid, game_variant);
}

bool game_engine_variant_validate(c_game_variant* game_variant)
{
	return INVOKE(0x00572920, game_engine_variant_validate, game_variant);
}

