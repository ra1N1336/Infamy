#include "hooks.h"
#include "Globals.h"
#include "Accessors.h"

FrameStageNotifyFn oFrameStageNotify;

#define SEQUENCE_DEFAULT_DRAW 0
#define SEQUENCE_DEFAULT_IDLE1 1
#define SEQUENCE_DEFAULT_IDLE2 2
#define SEQUENCE_DEFAULT_LIGHT_MISS1 3
#define SEQUENCE_DEFAULT_LIGHT_MISS2 4
#define SEQUENCE_DEFAULT_HEAVY_MISS1 9
#define SEQUENCE_DEFAULT_HEAVY_HIT1 10
#define SEQUENCE_DEFAULT_HEAVY_BACKSTAB 11
#define SEQUENCE_DEFAULT_LOOKAT01 12

#define SEQUENCE_BUTTERFLY_DRAW 0
#define SEQUENCE_BUTTERFLY_DRAW2 1
#define SEQUENCE_BUTTERFLY_LOOKAT01 13
#define SEQUENCE_BUTTERFLY_LOOKAT03 15

#define SEQUENCE_FALCHION_IDLE1 1
#define SEQUENCE_FALCHION_HEAVY_MISS1 8
#define SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP 9
#define SEQUENCE_FALCHION_LOOKAT01 12
#define SEQUENCE_FALCHION_LOOKAT02 13

#define SEQUENCE_DAGGERS_IDLE1 1
#define SEQUENCE_DAGGERS_LIGHT_MISS1 2
#define SEQUENCE_DAGGERS_LIGHT_MISS5 6
#define SEQUENCE_DAGGERS_HEAVY_MISS2 11
#define SEQUENCE_DAGGERS_HEAVY_MISS1 12

#define SEQUENCE_BOWIE_IDLE1 1

#define	LIFE_ALIVE 0

#define RandomInt(nMin, nMax) (rand() % (nMax - nMin + 1) + nMin);

void RecvProxy_Viewmodel(const CRecvProxyData* pData, void* pStruct, void* pOut)
{
	int iModel = pData->m_Value.m_Int;

	auto nCTDefault = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_default_ct.mdl"));
	auto nBayonet = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_bayonet.mdl"));
	auto nGut = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_gut.mdl"));
	auto nTDefault = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_default_t.mdl"));
	auto nButterfly = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_butterfly.mdl"));
	auto nFlip = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_flip.mdl"));
	auto nGunGame = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_gg.mdl"));
	auto nFalchion = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_falchion_advanced.mdl"));
	auto nM9Bayonet = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_m9_bay.mdl"));
	auto nKarambit = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_karam.mdl"));
	auto nHuntsman = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_tactical.mdl"));
	auto nDagger = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_push.mdl"));
	auto nBowie = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_survival_bowie.mdl"));

	CBaseEntity *localPlayer = static_cast<CBaseEntity*>(ClientEntList->GetClientEntity(Engine->GetLocalPlayer()));
	if (localPlayer)
	{
		if (localPlayer->GetWeapon())
		{
			if (iModel == nBayonet
				|| iModel == nButterfly
				|| iModel == nCTDefault
				|| iModel == nTDefault
				|| iModel == nFlip
				|| iModel == nGut
				|| iModel == nHuntsman
				|| iModel == nGunGame
				|| iModel == nKarambit
				|| iModel == nM9Bayonet
				|| iModel == nFalchion)
			{
				switch (Options.Skins.KnifeSelect)
				{
				case 1:
					iModel = nBayonet;
					break;
				case 2:
					iModel = nFlip;
					break;
				case 3:
					iModel = nGut;
					break;
				case 4:
					iModel = nKarambit;
					break;
				case 5:
					iModel = nM9Bayonet;
					break;
				case 6:
					iModel = nHuntsman;
					break;
				case 7:
					iModel = nButterfly;
					break;
				case 8:
					iModel = nFalchion;
					break;
				case 9:
					iModel = nDagger;
					break;
				case 10:
					iModel = nBowie;
					break;
				}
			}
		}
	}

	*static_cast<int*>(pOut) = iModel;
}

