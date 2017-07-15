#pragma once
#include "SDK.h"
#include "Globals.h"
#include "Globals.h"
#include "Menu.h"

extern DWORD __stdcall Visuals(void* args);
extern DWORD __stdcall Glow(void* args);
class cLegit
{
public:
	cLegit();
	void HandleTrigger(CUserCmd* pCmd);
	void triggerbot(CUserCmd*);
	CBaseEntity* getTargetUnderCrosshair(CUserCmd*, bool, bool, trace_t*) const;
	bool isNotAbleToShoot(CBaseEntity* entity, CBaseCombatWeapon* weapon);
	void pSilentLoop(CUserCmd* cmd, int bone);
	void Aimbot();
	int getBestTarget(CBaseEntity* local, CBaseCombatWeapon* weapon, Vector& dest);
	int GetTargetClosest();
	void GoToTarget(CBaseEntity* pTarget);
    bool ValidEntity(int i);
	void HandleConfigs();
	bool isBoneVisible(CBaseEntity* target, int bone);
	bool isPlayerVisible(CBaseEntity* target);
	QAngle calcViewangleAdjustment(CBaseEntity* target, CUserCmd* cmd, int bone, bool doubleRecoilComp);
	float screenDifference(QAngle& ang);
	Vector getPredictedPosition(Vector src, Vector velocity);
	float getRandomizedAngles(CBaseEntity* local);
	CBaseEntity* getTargetNearestCrosshair(CUserCmd* cmd, QAngle* deviance);
	void applyLinearAdjustment(int desiredX, int desiredY, int maxDistancePerSecond, float lastIteration);
	int GetClosestBone(CBaseEntity * Entity);
	QAngle getRandomizedRecoil(CBaseEntity* local);
	void RCS(CUserCmd * cmd);
	void subtleAim(CUserCmd* cmd, int bone);
private:
	int bestTarget;

	QAngle viewAngles;
	Vector hitboxPosition;
	QAngle finalAngles;
};
extern cLegit* g_pLegit;
struct FireBulletData
{
	Vector src;
	trace_t enter_trace;
	Vector direction;
	CTraceFilter filter;
	float trace_length;
	float trace_length_remaining;
	float current_damage;
	int penetrate_count;
};

class class_autowall
{
public:
	class_autowall();
	bool AutoWall(CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon, Vector& point);
	float GetDamage(Vector& point);
	float GetHitgroupDamage(int iHitgroup);
	float GetHitgroupDamageHigh(int iHitgroup);
	bool TraceToExit(Vector& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace);
	void ScaleDamage(int Hitgroup, CBaseEntity* pEntity, float weapon_armor_ratio, float& current_damage);
	void ScaleDamageHigh(int Hitgroup, CBaseEntity* pEntity, float weapon_armor_ratio, float& current_damage);
	static bool DidHitNonWorldEntity(CBaseEntity* m_pEnt);
	//bool TraceToExit(Vector& end, trace_t* enter_trace, Vector start, Vector dir, trace_t* exit_trace);

	bool SimulateFireBullet(CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon, FireBulletData& data);
	bool HandleBulletPenetration(WeaponInfo_t* wpn_data, FireBulletData& data);
	bool IsFuckingAutowalling;
	float bIsPointPenetrable(Vector vEnd);
private:
	CTraceFilterNoPlayer tfNoPlayers;
};

extern class_autowall g_pAutowall;
struct Hitbox
{
	Hitbox(void)
	{
		hitbox = -1;
	}

	Hitbox(int newHitBox)
	{
		hitbox = newHitBox;
	}

	int  hitbox;
	Vector points[9];
};

enum
{
	FL_HIGH = (1 << 0),
	FL_LOW = (1 << 1),
	FL_SPECIAL = (1 << 2)
};

struct BestPoint
{
	BestPoint(void)
	{
		hitbox = -1;
		point = Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	explicit BestPoint(int newHitBox)
	{
		hitbox = newHitBox;
		point = Vector(0, 0, 0);
		index = -1;
		dmg = -1;
		flags = 0;
	}

	Vector point;
	int  index;
	int  dmg;
	int  flags;
	int  hitbox;
};
class CFixMove
{
public:
	void Start();
	void End();
private:
	float m_oldforward, m_oldsidemove;
	QAngle m_oldangle;
};// stolen from a5
class cRage
{
public:
	void Invoke(CUserCmd*,bool&,bool);
	bool GetHitbox(CBaseEntity*, Hitbox*);
	bool GetBestPoint(CBaseEntity*, Hitbox*, BestPoint*);
	bool CustomMultipoint(CBaseEntity*, Hitbox*, BestPoint*);
	void AimStep(CBaseEntity* entity, QAngle& angle, CUserCmd* cmd);
	bool BestAimPointAll(CBaseEntity*, Vector&);
	bool BestAimPoint(CBaseEntity* target, Vector& hitboxs);
	bool BestAimPointHitbox(CBaseEntity*, Vector&);
	bool IsValidEntity(int);
	bool CustomHitscans(CBaseEntity*, Vector&);
	float AimNearPlayer(CBaseEntity*);
	void StopPlayer(CUserCmd*);
	int TargetSelection(CUserCmd*);
	void AntiAim(CUserCmd*, bool&);
	void Aimbot(CUserCmd*);
	void EnginePred(CUserCmd*);
	void MoniterNoSpread(CUserCmd*);
	void SetViewAngles(CUserCmd* pCmd, QAngle& fAngle);
	int target;
	bool IsAimbotting, IsStopped;
};
extern cRage* g_pRage;
class cPlayer
{
public:
	void Bhop(CUserCmd*);
	void ForceThirdPerson(CUserCmd* pCmd);
	void AutoStrafe(CUserCmd*);
	void FakeLag(CUserCmd*, bool&);
	void AirStuck(CUserCmd*);
	void SpoofConvars();
	void ForceUpdate();
	void LeftHandOnly();
	void NoName();
	void ClanTagChanger();
	void ValveEmployeeSlow();
	void InfamyName();
	void CustomizeFlash();
	void RageAutoStrafe(CUserCmd*);
	void doRecoilControl(CBaseEntity* local, CBaseCombatWeapon* weapon, CUserCmd* cmd);
	void SoundESP();
};
extern cPlayer* g_pPlayer;

class cESP
{
	struct plist_t
	{
		char* name;
		char* steamid;
		int   money;
		int   health;
		int   mmwins;
		char* mmrank;
	}players[64];

public:
	cESP();

	void think(CBaseEntity* local);
	void getScreenSize();
	bool isVisible(Vector& start, Vector& end, CBaseEntity* entity);
	void RunEntityGlow(CBaseEntity* pEnt);
	void DrawDLight(CBaseEntity* pEnt);
	void drawNadeTracer(CBaseEntity* entity);
	void drawWorld(CBaseEntity* entity);
	void drawBoundingBox(CBaseEntity* entity, Color color, const char* text);
private:
	void drawPlayer(CBaseEntity* local, CBaseEntity* entity);
	void DrawBone(CBaseEntity* pEnt);
	void DrawAimPoint(Color cColor, CBaseEntity* pEnt);
	void RunTrace(CBaseEntity* pEnt, Vector& vecStart, Vector& vecForward);
	void DrawTraceLine(Color cColor, CBaseEntity* pEnt);
	void DrawBombDefuser(CBaseEntity* pEnt);
	void DrawGlow(CBaseEntity* pEnt);
public:
	int width;
	int height;

private:
	Color espColor;
	Color glowColor;

private:
	player_info_t info;
};

extern cESP* g_pESP;