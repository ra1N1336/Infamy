#pragma once
#include "Cheats.h"
#include "sdk.h"
#include "Globals.h"
#include <vector>
#include <set>
#include <unordered_map>

class cManagers
{
public:
	//Single line calls for hook
	void CreateMove(CUserCmd*, bool&);
	void Painttraverse(HFont);
	void Clamp(CUserCmd*);
};
class cpSilent
{
public:
	bool bCanFire = false;
	bool bOldBullet = false;
	float flCurTime;
	int iMaxChokedticks = 14;
    int iChokedticks = -1;
	float flNextPrimary;
	void Setup();
	void Handle(bool&);
};
extern cManagers* g_pManagers;
extern void ChangeKnifeColor(CBaseCombatWeapon* pWeapon, int nBayonet, int nFlip, int nGut, int nKarambit, int nM9Bayonet, int nHuntsman, int nButterfly, int nFalchion, int nDagger, int nBowie);
class CCustomString
{
public:
	char* m_pszString;
	int m_iUnknown0, m_iUnknown1;
	int m_iLength;
};

class itemTimer {
public:
	itemTimer();
	itemTimer(float maxTime);
	float getTimeRemaining();
	float getTimeRemainingRatio();
	float getMaxTime();
	void setMaxTime(float);
	void startTimer();
private:
	float timeStarted;
	float maxTime;
};


class FloatingText
{
public:
	void Draw();
	float TimeCreated;
	float ExpireTime;
	FloatingText(CBaseEntity* attachEnt, float lifetime, int Damage);

private:
	CBaseEntity* pEnt;
	int DamageAmt;

};

class CTimer
{
private:
	__int64 initialTS, currentTS;
	float secsPerCount;

public:
	CTimer()
	{
		__int64 countsPerSec = initialTS = currentTS = 0;
		QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
		if (countsPerSec == 0)
			secsPerCount = 1.0f;
		else
			secsPerCount = 1.0f / (float)countsPerSec;
	}
	void init()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&initialTS);
	}
	float diff()
	{
		QueryPerformanceCounter((LARGE_INTEGER*)&currentTS);
		return ((float)currentTS - (float)initialTS)*secsPerCount;
	}
};

struct CTraceObj
{
	CTraceObj() = default;
	CTraceObj(Color, unsigned int);

	Color m_colorTrace;
	unsigned int m_iMaxLength;
	std::vector<Vector> m_vecTracePoints;
	CTimer m_timerPointLock;
};

class CNadeTracer
{
private:

	std::unordered_map<CBaseEntity*, CTraceObj> m_mapGrenades;
	std::set<CBaseEntity*> m_setGrenadeExists;
	
public:
	//CNadeTracer(Renderer*, source_engine::Math*);
	void AddTracer(CBaseEntity*, Color, unsigned int);
	void Draw();
	void Clear();
};

class CPaintKit
{
public:
	int id;

	CCustomString name;
	CCustomString description_string;
	CCustomString description_tag;
	CCustomString pattern;
	CCustomString logo_material;

private:
	DWORD pad0[2];

public:
	int style;

	Color color0;
	Color color1;
	Color color2;
	Color color3;

private:
	DWORD pad1[4];

public:
	float wear_default;
	float wear_remap_min;
	float wear_remap_max;

	BYTE seed;

	BYTE phongexponent;
	BYTE phongalbedoboost;
	BYTE phongintensity;

	float pattern_scale;
	float pattern_offset_y_start;
	float pattern_offset_y_end;
	float pattern_offset_x_start;
	float pattern_offset_x_end;
	float pattern_rotate_start;
	float pattern_rotate_end;

	float logo_scale;
	float logo_offset_x;
	float logo_offset_y;
	float logo_rotation;

	int ignore_weapon_size_scale;

	int view_model_exponent_override_size;

	int only_first_material;

private:
	DWORD pad2[2];
};