void RecvProxy_Sequence(const CRecvProxyData* pData, void* pStruct, void* pOut)
{
	int iSequence = pData->m_Value.m_Int;

	CBaseCombatWeapon* Weapon = static_cast<CBaseCombatWeapon*>(pStruct);


	if (Weapon && Weapon->GetModel())
	{
		std::string rWeapon = ModelInfo->GetModelName(Weapon->GetModel());

		static bool bWasOpen = false;

		if (rWeapon.find(XorStr("v_knife_push.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_IDLE2:
				iSequence = SEQUENCE_DAGGERS_IDLE1; break;
			case SEQUENCE_DEFAULT_LIGHT_MISS1:
			case SEQUENCE_DEFAULT_LIGHT_MISS2:
				iSequence = RandomInt(SEQUENCE_DAGGERS_LIGHT_MISS1, SEQUENCE_DAGGERS_LIGHT_MISS5); break;
			case SEQUENCE_DEFAULT_HEAVY_MISS1:
				iSequence = RandomInt(SEQUENCE_DAGGERS_HEAVY_MISS2, SEQUENCE_DAGGERS_HEAVY_MISS1); break;
			case SEQUENCE_DEFAULT_HEAVY_HIT1:
			case SEQUENCE_DEFAULT_HEAVY_BACKSTAB:
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence += 3; break;
			case SEQUENCE_DEFAULT_DRAW:
			case SEQUENCE_DEFAULT_IDLE1:
				break;
			default:
				iSequence += 2;
			}
		}
		else if (rWeapon.find(XorStr("v_knife_falchion_advanced.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_IDLE2:
				iSequence = SEQUENCE_FALCHION_IDLE1; break;
			case SEQUENCE_DEFAULT_HEAVY_MISS1:
				iSequence = RandomInt(SEQUENCE_FALCHION_HEAVY_MISS1, SEQUENCE_FALCHION_HEAVY_MISS1_NOFLIP); break;
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomInt(SEQUENCE_FALCHION_LOOKAT01, SEQUENCE_FALCHION_LOOKAT02); break;
			case SEQUENCE_DEFAULT_DRAW:
			case SEQUENCE_DEFAULT_IDLE1:
				break;
			default:
				iSequence--;
			}
		}
		else if (rWeapon.find(XorStr("v_knife_butterfly.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_DRAW:
				iSequence = RandomInt(SEQUENCE_BUTTERFLY_DRAW, SEQUENCE_BUTTERFLY_DRAW2); break;
			case SEQUENCE_DEFAULT_LOOKAT01:
				iSequence = RandomInt(SEQUENCE_BUTTERFLY_LOOKAT01, SEQUENCE_BUTTERFLY_LOOKAT03); break;
			default:
				iSequence++;
			}
		}
		else if (rWeapon.find(XorStr("v_knife_survival_bowie.mdl")) != std::string::npos)
		{
			switch (iSequence) {
			case SEQUENCE_DEFAULT_DRAW:
			case SEQUENCE_DEFAULT_IDLE1:
				break;
			case SEQUENCE_DEFAULT_IDLE2:
				iSequence = SEQUENCE_BOWIE_IDLE1; break;
			default:
				iSequence--;
			}
		}

		*static_cast<int*>(pOut) = iSequence;
	}
}
void StoreYaw(const CRecvProxyData* pData, void* pStruct, void* pOut)
{
   Global::oAAA[1] = pData->m_Value.m_Float;
}
void StorePitch(const CRecvProxyData* pData, void* pStruct, void* pOut)
{
   Global::oAAA[0] = pData->m_Value.m_Float;
}

void __stdcall Game::hkdFrameStageNotify(ClientFrameStage_t curStage)
{
	QAngle aimold;
	QAngle viewold;
	QAngle* aim = nullptr;
	QAngle* view = nullptr;
	if (Engine->IsConnected() && Engine->IsInGame())
	{
		if (FRAME_RENDER_START)
		{
			auto LocalPlayer = static_cast<CBaseEntity*>(ClientEntList->GetClientEntity(Engine->GetLocalPlayer()));
			if (!LocalPlayer)
				return;
			if (LocalPlayer->GetAlive())
			{
				if (Options.Visuals.Removals.VisualRecoil)
				{

					aim = reinterpret_cast<QAngle*>(DWORD(Global::LocalPlayer) + offsets.m_aimPunchAngle);
					view = reinterpret_cast<QAngle*>(DWORD(Global::LocalPlayer) + offsets.m_viewPunchAngle);
					aimold = *aim;
					viewold = *view;
					*aim = QAngle(0, 0, 0);
					*view = QAngle(0, 0, 0);

				}

				auto ThirdPerson = *reinterpret_cast<bool*>(reinterpret_cast<DWORD>(g_pCInput) + 0xA5);

				if (ThirdPerson)
				{
					*reinterpret_cast<QAngle*>(reinterpret_cast<DWORD>(LocalPlayer) + offsets.dwDeadFlag + 0x4) = Global::VisualAngle;
				}
			}
		}

		// Begin Standard Skin Changer ( VERY EARLY STAGES )
		if (FRAME_NET_UPDATE_POSTDATAUPDATE_START)
		{
			if(Options.Rage.Aimbot.AntiAntiAim)
			{
			// Run the actual check to make sure this functions only when enabled is on.
				for (auto i = 0; i < ClientEntList->GetHighestEntityIndex(); i++)
				{
					static float Jittering[64] = { 0 };
					CBaseEntity* pEnt = nullptr;
					if (!(pEnt = ClientEntList->GetClientEntity(i)))
						continue;
					if ((pEnt == Global::LocalPlayer))
						continue;
					player_info_t pTemp;

					if (!Engine->GetPlayerInfo(i, &pTemp))
						continue;
					Options.Rage.Aimbot.AAA.oAngle[i].x = *reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEnt) + offsets.m_angEyeAnglesX);
					Options.Rage.Aimbot.AAA.oAngle[i].y = *reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEnt) + offsets.m_angEyeAnglesY);
					if (Options.Rage.Aimbot.AntiAntiAim)
					{
						auto bIsJitter = false;
						auto *Pitch = reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEnt) + offsets.m_angEyeAnglesX);
						auto *Yaw = reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEnt) + offsets.m_angEyeAnglesY);
						if (Options.Rage.Aimbot.AAA.Lisp[i] == 4 || Options.Rage.Aimbot.AAA.Lisp[i] == 5)
							*Yaw = Global::pCmd->tick_count * 20 % 360;
						else
						{
							if (*Yaw > 180.f)
								*Yaw -= 360.f;
							if (*Yaw < -180.f)
								*Yaw += 360.f;
							if (Options.Rage.Aimbot.AAA.Lisp[i] == 2
								|| Options.Rage.Aimbot.AAA.Lisp[i] == 3)
							{
								auto oYaw = Yaw;
								if ((*Yaw - Jittering[i]) > 15.f || (*Yaw - Jittering[i]) < -15.f)
								{
									bIsJitter = true;
								}
								if (bIsJitter)
								{
									*Yaw -= (Yaw - oYaw);
								}
								Jittering[i] = *oYaw;// jitter fix untill I have Interpolation fix working.
							}
						}
						if (Options.Rage.Aimbot.AAA.Lisp[i] == 3 || Options.Rage.Aimbot.AAA.Lisp[i] == 5)
						{
							static auto bFlip = false;
							if (bFlip)
							{
								*Pitch = -89;
							}
							else
							{
								*Pitch = 89;
							}
							bFlip = !bFlip;
						}
						else if (Options.Rage.Aimbot.AAA.Lisp[i] == 1
							|| Options.Rage.Aimbot.AAA.Lisp[i] == 2
							|| Options.Rage.Aimbot.AAA.Lisp[i] == 4)
						{

							if (*Pitch > 89.f  && *Pitch < 270.f)
								*Pitch = 89.f;
							else if (*Pitch < 270.f && *Pitch > 360.f)
								*Pitch = -89.f;
						}


						if (Options.Rage.Aimbot.AAA.Lisp[i] != 5)
						{
							if (Options.Rage.Aimbot.AAA.Lisp[i] != 3)
								*Pitch += Options.Rage.Aimbot.AAA.CAngle[i].x;
							if (Options.Rage.Aimbot.AAA.Lisp[i] != 4)
								*Yaw += Options.Rage.Aimbot.AAA.CAngle[i].y;
						}
					}
				}
			}

			if (Options.Skins.Enabled)
			{
				auto nCTDefault = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_default_ct.mdl"));
				auto nBayonet = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_bayonet.mdl"));
				auto nGut = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_gut.mdl"));
				auto nTDefault = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_default_t.mdl"));
				auto nButterfly = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_butterfly.mdl"));
				auto nFlip = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_flip.mdl"));
				auto nGunGame = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_gg.mdl"));
				auto nFalchion = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_falchion_advanced.mdl"));
				auto nM9Bayonet = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_m9_bay.mdl"));
				auto nKarambit = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_karam.mdl"));
				auto nHuntsman = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_tactical.mdl"));
				auto nDagger = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_push.mdl"));
				auto nBowie = ModelInfo->GetModelIndex(XorStr("models/weapons/v_knife_survival_bowie.mdl"));

				CBaseEntity *pLocal = ClientEntList->GetClientEntity(Engine->GetLocalPlayer());

				for (int i = ClientEntList->GetHighestEntityIndex(); i >= 0; --i)
				{
					CBaseEntity* pEntity = ClientEntList->GetClientEntity(i);
					if (pEntity)
					{
						ULONG hOwnerEntity = *reinterpret_cast<PULONG>(DWORD(pEntity) + 0x148);

						CBaseEntity* pOwner = ClientEntList->GetClientEntityFromHandle(hOwnerEntity);

						if (pOwner)
						{

							if (pOwner == pLocal)
							{

								std::string rWeapon = ModelInfo->GetModelName(pEntity->GetModel());

								if (!(rWeapon.find(XorStr("models/weapons"), 0) != std::string::npos))
									continue;

								if (rWeapon.find(XorStr("c4_planted"), 0) != std::string::npos)
									continue;

								if (rWeapon.find(XorStr("thrown"), 0) != std::string::npos)
									continue;

								if (rWeapon.find(XorStr("smokegrenade"), 0) != std::string::npos)
									continue;

								if (rWeapon.find(XorStr("flashbang"), 0) != std::string::npos)
									continue;

								if (rWeapon.find(XorStr("fraggrenade"), 0) != std::string::npos)
									continue;

								if (rWeapon.find(XorStr("molotov"), 0) != std::string::npos)
									continue;

								if (rWeapon.find(XorStr("decoy"), 0) != std::string::npos)
									continue;

								if (rWeapon.find(XorStr("incendiarygrenade"), 0) != std::string::npos)
									continue;

								if (rWeapon.find(XorStr("ied"), 0) != std::string::npos)
									continue;

								if (rWeapon.find(XorStr("w_eq_"), 0) != std::string::npos)
									continue;

								CBaseCombatWeapon* pWeapon = reinterpret_cast<CBaseCombatWeapon*>(pEntity);

								ClientClass *pClass = Client->GetAllClasses();

								NetVars->HookProp(XorStr("DT_BaseViewModel"), XorStr("m_nModelIndex"), RecvProxy_Viewmodel);
								NetVars->HookProp(XorStr("DT_BaseViewModel"), XorStr("m_nSequence"), RecvProxy_Sequence);

								player_info_t LocalInfo;
								LocalInfo = pLocal->GetPlayerInfo();

								auto weaponID = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pWeapon) + offsets.m_iItemDefinitionIndex);
								switch (weaponID)
								{
								case WEAPON_DEAGLE:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.deagle;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_CZ75A:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.cz75;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_HKP2000:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.p2000;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_ELITE:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.elites;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_P250:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.p250;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_FIVESEVEN:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.fiveseven;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_TEC9:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.tec9;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_GLOCK:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.glock;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_AUG:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.aug;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_GALILAR:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.galil;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_USP_SILENCER:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.usps;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_AK47:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.ak47;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_FAMAS:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.famas;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_M4A1:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.m4a4;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_M4A1_SILENCER:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.m4a1s;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_BIZON:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.bizon;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;

								case WEAPON_MAC10:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.mac10;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_MP7:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.mp7;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_MP9:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.mp9;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_P90:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.p90;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_M249:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.m249;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_UMP45:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.ump45;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_NEGEV:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.negev;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_MAG7:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.mag7;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_NOVA:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.nova;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_SAWEDOFF:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.sawedoff;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_XM1014:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.xm1014;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_SCAR20:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.scar20;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_AWP:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.awp;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_SSG08:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.ssg08;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_G3SG1:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.g3sg1;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_REVOLVER:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.magnum;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case WEAPON_SG556:
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackPaintKit) = Options.Skins.sg556;
									if (Options.Skins.StatTrak > 1)
									{
										*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iEntityQuality) = 2;
									}
									break;
								case 59:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								case 500:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								case 42:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								case 507:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								case 506:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								case 508:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								case 509:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								case 515:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								case 516:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								case 505:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie); 
									break;
								case 512:
									ChangeKnifeColor(pWeapon, nBayonet, nFlip, nGut, nKarambit, nM9Bayonet, nHuntsman, nButterfly, nFalchion, nDagger, nBowie);
									break;
								}
								*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_OriginalOwnerXuidHigh) = LocalInfo.xuidhigh;
								*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_OriginalOwnerXuidLow) = LocalInfo.xuidlow;
								*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iAccountID) = LocalInfo.xuidlow;
								*reinterpret_cast<float*>(DWORD(pWeapon) + offsets.m_flFallbackWear) = float(0.000000002f);
								if (Options.Skins.StatTrak > 1)
								{
									*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_nFallbackStatTrak) = Options.Skins.StatTrak;
								}
								*reinterpret_cast<int*>(DWORD(pWeapon) + offsets.m_iItemIDHigh) = -1;
							}
						}
					}
				}
			}
		}

	}
	oFrameStageNotify(curStage);
	if (aim && view && Options.Visuals.Removals.VisualRecoil)
	{
		*aim = aimold;
		*view = viewold;
	}
}
void __stdcall Game::hkdHudUpdate(bool active)
{
	static auto dwHudUpdate = Hooks::pMovePacket->dwGetMethodAddress(11);
	__asm
	{
		push active
		call dwHudUpdate
	}
	if (Engine->IsInGame() && Engine->IsConnected())
	{
		NetVars->HookProp("DT_CSPlayer", "m_angEyeAngles[0]", StorePitch);
		NetVars->HookProp("DT_CSPlayer", "m_angEyeAngles[1]", StoreYaw);
	}
}
