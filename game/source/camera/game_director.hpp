#pragma once

#include "camera/director.hpp"

struct c_game_director :
	public c_director
{
public:
	void constructor(int32 user_index)
	{
		INVOKE_CLASS_MEMBER(0x007215C0, c_game_director, constructor, user_index);
	}
	
//protected:
	byte unused[0x14];
};
static_assert(sizeof(c_game_director) == 0x160);

