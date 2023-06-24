#include "game/game_engine_infection.hpp"

#include "memory/byte_swapping.hpp"

REFERENCE_DECLARE(0x050D9F84, c_game_engine_infection_variant*, infection_variant);

void c_game_engine_infection_variant::byteswap()
{
	c_game_engine_base_variant::byteswap();

	bswap_word_inplace(m_safe_haven_movement_time);
	m_zombie_traits.byteswap();
	m_first_zombie_traits.byteswap();
	m_safe_haven_defender_traits.byteswap();
	m_last_human_traits.byteswap();

	ASSERT(array_is_zeroed(m_pad1));
}

void c_game_engine_infection_variant::set(c_game_engine_infection_variant const* variant, bool force)
{
	ASSERT(variant != NULL);

	c_game_engine_base_variant::set(variant, force);

	get_miscellaneous_options_writeable()->set_teams_enabled(false);
	set_respawn_on_haven_move(variant->get_respawn_on_haven_move());
	set_safe_havens(variant->get_safe_havens());
	set_next_zombie(variant->get_next_zombie());
	set_initial_zombie_count(variant->get_initial_zombie_count());
	set_safe_haven_movement_time(variant->get_safe_haven_movement_time());
	set_zombie_kill_points(variant->get_zombie_kill_points());
	set_infection_points(variant->get_infection_points());
	set_safe_haven_arrival_points(variant->get_safe_haven_arrival_points());
	set_suicide_points(variant->get_suicide_points());
	set_betrayal_points(variant->get_betrayal_points());
	set_last_man_bonus_points(variant->get_last_man_bonus_points());
	set_zombie_traits(variant->get_zombie_traits(), force);
	set_first_zombie_traits(variant->get_first_zombie_traits(), force);
	set_safe_haven_defender_traits(variant->get_safe_haven_defender_traits(), force);
	set_last_human_traits(variant->get_last_human_traits(), force);

	zero_array(m_pad1);
}

//void c_game_engine_infection_variant::set(s_game_engine_infection_variant_definition const* definition, bool force)
//{
//}

void c_game_engine_infection_variant::encode_to_mcc(c_bitstream* packet) const
{
	c_game_engine_base_variant::encode_to_mcc(packet);

	bool respawn_on_haven_move = get_respawn_on_haven_move();
	e_infection_safe_havens_settings safe_havens = get_safe_havens();
	e_infection_next_zombie_settings next_zombie = get_next_zombie();
	e_infection_initial_zombie_count_settings initial_zombie_count = get_initial_zombie_count();
	short safe_haven_movement_time = get_safe_haven_movement_time();
	char zombie_kill_points = get_zombie_kill_points();
	char infection_points = get_infection_points();
	char safe_haven_arrival_points = get_safe_haven_arrival_points();
	char suicide_points = get_suicide_points();
	char betrayal_points = get_betrayal_points();
	char last_man_bonus_points = get_last_man_bonus_points();

	packet->write_bool("infection-respawn-on-haven-move", respawn_on_haven_move);
	packet->write_integer("infection-safe-havens", safe_havens, 2);
	packet->write_integer("infection-next-zombie", next_zombie, 2);
	packet->write_integer("infection-initial-zombie-count", initial_zombie_count, 5);
	packet->write_integer("infection-safe-haven-movement-time", safe_haven_movement_time, 7);
	packet->write_signed_integer("infection-zombie-kill-points", zombie_kill_points, 5);
	packet->write_signed_integer("infection-infection-points", infection_points, 5);
	packet->write_signed_integer("infection-safe-haven-arrival-points", safe_haven_arrival_points, 5);
	packet->write_signed_integer("infection-suicide-points", suicide_points, 5);
	packet->write_signed_integer("infection-betrayal-points", betrayal_points, 5);
	packet->write_signed_integer("infection-last-man-bonus-points", last_man_bonus_points, 5);
	get_zombie_traits()->encode_to_mcc(packet);
	get_first_zombie_traits()->encode_to_mcc(packet);
	get_safe_haven_defender_traits()->encode_to_mcc(packet);
	get_last_human_traits()->encode_to_mcc(packet);
}

