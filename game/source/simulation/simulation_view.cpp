#include "simulation/simulation_view.hpp"

//.text:00465D00 ; void c_simulation_view::attach_observer_channel(c_network_observer*, int32, s_transport_secure_address const*)
//.text:00465EC0 ; void c_simulation_view::attach_to_world(c_simulation_world*)
//.text:00465EE0 ; bool c_simulation_view::client_in_game() const
//.text:00465F00 ; bool c_simulation_view::client_join_is_finished() const
//.text:00465F50 ; void c_simulation_view::destroy_view()
//.text:00465F60 ; void c_simulation_view::detach_from_world()
//.text:00465FC0 ; void c_simulation_view::detach_observer_channel()
//.text:00466100 ; void c_simulation_view::dispatch_synchronous_actions(uint32, c_static_array<player_action, 4> const&)
//.text:00466230 ; void c_simulation_view::dispatch_synchronous_playback_control(e_network_synchronous_playback_control, int32, int32)
//.text:004662A0 ; void c_simulation_view::dispatch_synchronous_update(struct simulation_update const*, s_simulation_update_metadata const*)
//.text:00466350 ; void c_simulation_view::distributed_join_abort()
//.text:00466370 ; static void c_simulation_view::distributed_join_complete()
//.text:00466380 ; bool c_simulation_view::distributed_join_in_progress() const
//.text:004663F0 ; bool c_simulation_view::distributed_join_initiate()
//.text:00466400 ; bool c_simulation_view::established() const
//.text:00466420 ; bool c_simulation_view::establishment_add_cache_file_signature(int32*, int32, uint8*) const
//.text:00466480 ; bool c_simulation_view::establishment_verify_cache_file_signature(int32, uint8 const*) const
//.text:00466500 ; void c_simulation_view::failed_to_join()
//.text:00466590 ; void c_simulation_view::force_unacknowledge_player(int32)
//.text:004665B0 ; uint32 c_simulation_view::get_acknowledged_player_mask() const
//.text:004665C0 ; c_replication_control_view* c_simulation_view::get_control_view()

e_simulation_view_type c_simulation_view::view_type() const
{
	return INVOKE_CLASS_MEMBER(0x00466600, c_simulation_view, view_type);
}

//.text:00466620 ; int32 c_simulation_view::get_machine_index() const
//.text:00466680 ; void c_simulation_view::get_statistics(s_simulation_view_statistics*)
//.text:00466700 ; c_simulation_view::get_machine_identifier?

char const* c_simulation_view::get_view_description() const
{
	return INVOKE_CLASS_MEMBER(0x00466710, c_simulation_view, get_view_description);

	//return NULL;
}

int32 c_simulation_view::get_view_establishment_identifier() const
{
	return INVOKE_CLASS_MEMBER(0x00466720, c_simulation_view, get_view_establishment_identifier);

	//return m_view_establishment_identifier;
}

e_simulation_view_establishment_mode c_simulation_view::get_view_establishment_mode() const
{
	return INVOKE_CLASS_MEMBER(0x00466730, c_simulation_view, get_view_establishment_mode);

	//return m_view_establishment_mode;
}

//.text:00466740 ; void c_simulation_view::go_out_of_sync()

bool c_simulation_view::handle_distributed_game_results(int32 message_establishment_identifier, int32 incremental_update_number, s_game_results_incremental_update const* incremental_update)
{
	return INVOKE_CLASS_MEMBER(0x004667A0, c_simulation_view, handle_distributed_game_results, message_establishment_identifier, incremental_update_number, incremental_update);

	//ASSERT(exists());
	//ASSERT(m_view_type == _simulation_view_type_distributed_to_remote_authority);
	//ASSERT(m_distributed_view);
	//
	//if (message_establishment_identifier == m_view_establishment_identifier)
	//{
	//	return m_distributed_view->m_control_view.m_game_results_replicator.handle_update();
	//}
	//
	//if (message_establishment_identifier >= m_view_establishment_identifier)
	//{
	//	event(_event_warning, "networking:simulation:view: failing to handle incremental game results (message establishment identifier [%d] > current [%d])",
	//		message_establishment_identifier,
	//		m_view_establishment_identifier);
	//	return false;
	//}
	//
	//
	//event(_event_message, "networking:simulation:view: ignoring incremental game results (message establishment identifier %d < current %d)",
	//	message_establishment_identifier,
	//	m_view_establishment_identifier);
	//return true;
}

bool c_simulation_view::handle_player_acknowledge(uint32 player_valid_mask, uint32 player_in_game_mask, s_player_identifier const* player_identifiers)
{
	return INVOKE_CLASS_MEMBER(0x00466820, c_simulation_view, handle_player_acknowledge, player_valid_mask, player_in_game_mask, player_identifiers);
}

