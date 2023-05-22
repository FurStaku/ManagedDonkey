#pragma once

#include "camera/camera.hpp"

struct c_static_camera : public c_camera
{
	real_point3d m_position;
	vector3d m_forward;
	real m_field_of_view;

	real __unknown2C;
	dword __unknown30;

	byte unused[0x18];

	void constructor(long user_index)
	{
		DECLFUNC(0x0072F170, void, __thiscall, c_camera*, long)(this, user_index);
	}
};
static_assert(sizeof(c_static_camera) == 0x4C);

struct c_scripted_camera : public c_camera
{
	byte unused[0x3C];

	void constructor()
	{
		DECLFUNC(0x0072BEB0, void, __thiscall, c_camera*)(this);
	}
};
static_assert(sizeof(c_scripted_camera) == 0x4C);