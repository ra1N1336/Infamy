#pragma once
#include "Common.h"
#include "VMTHooks.h"
#include "netvars.h"
#include "FindPattern.h"
#include "offsets.h"
#include "Angles.h"
#include "Convar.h"
#include "CBaseEntity.h"
#include "Trace.h"
#include "Util.h"
#include "Interfaces.h"
#include "Math.h"
#include "draw.h"
#include "Effects.h"
#include "GlowManager.h"
#include "InputSystem.h"


// Timer Class
class delta_time
{
private:
	float spc_;
	__int64 pts_;


public:
	delta_time();
	~delta_time();

	float get_dt();

	void reset();

};


