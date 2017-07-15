#include "Accessors.h"
#include <vector>
cManagers* g_pManagers = new cManagers;
cpSilent* g_pSilent = new cpSilent;
void cManagers::CreateMove(CUserCmd* pCmd, bool& bSendPackets)
{

	// Call Pregame stuff here


	//call Create Move Features Here
	if (!Global::LocalPlayer) return;

	if (!Global::LocalPlayer->GetAlive()) return;

	// Testing new convar stuff

	static bool RegisterCommandOnce;

	if (!RegisterCommandOnce)
	{
		MinspecCvar* fovbypass = new MinspecCvar("viewmodel_fov", "inf_fov", 60);
		RegisterCommandOnce = true;
	}
	ConVar* ViewModelFOV = Cvar->FindVar("inf_fov");


	if (Options.PlayerMods.Flash >= 1)
		g_pPlayer->CustomizeFlash();

	if (Options.Visuals.ESP.NoName)
		g_pPlayer->NoName();

	if (Options.PlayerMods.ClanTags.Enabled >= 1)
		g_pPlayer->ClanTagChanger();

	if (Options.Visuals.ESP.Enabled && Options.Visuals.ESP.FOV2 > 1)
	{
		int newViewModel = 60 + Options.Visuals.ESP.FOV2;
		ViewModelFOV->SetValue(newViewModel);
	}

	//auto LocalWepID = Global::LocalPlayer->GetWeaponID();
	auto LocalWep = Global::LocalPlayer->GetWeapon();
	if (LocalWep)
		g_pSilent->Setup();

	if (Options.Skins.LeftHandKnife)
		g_pPlayer->LeftHandOnly();

	if (Options.PlayerMods.bhop.Enabled)
		g_pPlayer->Bhop(pCmd);

	if (Options.PlayerMods.AutoStrafe.Enabled)
		g_pPlayer->AutoStrafe(pCmd);

	if (Options.PlayerMods.AutoStrafe.REnabled)
		g_pPlayer->RageAutoStrafe(pCmd);

	static auto WasFiring = false;
	auto WeaponInfo = LocalWep->GetCSWpnData();
	if (LocalWep)
	{
		if (!WeaponInfo->m_bFullAuto && Options.PlayerMods.AutoPistol.Enabled)
		{

			if (LocalWep->GetWeaponID() == WEAPON_C4 || LocalWep->GetWeaponType() == WEPCLASS_INVALID)
				return;

			if (pCmd->buttons & IN_ATTACK)
			{
				if (WasFiring)
				{
					pCmd->buttons &= ~IN_ATTACK;
				}
			}

			WasFiring = pCmd->buttons & IN_ATTACK ? true : false;
		}
	}

	if (LocalWep && Options.Legit.Aimbot.Enabled && !Options.AntiCheat.League && g_pSilent->bCanFire)
		g_pLegit->Aimbot();


	if (LocalWep && Options.Legit.Aimbot.Enabled && Options.AntiCheat.League)
	{
		if (GetAsyncKeyState(0x01))
		{
			g_pLegit->subtleAim(Global::pCmd, Options.Legit.Aimbot.Bone);
		}
	}

	if (LocalWep)
		g_pRage->Invoke(pCmd, bSendPackets, g_pSilent->bCanFire);

	if (pCmd->buttons & IN_ATTACK && !g_pRage->IsAimbotting && Options.Visuals.Removals.Recoil)
		pCmd->viewangles -= Global::LocalPlayer->GetPunch() * 2.f;

	if (LocalWep)
		g_pLegit->HandleTrigger(pCmd);

	if (Options.PlayerMods.AirStuck.Enabled)
		g_pPlayer->AirStuck(pCmd);

	if (Options.PlayerMods.FakeLag.Enabled)
		g_pPlayer->FakeLag(pCmd, bSendPackets);

	g_pSilent->Handle(bSendPackets);

	if (Options.AntiCheat.MM || Options.AntiCheat.SMAC || Options.AntiCheat.League || Options.AntiCheat.VAC)
		this->Clamp(pCmd);
}

void cManagers::Painttraverse(HFont hFont)
{
	//call Drawn Features Here
}

void cManagers::Clamp(CUserCmd* pCmd)
{
	pCmd->viewangles.Normalize();
	if (pCmd->forwardmove > 450.f)
		pCmd->forwardmove = 450.f;
	else if (pCmd->forwardmove < -450.f)
		pCmd->forwardmove = -450.f;

	if (pCmd->sidemove > 450.f)
		pCmd->sidemove = 450.f;
	else if (pCmd->sidemove < -450.f)
		pCmd->sidemove = -450.f;

	if (pCmd->upmove > 320.f)
		pCmd->upmove = 320.f;
	else if (pCmd->upmove < -320.f)
		pCmd->upmove = -320.f;

	pCmd->viewangles.Clamp();
}

void cpSilent::Setup()
{
    bCanFire = true;
	flCurTime = Globals->interval_per_tick * (Global::LocalPlayer->GetTickBase() + 1);
	flNextPrimary = Global::LocalPlayer->GetWeapon()->GetNextPrimaryAttack();
	if (flNextPrimary > flCurTime || bOldBullet)
		bCanFire = false;
	if (!(flNextPrimary > flCurTime))
		bOldBullet = false;
}

