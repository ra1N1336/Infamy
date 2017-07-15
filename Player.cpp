#include "Cheats.h"
cPlayer* g_pPlayer = new cPlayer;
void cPlayer::Bhop(CUserCmd* pCmd)
{
	static auto bJumped = false;
	static auto bFake = false;
	if(!bJumped && bFake)
	{ 
		bFake = false;
		pCmd->buttons |= IN_JUMP;
	}
	else if(pCmd->buttons & IN_JUMP)
	{
		if(Global::LocalPlayer->GetFlags() & FL_ONGROUND)
		{
			bJumped = true;
			bFake   = true;
		}
		else
		{
			pCmd->buttons &= ~IN_JUMP;
			bJumped = false;
		}
	}
	else
	{
		bJumped = false;
		bFake = false;
	}
}
template<class T, class U>
T Clamp(T in, U low, U high)
 {
	if (in <= low)
		 return low;
	
		if (in >= high)
		 return high;

	return in;
}

void cPlayer::ForceThirdPerson(CUserCmd* pCmd)
{
	static auto ThirdPerson = false;

	if (Engine->IsInGame() && Engine->IsConnected())
	{
		if (Global::LocalPlayer)
		{

			if (Options.Visuals.ESP.ThirdPerson)
			{
				auto LifeState = Global::LocalPlayer->GetAlive();
				static auto oLifeState = !LifeState;

				if (oLifeState != LifeState)
				{
					if (LifeState)				
						Engine->ExecuteClientCmd(XorStr("thirdperson"));
					else
						Engine->ExecuteClientCmd(XorStr("firstperson"));
				}
				oLifeState = LifeState;
				ThirdPerson = true;
			}
			
		
		}
	}
	if (!Options.Visuals.ESP.ThirdPerson && ThirdPerson)
	{
		ThirdPerson = false;
		Engine->ExecuteClientCmd(XorStr("firstperson"));
	}
}

void cPlayer::AutoStrafe(CUserCmd* pCmd)
{
	if (Global::LocalPlayer->GetFlags() & FL_ONGROUND)
		return;

	if (Global::pCmd->mousedx > 1 || Global::pCmd->mousedx < -1) {
		Global::pCmd->sidemove = Global::pCmd->mousedx < 0.f ? -400.f : 400.f;
	}

}
void cPlayer::FakeLag(CUserCmd* pCmd, bool& bSendPacket) 
{
	if (pCmd->buttons & IN_ATTACK) return;
	if (Global::LocalPlayer->GetVelocity() == Vector(0, 0, 0)) return;
	static int iTicks;
	if (iTicks > Options.PlayerMods.FakeLag.Choke)
		iTicks = 0;
	bSendPacket = iTicks < Options.PlayerMods.FakeLag.Send;
	iTicks++;
}

void cPlayer::AirStuck(CUserCmd* pCmd)
{
	static auto bAirStucked = false;
	if (pCmd->buttons & IN_ATTACK) return;
	if (GetAsyncKeyState(Options.PlayerMods.AirStuck.Key) & 1)
		bAirStucked = !bAirStucked;
	if (bAirStucked)
		pCmd->tick_count = 0xFFFFFFF;
}

void cPlayer::SpoofConvars()
{
	auto svcheatsspoof = new MinspecCvar(XorStr("sv_cheats"), XorStr("inf_cheeto"), 0);
	auto svcheats = Cvar->FindVar(XorStr("inf_cheeto"));
	svcheats->SetValue(1);
}

void cPlayer::LeftHandOnly()
{
	if (Options.Skins.LeftHandKnife)
	{

		auto LocalWep = Global::LocalPlayer->GetWeapon();
		if (LocalWep->GetWeaponType() == WEPCLASS_KNIFE)
		{
			Engine->ExecuteClientCmd(XorStr("cl_righthand 0"));
		}
		else
		{
			Engine->ExecuteClientCmd(XorStr("cl_righthand 1"));
		}
	}
	else
	{
		Engine->ExecuteClientCmd(XorStr("cl_righthand 1"));
	}
}

void cPlayer::NoName()
{
	ConVar* nameConvar = Cvar->FindVar(XorStr("name"));
	*reinterpret_cast<int*>(DWORD(&nameConvar->fnChangeCallback) + 0xC) = NULL;
	nameConvar->SetValue(XorStr("\n"));
}