bool c_simulation_view::handle_remote_establishment(e_simulation_view_establishment_mode establishment_mode, int32 establishment_identifier, int32 signature_size, uint8 const* signature_data)
{
	return INVOKE_CLASS_MEMBER(0x00466940, c_simulation_view, handle_remote_establishment, establishment_mode, establishment_identifier, signature_size, signature_data);
}

bool c_simulation_view::handle_synchronous_acknowledge(int32 current_update_number)
{
	return INVOKE_CLASS_MEMBER(0x00466B10, c_simulation_view, handle_synchronous_acknowledge, current_update_number);
}

bool c_simulation_view::handle_synchronous_actions(int32 action_number, int32 current_action_number, uint32 user_flags, player_action const* actions)
{
	return INVOKE_CLASS_MEMBER(0x00466B30, c_simulation_view, handle_synchronous_actions, action_number, current_action_number, user_flags, actions);
}

bool c_simulation_view::handle_synchronous_gamestate(s_network_message_synchronous_gamestate const* synchronous_gamestate, void const* chunk_data)
{
	return INVOKE_CLASS_MEMBER(0x00466BB0, c_simulation_view, handle_synchronous_gamestate, synchronous_gamestate, chunk_data);
}

bool c_simulation_view::handle_synchronous_playback_control(e_network_synchronous_playback_control type, int32 identifier, int32 update_number)
{
	return INVOKE_CLASS_MEMBER(0x00466D10, c_simulation_view, handle_synchronous_playback_control, type, identifier, update_number);
}

bool c_simulation_view::handle_synchronous_update(struct simulation_update const* update)
{
	return INVOKE_CLASS_MEMBER(0x00466D50, c_simulation_view, handle_synchronous_update, update);
}

//.text:00466DC0 ; void c_game_results_replicator::handle_view_establishment(bool)

//.text:00466EB0 ; void c_simulation_view::initialize_view(int32, e_simulation_view_type, c_simulation_distributed_view*, s_machine_identifier const*, int32, char const*)

bool c_simulation_view::is_client_view() const
{
	return INVOKE_CLASS_MEMBER(0x00466FC0, c_simulation_view, is_client_view);
}

//.text:00466FE0 ; bool c_simulation_view::is_dead(int32*) const
//.text:00467000 ; bool c_simulation_view::is_distributed() const
//.text:00467050 ; void c_simulation_view::kill_view(e_simulation_view_reason)
//.text:00467120 ; void c_simulation_view::no_longer_authority()
//.text:00467180 ; void c_simulation_view::notify_closed()
//.text:004671E0 ; bool c_simulation_view::observer_channel_backlogged(e_network_message_type) const
//.text:00467210 ; bool c_simulation_view::observer_channel_get_bandwidth_events(int32, int32*) const
//.text:00467240 ; void c_simulation_view::observer_channel_set_waiting_on_backlog(e_network_message_type)
//.text:00467270 ; void c_simulation_view::send_establishment_message()

//.text:00467330 ; void c_game_results_replicator::send_game_results_update()

//.text:00467410 ; void c_simulation_view::send_message(e_network_message_type, int32, void const*, bool) const
//.text:00467490 ; void c_simulation_view::set_view_establishment(e_simulation_view_establishment_mode, int32)

//.text:00467520 ; void c_game_results_replicator::start_receiving_updates()
//.text:00467550 ; void c_game_results_replicator::start_sending_updates()
//.text:00467580 ; void c_game_results_replicator::stop_receiving_updates()
//.text:00467590 ; void c_game_results_replicator::stop_sending_updates()

int32 c_simulation_view::synchronous_catchup_attempt_count() const
{
	return INVOKE_CLASS_MEMBER(0x004675A0, c_simulation_view, synchronous_catchup_attempt_count);
}

void c_simulation_view::synchronous_catchup_complete()
{
	INVOKE_CLASS_MEMBER(0x004675B0, c_simulation_view, synchronous_catchup_complete);
}

bool c_simulation_view::synchronous_catchup_in_progress() const
{
	return INVOKE_CLASS_MEMBER(0x00467610, c_simulation_view, synchronous_catchup_in_progress);
}

bool c_simulation_view::synchronous_catchup_initiate()
{
	return INVOKE_CLASS_MEMBER(0x00467620, c_simulation_view, synchronous_catchup_initiate);
}

void c_simulation_view::synchronous_catchup_send_data()
{
	INVOKE_CLASS_MEMBER(0x00467730, c_simulation_view, synchronous_catchup_send_data);
}

void c_simulation_view::synchronous_catchup_terminate()
{
	INVOKE_CLASS_MEMBER(0x00467A60, c_simulation_view, synchronous_catchup_terminate);
}

int32 c_simulation_view::synchronous_client_get_acknowledged_update_number()
{
	return INVOKE_CLASS_MEMBER(0x00467AA0, c_simulation_view, synchronous_client_get_acknowledged_update_number);
}

//.text:00467AD0 ; void c_game_results_replicator::update()

//.text:00467B80 ; void c_simulation_view::update()
//.text:00467BF0 ; void c_simulation_view::update_view_activation_state()

