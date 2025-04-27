#pragma once

#include "cseries/cseries.hpp"
#include "networking/replication/replication_scheduler.hpp"

struct s_replication_event_manager_view_statistics
{
	int32 events_sent;
	int32 events_pending;
	int32 events_in_transit;
};
static_assert(sizeof(s_replication_event_manager_view_statistics) == 0xC);

struct c_replication_outgoing_event;
struct c_replication_event_manager;
struct c_replication_event_manager_view :
	public c_replication_scheduler_client
{
public:
	struct c_event_record
	{
		c_replication_outgoing_event* m_event;
		c_event_record* m_next;
	};
	static_assert(sizeof(c_event_record) == 0x8);
	
	struct c_packet_record
	{
		int32 m_packet_sequence_number;
		c_event_record* m_event_list;
		c_packet_record* m_next;
	};
	static_assert(sizeof(c_packet_record) == 0xC);

//private:
	bool m_initialized;
	bool m_fatal_error;
	int32 m_view_index;
	c_packet_record* m_packet_list;
	int32 m_packet_list_length;
	c_replication_event_manager* m_event_manager;
	s_replication_event_manager_view_statistics m_view_statistics;
};
static_assert(sizeof(c_replication_event_manager_view) == 0x28);

