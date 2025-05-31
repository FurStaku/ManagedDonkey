#pragma once

#include "networking/logic/life_cycle/life_cycle_state_handler.hpp"

struct s_life_cycle_matchmaking_progress;

//typedef c_flags<e_matchmaking_select_host_flags, uns8, k_matchmaking_select_host_flags_count> c_matchmaking_select_host_flags;
typedef uns8 c_matchmaking_select_host_flags;

struct c_life_cycle_state_handler_matchmaking_select_host :
	public c_life_cycle_state_handler
{
public:
	virtual void update() override;
	virtual e_life_cycle_state_transition_type update_for_state_transition() override;
	virtual void enter(c_life_cycle_state_handler* from, int32 entry_data_size, void* entry_data) override;
	virtual void exit(c_life_cycle_state_handler* to) override;
	virtual const char* get_state_string() override;
	virtual void handle_missing_required_session_parameter(e_network_session_type session_type) override;

public:
	c_life_cycle_state_handler_matchmaking_select_host();
	void dispose();
	void get_progress(s_life_cycle_matchmaking_progress* progress_out);
	void initialize(c_life_cycle_state_manager* manager);
	
//protected:
	c_matchmaking_select_host_flags m_flags;
	uns32 m_select_host_start_time;
};
static_assert(sizeof(c_life_cycle_state_handler_matchmaking_select_host) == 0x30);