void cpSilent::Handle(bool& bSendPackets)
{
	if (!Options.Legit.Aimbot.PerfectSilentAim)return;
	if (bCanFire && Global::pCmd->buttons & IN_ATTACK)
	{
		bSendPackets = false;
		iChokedticks++;
	}
	//So we dont kill ourselfs
	if (iChokedticks > iMaxChokedticks)
		bSendPackets = true;//this will overwrite fakelag values when psilent is on
	if (bSendPackets)
	{
		iChokedticks = 0;
		Global::pCmd->viewangles = Global::oCmd->viewangles;
		Global::pCmd->forwardmove = Global::oCmd->forwardmove;
		Global::pCmd->sidemove = Global::oCmd->sidemove;
	}
}

itemTimer::itemTimer() {
	maxTime = 0;
}

itemTimer::itemTimer(float _maxTime) {
	maxTime = _maxTime;
}

float itemTimer::getTimeRemaining() {
	auto time = (timeStarted - (float(clock()) / float(CLOCKS_PER_SEC))) + maxTime;
	return time ? time : 0.00001f; //ensure we don't ever return a 0
}

float itemTimer::getTimeRemainingRatio() {
	return getTimeRemaining() / getMaxTime();
}

float itemTimer::getMaxTime() {
	return maxTime ? maxTime : 1; //don't ever return 0
}

void itemTimer::startTimer() {
	timeStarted = float(float(clock()) / float(CLOCKS_PER_SEC));
}

void itemTimer::setMaxTime(float time) {
	maxTime = time;
}

FloatingText::FloatingText(CBaseEntity* attachEnt, float lifetime, int Damage)
{
	TimeCreated = Global::CurrTime;
	ExpireTime = TimeCreated + lifetime;
	pEnt = attachEnt;
	DamageAmt = Damage;
}

void FloatingText::Draw()
{
	auto head = pEnt->GetBonePosition(6);
	Vector screen;

	if (WorldToScreen(head, screen))
	{
		auto lifetime = ExpireTime - TimeCreated;
		auto pct = 1 - ((ExpireTime - Global::CurrTime) / lifetime);
		int offset = pct * 50;
		int y = screen.y - 15 - offset;

		if (DamageAmt >= 100)
		{
			DrawString(HitIndicator, screen.x, y, Color(255, 0, 0, 255 * (1 - pct)), FONT_CENTER, "CRITICAL HIT");
		}
		else
		{
			DrawString(HitIndicator, screen.x, y, Color(255, 0, 0, 255 * (1 - pct)), FONT_CENTER, "-%d", DamageAmt);
		}
		//DrawRect(1, 1, 1920, 1080, Color(0, 0, 0, 255));// drawing dicks here
	}
}


void CNadeTracer::AddTracer(CBaseEntity* pGrenade, Color colorTrace, unsigned int iMaxLength)
{
	m_setGrenadeExists.insert(pGrenade);
	if (m_mapGrenades.find(pGrenade) == m_mapGrenades.end())
		m_mapGrenades[pGrenade] = CTraceObj(colorTrace, iMaxLength);

	if (m_mapGrenades[pGrenade].m_timerPointLock.diff() > 0.025f) //25 ms
	{
		m_mapGrenades[pGrenade].m_vecTracePoints.push_back(pGrenade->GetOrigin());
		if (m_mapGrenades[pGrenade].m_vecTracePoints.size() > m_mapGrenades[pGrenade].m_iMaxLength)
			m_mapGrenades[pGrenade].m_vecTracePoints.erase(m_mapGrenades[pGrenade].m_vecTracePoints.begin());

		m_mapGrenades[pGrenade].m_timerPointLock.init();
	}
}

void CNadeTracer::Draw()
{
	Vector vecLastScreenPos;
	bool bInit = false;

	for (auto& traceObj : m_mapGrenades)
	{
		for (auto& vecPos : traceObj.second.m_vecTracePoints)
		{
			Vector vecScreenPos;
			WorldToScreen(vecPos, vecScreenPos);
			if (vecScreenPos.x != NULL || vecScreenPos.y != NULL)
			{
				if (bInit)
					DrawLine(vecLastScreenPos.x, vecLastScreenPos.y, vecScreenPos.x, vecScreenPos.y, traceObj.second.m_colorTrace);

				vecLastScreenPos = vecScreenPos;
				bInit = true;
			}
		}
		bInit = false;
	}
}

void CNadeTracer::Clear()
{
	for (auto it = m_mapGrenades.begin(); it != m_mapGrenades.end(); ++it)
	{
		if (m_setGrenadeExists.find((*it).first) == m_setGrenadeExists.end())
		{
			it = m_mapGrenades.erase(it);
			if (it == m_mapGrenades.end())
				break;
		}
	}

	m_setGrenadeExists.clear();
}

CTraceObj::CTraceObj(Color colorTrace, unsigned int iMaxLength)
{
	m_colorTrace = colorTrace;
	m_iMaxLength = iMaxLength;
	m_timerPointLock.init();
}