void SetClanTag(const char* tag, const char* name)
{
	typedef void(__fastcall* pSetClanTagFn)(const char*, const char*);
	static auto pSetClanTag = reinterpret_cast<pSetClanTagFn>(Memory::FindPatternAlt(XorStr("engine.dll"),
		reinterpret_cast<PBYTE>(XorStr("\x53\x56\x57\x8B\xDA\x8B\xF9\xFF\x15\x00\x00\x00\x00\x6A\x24\x8B\xC8\x8B\x30")), XorStr("xxxxxxxxx????xxxxxx"), 0, 0));

	pSetClanTag(tag, name);
}

void cPlayer::ClanTagChanger()
{
	switch(Options.PlayerMods.ClanTags.Enabled)
	{
	case 1:
		InfamyName();
		break;
	case 2:
		SetClanTag(XorStr("[VALV\xE1\xB4\xB1]"), XorStr("Valve"));
		break;
	}
}

void cPlayer::InfamyName()
{

	static float timer;
	timer += 0.05;
	if (timer > 8.f) timer = 0.f;

	if (timer > 1)
		SetClanTag(XorStr("\xCE\xBB"), XorStr("INFAMY"));

	if (timer > 2)
		SetClanTag(XorStr("\xCE\xBB"), XorStr("INFAMY"));

	if (timer > 3)
		SetClanTag(XorStr("\xCE\xBBn"), XorStr("INFAMY"));

	if (timer > 4)
		SetClanTag(XorStr("\xCE\xBBnf"), XorStr("INFAMY"));

	if (timer > 5)
		SetClanTag(XorStr("\xCE\xBBnfa"), XorStr("INFAMY"));

	if (timer > 6)
		SetClanTag(XorStr("\xCE\xBBnfam"), XorStr("INFAMY"));

	if (timer > 7)
		SetClanTag(XorStr("\xCE\xBBnfamy"), XorStr("INFAMY"));
	
}

void cPlayer::CustomizeFlash()
{
	auto localPlayer = static_cast<CBaseEntity*>(ClientEntList->GetClientEntity(Engine->GetLocalPlayer()));

	float FlashAlpha = 0;
	switch (Options.PlayerMods.Flash)
	{
	case 1: // 10%
		FlashAlpha = 25.5f;
		break;
	case 2: // 20%
		FlashAlpha = 51.f;
		break;
	case 3: // 30%
		FlashAlpha = 76.5f;
		break;
	case 4: // 40%
		FlashAlpha = 102.f;
		break;
	case 5: // 50%
		FlashAlpha = 127.5f;
		break;
	case 6: // 60%
		FlashAlpha = 153.f;
		break;
	case 7: // 70%
		FlashAlpha = 178.5f;
		break;
	case 8: // 80%
		FlashAlpha = 204.f;
		break;
	case 9: // 90%
		FlashAlpha = 229.5f;
		break;
	case 10: // 100%
		FlashAlpha = 255.f;
		break;
	}

	*reinterpret_cast<float*>(DWORD(localPlayer) + offsets.m_flFlashMaxAlpha) = FlashAlpha;
}

void cPlayer::RageAutoStrafe(CUserCmd* pCmd)
{
	if (GetAsyncKeyState(0x57)//W 
		|| GetAsyncKeyState(0x41)//A
		|| GetAsyncKeyState(0x53)//S
		|| GetAsyncKeyState(0x44))//D
		return;

	 if (GetAsyncKeyState(VK_SPACE)  && (Global::LocalPlayer->GetFlags() & FL_ONGROUND)
		 && Global::LocalPlayer->GetVelocity().Length() <= 60.f)
	 {
		 pCmd->forwardmove = 450.f;
	 }
	 auto Delta = 0.f;
	 if (Global::LocalPlayer->GetVelocity().Length() > 60.f)
	 {
		 auto x = 30.f;
		 auto z = x / Global::LocalPlayer->GetVelocity().Length();
		 z = fabsf(z);
		 auto a = x * z;
		 Delta = a;
	 }
	 if (GetAsyncKeyState(VK_SPACE) && !(Global::LocalPlayer->GetFlags() & FL_ONGROUND))
	 {
		 if (pCmd->mousedx < 0)
			 pCmd->sidemove = -450;
		 if (pCmd->mousedx > 0)
			 pCmd->sidemove = 450;
		 if (pCmd->tick_count % 2)
		 {
			 pCmd->sidemove = -450;
		 }
		 else
		 {
			 pCmd->viewangles.y += Delta;
			 pCmd->sidemove = 450;
		 }
	 }
}