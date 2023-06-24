#include "game/game_engine_sandbox.hpp"

#include "memory/byte_swapping.hpp"

REFERENCE_DECLARE(0x0240648C, c_game_engine_sandbox_variant*, sandbox_variant);

void c_game_engine_sandbox_variant::byteswap()
{
	c_game_engine_base_variant::byteswap();

	bswap_word_inplace(m_respawn_time);
	m_player_traits.byteswap();
}

void c_game_engine_sandbox_variant::set(c_game_engine_sandbox_variant const* variant, bool force)
{
	ASSERT(variant != NULL);

	c_game_engine_base_variant::set(variant, force);

	set_edit_mode(variant->get_edit_mode());
	set_respawn_time(variant->get_respawn_time());
	set_open_channel_voice(variant->get_open_channel_voice());
	set_player_traits(variant->get_player_traits(), force);
}

//void c_game_engine_sandbox_variant::set(s_game_engine_sandbox_variant_definition const* definition, bool force)
//{
//}

void c_game_engine_sandbox_variant::encode_to_mcc(c_bitstream* packet) const
{
	c_game_engine_base_variant::encode_to_mcc(packet);

	bool open_channel_voice = get_open_channel_voice();
	e_sandbox_edit_mode_settings edit_mode = get_edit_mode();
	short respawn_time = get_respawn_time();

	packet->write_bool("sandbox-open-channel-voice", open_channel_voice);
	packet->write_integer("sandbox-edit-mode", edit_mode, 2);
	packet->write_integer("sandbox-respawn-time", respawn_time, 6);
	get_player_traits()->encode_to_mcc(packet);
}

void c_game_engine_sandbox_variant::decode_from_mcc(c_bitstream* packet)
{
	get_miscellaneous_options_writeable()->set_round_limit(1);
	get_miscellaneous_options_writeable()->set_round_time_limit_minutes(0);

	c_game_engine_base_variant::decode_from_mcc(packet);

	bool open_channel_voice = packet->read_bool("sandbox-open-channel-voice");
	e_sandbox_edit_mode_settings edit_mode = packet->read_enum<e_sandbox_edit_mode_settings, 2>("sandbox-edit-mode");
	short respawn_time = static_cast<short>(packet->read_integer("sandbox-respawn-time", 6));
	get_player_traits_writeable()->decode_from_mcc(packet);

	set_edit_mode(edit_mode);
	set_respawn_time(respawn_time);
}

bool c_game_engine_sandbox_variant::get_open_channel_voice() const
{
	return m_variant_flags.test(_sandbox_variant_flags_open_channel_voice);
}

void c_game_engine_sandbox_variant::set_open_channel_voice(bool open_channel_voice)
{
	m_variant_flags.set(_sandbox_variant_flags_open_channel_voice, open_channel_voice);
}

e_sandbox_edit_mode_settings c_game_engine_sandbox_variant::get_edit_mode() const
{
	return m_edit_mode;
}

void c_game_engine_sandbox_variant::set_edit_mode(e_sandbox_edit_mode_settings edit_mode)
{
	if (!VALID_INDEX(edit_mode, k_sandbox_edit_mode_settings))
	{
		c_console::write_line("game_engine:sandbox: invalid edit_mode setting '%d' outside range '[0, %d)'!", edit_mode, k_sandbox_edit_mode_settings);

		m_edit_mode = k_sandbox_edit_mode_settings_default;
	}
	else
	{
		m_edit_mode = edit_mode;
	}
}

short c_game_engine_sandbox_variant::get_respawn_time() const
{
	return m_respawn_time;
}

void c_game_engine_sandbox_variant::set_respawn_time(short respawn_time)
{
	if (!VALID_INDEX(respawn_time, k_sandbox_respawn_times))
	{
		c_console::write_line("game_engine:sandbox: invalid respawn_time setting '%d' outside range '[%d, %d]'!", respawn_time, _sandbox_respawn_time_instant, _sandbox_respawn_time_60_seconds);

		m_respawn_time = k_sandbox_respawn_times_default;
	}
	else
	{
		m_respawn_time = respawn_time;
	}
}

c_player_traits* c_game_engine_sandbox_variant::get_player_traits_writeable()
{
	return &m_player_traits;
}

c_player_traits const* c_game_engine_sandbox_variant::get_player_traits() const
{
	return &m_player_traits;
}

void c_game_engine_sandbox_variant::set_player_traits(c_player_traits const* traits, bool force)
{
	m_player_traits.set(traits, force);
}

