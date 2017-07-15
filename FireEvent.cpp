#include "hooks.h"
#include "Globals.h"
#include <unordered_map>
#include "Accessors.h"
#pragma comment(lib,"Winmm.lib")
FireEventClientSideFn oFireEventClientSide;
float  _flHurtTime;


bool __fastcall Game::FireEventClientSideThink(void* ecx, void* edx, IGameEvent* pEvent) {
	// If the event pointer is invalid just call the original.
	if (!pEvent)
		return oFireEventClientSide(ecx, pEvent);


	if (Options.PlayerMods.KillMsg.Enabled)
	{
		if (!strcmp(pEvent->GetName(), XorStr("player_death")))
		{
			// The game launched a player_death event.
			auto nUserID = pEvent->GetInt(XorStr("attacker"));
			auto nDead = pEvent->GetInt(XorStr("userid"));
			if (!nUserID || !nDead)
				return false;

			// Continue only if I'm the one who killed
			if (Engine->GetPlayerForUserID(nUserID) != Engine->GetLocalPlayer())
				return false;

			char pszBuffer[6969];
			sprintf_s(pszBuffer, "say %s", Options.PlayerMods.KillMsg.buf);

			Engine->ClientCmd(pszBuffer);
		}
	}

	if (Options.Visuals.ESP.DamageIndicator)
	{
		if (!strcmp(pEvent->GetName(), XorStr("player_hurt"))) {
			auto attacker = pEvent->GetInt(XorStr("attacker"));
			auto dmgdone = pEvent->GetInt(XorStr("dmg_health"));
			auto Hurt = pEvent->GetInt(XorStr("userid"));
			CBaseEntity* pEnt = ClientEntList->GetClientEntity(Engine->GetPlayerForUserID(Hurt));
			if (Engine->GetPlayerForUserID(attacker) == Engine->GetLocalPlayer()) {
				Global::DamageDealt = dmgdone;
				Global::DamageHit.push_back(FloatingText(pEnt, 1.f, dmgdone));
			}
		}
	}

	if (Options.Visuals.ESP.Hitmarker)
	{
		if (!strcmp(pEvent->GetName(), XorStr("player_hurt"))) {

			auto attacker = pEvent->GetInt(XorStr("attacker"));
			auto dmgdone = pEvent->GetInt(XorStr("dmg_health"));

			if (Engine->GetPlayerForUserID(attacker) == Engine->GetLocalPlayer()) {
				PlaySoundA(XorStr("C:\\Infamy\\Files\\hitsound.wav"), nullptr, SND_ASYNC);
				Global::flHurtTime = Globals->curtime;
			}
		}
	}

	// Make sure we grab all instances when the bomb is not used.
	if (Options.Visuals.ESP.DrawBomb)
	{
		if (!strcmp(pEvent->GetName(), XorStr("bomb_defused")) || !strcmp(pEvent->GetName(), XorStr("bomb_exploded")) || !strcmp(pEvent->GetName(), XorStr("round_end")) || !strcmp(pEvent->GetName(), XorStr("round_start"))) {
			Global::isBombPlanted = false;
		}

		if (!strcmp(pEvent->GetName(), XorStr("bomb_planted"))) {
			Global::isBombPlanted = true;
		}
	}

	// Run the original FireEventClientSide function.
	return oFireEventClientSide(ecx, pEvent);
};