void c_game_engine_infection_variant::decode_from_mcc(c_bitstream* packet)
{
	c_game_engine_base_variant::decode_from_mcc(packet);

	bool respawn_on_haven_move = packet->read_bool("infection-respawn-on-haven-move");
	e_infection_safe_havens_settings safe_havens = packet->read_enum<e_infection_safe_havens_settings, 2>("infection-safe-havens");
	e_infection_next_zombie_settings next_zombie = packet->read_enum<e_infection_next_zombie_settings, 2>("infection-next-zombie");
	e_infection_initial_zombie_count_settings initial_zombie_count = packet->read_enum<e_infection_initial_zombie_count_settings, 5>("infection-initial-zombie-count");
	short safe_haven_movement_time = static_cast<short>(packet->read_integer("infection-safe-haven-movement-time", 7));
	char zombie_kill_points = static_cast<char>(packet->read_signed_integer("infection-zombie-kill-points", 5));
	char infection_points = static_cast<char>(packet->read_signed_integer("infection-infection-points", 5));
	char safe_haven_arrival_points = static_cast<char>(packet->read_signed_integer("infection-safe-haven-arrival-points", 5));
	char suicide_points = static_cast<char>(packet->read_signed_integer("infection-suicide-points", 5));
	char betrayal_points = static_cast<char>(packet->read_signed_integer("infection-betrayal-points", 5));
	char last_man_bonus_points = static_cast<char>(packet->read_signed_integer("infection-last-man-bonus-points", 5));
	get_zombie_traits()->encode_to_mcc(packet);
	get_first_zombie_traits()->encode_to_mcc(packet);
	get_safe_haven_defender_traits()->encode_to_mcc(packet);
	get_last_human_traits()->encode_to_mcc(packet);

	set_respawn_on_haven_move(respawn_on_haven_move);
	set_safe_havens(safe_havens);
	set_next_zombie(next_zombie);
	set_initial_zombie_count(initial_zombie_count);
	set_safe_haven_movement_time(safe_haven_movement_time);
	set_zombie_kill_points(zombie_kill_points);
	set_infection_points(infection_points);
	set_safe_haven_arrival_points(safe_haven_arrival_points);
	set_suicide_points(suicide_points);
	set_betrayal_points(betrayal_points);
	set_last_man_bonus_points(last_man_bonus_points);
}

bool c_game_engine_infection_variant::get_respawn_on_haven_move() const
{
	return m_variant_flags.test(_infection_variant_flags_respawn_on_haven_move);
}

void c_game_engine_infection_variant::set_respawn_on_haven_move(bool respawn_on_haven_move)
{
	return m_variant_flags.set(_infection_variant_flags_respawn_on_haven_move, respawn_on_haven_move);
}

e_infection_safe_havens_settings c_game_engine_infection_variant::get_safe_havens() const
{
	return m_safe_havens;
}

void c_game_engine_infection_variant::set_safe_havens(e_infection_safe_havens_settings safe_havens)
{
	if (!VALID_INDEX(safe_havens, k_infection_safe_havens_settings))
	{
		c_console::write_line("game_engine:infection: invalid safe_havens setting '%d' outside range '[0, %d)'!", safe_havens, k_infection_safe_havens_settings);

		m_safe_havens = k_infection_safe_havens_settings_default;
	}
	else
	{
		m_safe_havens = safe_havens;
	}
}

e_infection_next_zombie_settings c_game_engine_infection_variant::get_next_zombie() const
{
	return m_next_zombie;
}

void c_game_engine_infection_variant::set_next_zombie(e_infection_next_zombie_settings next_zombie)
{
	if (!VALID_INDEX(next_zombie, k_infection_next_zombie_settings))
	{
		c_console::write_line("game_engine:infection: invalid next_zombie setting '%d' outside range '[0, %d)'!", next_zombie, k_infection_next_zombie_settings);

		m_next_zombie = k_infection_next_zombie_settings_default;
	}
	else
	{
		m_next_zombie = next_zombie;
	}
}

e_infection_initial_zombie_count_settings c_game_engine_infection_variant::get_initial_zombie_count() const
{
	return m_initial_zombie_count;
}

void c_game_engine_infection_variant::set_initial_zombie_count(e_infection_initial_zombie_count_settings initial_zombie_count)
{
	if (!VALID_INDEX(initial_zombie_count, k_infection_initial_zombie_count_settings))
	{
		c_console::write_line("game_engine:infection: invalid initial_zombie_count setting '%d' outside range '[0, %d)'!", initial_zombie_count, k_infection_initial_zombie_count_settings);

		m_initial_zombie_count = k_infection_initial_zombie_count_settings_default;
	}
	else
	{
		m_initial_zombie_count = initial_zombie_count;
	}
}

short c_game_engine_infection_variant::get_safe_haven_movement_time() const
{
	return m_safe_haven_movement_time;
}

void c_game_engine_infection_variant::set_safe_haven_movement_time(short safe_haven_movement_time)
{
	if (!VALID_INDEX(safe_haven_movement_time, 120))
	{
		c_console::write_line("game_engine:infection: invalid safe_haven_movement_time setting '%d' outside range '[%d, %d]'!", safe_haven_movement_time, 0, 120);

		m_safe_haven_movement_time = 30;
	}
	else
	{
		m_safe_haven_movement_time = safe_haven_movement_time;
	}
}

char c_game_engine_infection_variant::get_zombie_kill_points() const
{
	return m_zombie_kill_points;
}

void c_game_engine_infection_variant::set_zombie_kill_points(char zombie_kill_points)
{
	if (!VALID_INDEX(zombie_kill_points + 10, 20))
	{
		c_console::write_line("game_engine:infection: invalid zombie_kill_points setting '%d' outside range '[%d, %d]'!", zombie_kill_points, -10, 10);

		m_zombie_kill_points = 1;
	}
	else
	{
		m_zombie_kill_points = zombie_kill_points;
	}
}

char c_game_engine_infection_variant::get_infection_points() const
{
	return m_infection_points;
}

void c_game_engine_infection_variant::set_infection_points(char infection_points)
{
	if (!VALID_INDEX(infection_points + 10, 20))
	{
		c_console::write_line("game_engine:infection: invalid infection_points setting '%d' outside range '[%d, %d]'!", infection_points, -10, 10);

		m_infection_points = 0;
	}
	else
	{
		m_infection_points = infection_points;
	}
}

char c_game_engine_infection_variant::get_safe_haven_arrival_points() const
{
	return m_safe_haven_arrival_points;
}

void c_game_engine_infection_variant::set_safe_haven_arrival_points(char safe_haven_arrival_points)
{
	if (!VALID_INDEX(safe_haven_arrival_points + 10, 20))
	{
		c_console::write_line("game_engine:infection: invalid safe_haven_arrival_points setting '%d' outside range '[%d, %d]'!", safe_haven_arrival_points, -10, 10);

		m_safe_haven_arrival_points = 0;
	}
	else
	{
		m_safe_haven_arrival_points = safe_haven_arrival_points;
	}
}

char c_game_engine_infection_variant::get_suicide_points() const
{
	return m_suicide_points;
}

void c_game_engine_infection_variant::set_suicide_points(char suicide_points)
{
	if (!VALID_INDEX(suicide_points + 10, 20))
	{
		c_console::write_line("game_engine:infection: invalid suicide_points setting '%d' outside range '[%d, %d]'!", suicide_points, -10, 10);

		m_suicide_points = -1;
	}
	else
	{
		m_suicide_points = suicide_points;
	}
}

char c_game_engine_infection_variant::get_betrayal_points() const
{
	return m_betrayal_points;
}

void c_game_engine_infection_variant::set_betrayal_points(char betrayal_points)
{
	if (!VALID_INDEX(betrayal_points + 10, 20))
	{
		c_console::write_line("game_engine:infection: invalid betrayal_points setting '%d' outside range '[%d, %d]'!", betrayal_points, -10, 10);

		m_betrayal_points = -1;
	}
	else
	{
		m_betrayal_points = betrayal_points;
	}
}

char c_game_engine_infection_variant::get_last_man_bonus_points() const
{
	return m_last_man_bonus_points;
}

void c_game_engine_infection_variant::set_last_man_bonus_points(char last_man_bonus_points)
{
	if (!VALID_INDEX(last_man_bonus_points + 10, 20))
	{
		c_console::write_line("game_engine:infection: invalid last_man_bonus_points setting '%d' outside range '[%d, %d]'!", last_man_bonus_points, -10, 10);

		m_last_man_bonus_points = 0;
	}
	else
	{
		m_last_man_bonus_points = last_man_bonus_points;
	}
}

c_player_traits* c_game_engine_infection_variant::get_zombie_traits_writeable()
{
	return &m_zombie_traits;
}

c_player_traits const* c_game_engine_infection_variant::get_zombie_traits() const
{
	return &m_zombie_traits;
}

void c_game_engine_infection_variant::set_zombie_traits(c_player_traits const* traits, bool force)
{
	m_zombie_traits.set(traits, force);
}

c_player_traits* c_game_engine_infection_variant::get_first_zombie_traits_writeable()
{
	return &m_first_zombie_traits;
}

c_player_traits const* c_game_engine_infection_variant::get_first_zombie_traits() const
{
	return &m_first_zombie_traits;
}

void c_game_engine_infection_variant::set_first_zombie_traits(c_player_traits const* traits, bool force)
{
	m_first_zombie_traits.set(traits, force);
}

c_player_traits* c_game_engine_infection_variant::get_safe_haven_defender_traits_writeable()
{
	return &m_safe_haven_defender_traits;
}

c_player_traits const* c_game_engine_infection_variant::get_safe_haven_defender_traits() const
{
	return &m_safe_haven_defender_traits;
}

void c_game_engine_infection_variant::set_safe_haven_defender_traits(c_player_traits const* traits, bool force)
{
	m_safe_haven_defender_traits.set(traits, force);
}

c_player_traits* c_game_engine_infection_variant::get_last_human_traits_writeable()
{
	return &m_last_human_traits;
}

c_player_traits const* c_game_engine_infection_variant::get_last_human_traits() const
{
	return &m_last_human_traits;
}

void c_game_engine_infection_variant::set_last_human_traits(c_player_traits const* traits, bool force)
{
	m_last_human_traits.set(traits, force);
}

void c_infection_engine::dump_settings(s_file_reference* file) const
{
	ASSERT(file != NULL);

	c_game_engine::dump_settings(file);

}

