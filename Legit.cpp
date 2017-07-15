#include "Cheats.h"
cLegit* g_pLegit = new cLegit;
cLegit::cLegit()
{
	bestTarget = -1;

	viewAngles = QAngle(0.f, 0.f, 0.f);
	hitboxPosition = Vector(0.f, 0.f, 0.f);
	finalAngles = QAngle(0.f, 0.f, 0.f);
}
void cLegit::HandleTrigger(CUserCmd* pCmd)
{
	if (Options.Legit.Trigger.Enabled)
	{
		static auto TriggerTick = GetTickCount();
		if ((DWORD(TriggerTick) + 10) <= GetTickCount())
		{
			TriggerTick = DWORD(GetTickCount());
			this->triggerbot(pCmd);
		}
	}
}
bool cLegit::ValidEntity(int i)
{
	CBaseEntity* pTarget = nullptr;

	if (pTarget = ClientEntList->GetClientEntity(i))
		if (!(pTarget == Global::LocalPlayer))
			if (pTarget->GetHealth() >= 0)
				if (!pTarget->GetImmune())
					if (!pTarget->GetDormant())
						if (!(pTarget->GetTeam() == Global::LocalPlayer->GetTeam()))
							if (pTarget->IsVisible(Options.Legit.Aimbot.Bone))
							{
								QAngle Angles;
								CalcAngle(Global::LocalPlayer->GetEyePosition(), pTarget->GetBonePosition(Options.Legit.Aimbot.Bone), Angles);
								if (GetFov(Global::pCmd->viewangles, Angles) <= Options.Legit.Aimbot.Fov)
									return true;
							}
	return false;
}

void cLegit::HandleConfigs()
{
	if (!Options.Legit.Aimbot.WeaponConfigs) return;
	if (!Engine->IsInGame() || !Engine->IsConnected()) return;
	if (!Global::LocalPlayer)return;
	if (!Global::LocalPlayer->GetWeapon()) return;
	auto localPlayerWep = Global::LocalPlayer->GetWeapon();
	if (localPlayerWep->GetWeaponType() == WEPCLASS_KNIFE || localPlayerWep->GetWeaponType() == WEPCLASS_INVALID)
	{
		Options.Legit.Trigger.Enabled = false;
		Options.Legit.Aimbot.Enabled = false;
		Options.Legit.Aimbot.Bone = 0;
		Options.Legit.Aimbot.RCS = false;
		//Options.Legit.Aimbot.pRCS = false;
		//Options.Legit.Aimbot.lSmooth - 0.0f;
		Options.Legit.Aimbot.Smooth[0] = 1.f;
		Options.Legit.Aimbot.Smooth[1] = 1.f;
		Options.Legit.Aimbot.Fov = false;
		Options.Legit.Aimbot.SilentAim = false;
		Options.Legit.Aimbot.PerfectSilentAim = false;
		Options.Legit.Aimbot.LFOV = false;
		Options.Legit.Aimbot.AimSpeed = 0;
		Options.Legit.Aimbot.MultiplySpeed = 0;
		Options.Legit.Aimbot.FOVBOOST = 0;
		return;
	}

	if (localPlayerWep->GetWeaponType() == WEPCLASS_RIFLE)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Rifles.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.Rifles.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Rifles.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Rifles.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Rifles.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Rifles.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Rifles.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Rifles.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Rifles.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Rifles.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Rifles.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Rifles.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Rifles.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Rifles.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Rifles.FOVBOOST;
	}
	if (localPlayerWep->GetWeaponType() == WEPCLASS_PISTOL)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Pistols.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.Pistols.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Pistols.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Pistols.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Pistols.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Pistols.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Pistols.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Pistols.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Pistols.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Pistols.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Pistols.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Pistols.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Pistols.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Pistols.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Pistols.FOVBOOST;
	}
	if (localPlayerWep->GetWeaponType() == WEPCLASS_SNIPER)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Snipers.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.Snipers.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Snipers.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Snipers.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Snipers.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Snipers.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Snipers.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Snipers.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Snipers.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Snipers.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Snipers.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Snipers.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Snipers.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Snipers.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Snipers.FOVBOOST;
	}
	if (localPlayerWep->GetWeaponType() == WEPCLASS_SMG)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.SMGs.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.SMGs.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.SMGs.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.SMGs.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.SMGs.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.SMGs.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.SMGs.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.SMGs.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.SMGs.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.SMGs.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.SMGs.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.SMGs.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.SMGs.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.SMGs.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.SMGs.FOVBOOST;
	}
	if (localPlayerWep->GetWeaponType() == WEPCLASS_SHOTGUN)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Shotguns.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.Shotguns.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Shotguns.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Shotguns.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Shotguns.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Shotguns.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Shotguns.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Shotguns.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Shotguns.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Shotguns.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Shotguns.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Shotguns.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Shotguns.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Shotguns.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Shotguns.FOVBOOST;
	}
	if (localPlayerWep->GetWeaponType() == WEPCLASS_MACHINEGUN)
	{
		Options.Legit.Trigger.Enabled = Options.Legit.Aimbot.Configs.Machineguns.Trigger;
		Options.Legit.Aimbot.Enabled = Options.Legit.Aimbot.Configs.Machineguns.Enabled;
		Options.Legit.Aimbot.Bone = Options.Legit.Aimbot.Configs.Machineguns.Bone;
		Options.Legit.Aimbot.RCS = Options.Legit.Aimbot.Configs.Machineguns.RCS;
		Options.Legit.Aimbot.pRCS = Options.Legit.Aimbot.Configs.Machineguns.pRCS;
		Options.Legit.Aimbot.lSmooth = Options.Legit.Aimbot.Configs.Machineguns.lSmooth;
		Options.Legit.Aimbot.Smooth[0] = Options.Legit.Aimbot.Configs.Machineguns.Smooth[0];
		Options.Legit.Aimbot.Smooth[1] = Options.Legit.Aimbot.Configs.Machineguns.Smooth[1];
		Options.Legit.Aimbot.Fov = Options.Legit.Aimbot.Configs.Machineguns.Fov;
		Options.Legit.Aimbot.SilentAim = Options.Legit.Aimbot.Configs.Machineguns.SilentAim;
		Options.Legit.Aimbot.PerfectSilentAim = Options.Legit.Aimbot.Configs.Machineguns.PerfectSilentAim;
		// Begin League Options
		Options.Legit.Aimbot.LFOV = Options.Legit.Aimbot.Configs.Machineguns.LFOV;
		Options.Legit.Aimbot.AimSpeed = Options.Legit.Aimbot.Configs.Machineguns.AimSpeed;
		Options.Legit.Aimbot.MultiplySpeed = Options.Legit.Aimbot.Configs.Machineguns.MultiplySpeed;
		Options.Legit.Aimbot.FOVBOOST = Options.Legit.Aimbot.Configs.Machineguns.FOVBOOST;
	}
}

// Begin leaguebot rewrite

bool cLegit::isBoneVisible(CBaseEntity* target, int bone)
{
	Vector vEnd;
	auto Bone = 0;
	if (Options.Legit.Aimbot.DynamicHBox)
	{
		Bone = g_pLegit->GetClosestBone(target);
	}
	else
	{
		Bone = Options.Legit.Aimbot.Bone;
	}
	(vEnd = target->GetBonePosition(Bone));

	trace_t tr;
	Ray_t ray;

	CTraceFilter filter;
	filter.pSkip = Global::LocalPlayer;
	ray.Init(Global::LocalPlayer->GetEyePosition(), vEnd);
	EngineTrace->TraceRay(ray, CONTENTS_SOLID | CONTENTS_GRATE | CONTENTS_HITBOX, &filter, &tr);
	if (!tr.m_pEnt)
		return false;
	if (tr.hitgroup <= 7 && tr.hitgroup > 0)
		return true;
	return false;
}

bool cLegit::isPlayerVisible(CBaseEntity* target)
{
	for (auto i = 0; i < 6; i++)
	{
		if (isBoneVisible(target, i))
			return true;
	}
	return false;
}

QAngle cLegit::getRandomizedRecoil(CBaseEntity* local)
{
	auto punchAngles = local->GetPunch() * g_pMisc->random(Options.Legit.Aimbot.RCSMin, Options.Legit.Aimbot.RCSMax);
	return (local->GetShotsFired() > 1 ? punchAngles : QAngle(0.0f, 0.0f, 0.0f));
}

float cLegit::getRandomizedAngles(CBaseEntity* local)
{
	auto randomizedValue = 0.f;

	auto randomRate = g_pMisc->random(-Options.Legit.Aimbot.AngleValue, Options.Legit.Aimbot.AngleValue);
	auto randomDeviation = g_pMisc->random(-Options.Legit.Aimbot.AngleValue, Options.Legit.Aimbot.AngleValue);

	switch (rand() % 2)
	{
	case 0:
		randomizedValue = (randomRate * cos(randomDeviation));
		break;
	case 1:
		randomizedValue = (randomRate * sin(randomDeviation));
		break;
	}

	return (local->GetShotsFired() > 1 ? randomizedValue : 0.f);
}

QAngle cLegit::calcViewangleAdjustment(CBaseEntity* target, CUserCmd* cmd, int bone, bool doubleRecoilComp)
{
	auto localVecAimedFrom = Global::LocalPlayer->GetEyePosition();
	Vector targetVecAbs;
	(targetVecAbs = target->GetBonePosition(bone));
	auto targetVecRel = targetVecAbs - localVecAimedFrom;
	auto localPlayerWep = Global::LocalPlayer->GetWeapon();
	QAngle result;
	VectorAngles(targetVecRel, result);
	result -= cmd->viewangles;
	if (localPlayerWep->GetWeaponType() == WEPCLASS_RIFLE || localPlayerWep->GetWeaponType() == WEPCLASS_MACHINEGUN || localPlayerWep->GetWeaponType() == WEPCLASS_SMG && !Options.Legit.Aimbot.DynamicHBox)
	{
		// Begin testing
		if (Options.Legit.Aimbot.RCS)
			result -= doubleRecoilComp ? Global::LocalPlayer->GetPunch() * 2.f : Global::LocalPlayer->GetPunch();

	}

	if (Options.Legit.Aimbot.RandomizeAngles)
		result += getRandomizedAngles(target);

	if (result.x > 180)
		result.x -= 360;
	if (result.y > 180)
		result.y -= 360;
	return result;
}

float cLegit::screenDifference(QAngle& ang)
{
	return sqrt((ang.x * ang.x) + (ang.y * ang.y));
}


Vector cLegit::getPredictedPosition(Vector src, Vector velocity)
{
	return (src + (velocity * Globals->interval_per_tick));
}

CBaseEntity* cLegit::getTargetNearestCrosshair(CUserCmd* cmd, QAngle* deviance)
{
	CBaseEntity* closestEntity = nullptr;
	QAngle diff;
	diff.x = 999;
	diff.y = 999;
	QAngle newAngle;
	CBaseEntity* targetEntity;
	auto FinalBone = 0;
	for (auto i = 0; i <= ClientEntList->GetHighestEntityIndex(); i++)
	{
		Vector targetVec;
		if (!(targetEntity = static_cast<CBaseEntity*>(ClientEntList->GetClientEntity(i))))
			continue;
		if (targetEntity == Global::LocalPlayer)
			continue;

		if (!targetEntity->GetAlive() || targetEntity->GetDormant())
			continue;
		player_info_t throwaway;
		if (!Engine->GetPlayerInfo(i, &throwaway))
			continue;

		if (Options.Legit.Aimbot.EnemyOnly)
			if (targetEntity->GetTeam() == Global::LocalPlayer->GetTeam())
				continue;

		if (Options.Legit.Aimbot.DynamicHBox)
			FinalBone = g_pLegit->GetClosestBone(targetEntity);
		else
			FinalBone = Options.Legit.Aimbot.Bone;

		(targetVec = getPredictedPosition(targetEntity->GetBonePosition(FinalBone), targetEntity->GetVelocity()));
		if (targetVec == Vector(0, 0, 0))
			continue;
		newAngle = calcViewangleAdjustment(targetEntity, cmd, FinalBone, false);
		if (screenDifference(newAngle) < screenDifference(diff))
		{
			diff = newAngle;
			closestEntity = targetEntity;
		}
	}
	if (deviance)
		*deviance = diff;
	return closestEntity;
}


void cLegit::applyLinearAdjustment(int desiredX, int desiredY, int maxDistancePerSecond, float lastIteration)
{
	if (!g_pCInput->m_fMouseActive)
		return;
	auto maxAdjust = static_cast<float>(maxDistancePerSecond) * (Globals->realtime - lastIteration);
	float xAdjust, yAdjust;
	int width, height;
	Engine->GetScreenSize(width, height);
	auto centerX = width / 2;
	auto centerY = height / 2;
	auto negative = desiredX - centerX < 0;
	xAdjust = min(maxAdjust / 2.f, abs((float)(desiredX - centerX))) * (negative ? -1.f : 1.f);
	negative = desiredY - centerY < 0;
	if (xAdjust < (maxAdjust / 2.f))
		yAdjust = min(maxAdjust - xAdjust, abs((float)(desiredY - centerY))) * (negative ? -1.f : 1.f);
	else
		yAdjust = min(maxAdjust / 2.f, abs((float)(desiredY - centerY))) * (negative ? -1.f : 1.f);
	negative = xAdjust < 0;
	xAdjust = ceil(abs(xAdjust)) * (negative ? -1 : 1);
	negative = yAdjust < 0;
	yAdjust = ceil(abs(yAdjust)) * (negative ? -1 : 1);
	mouse_event(MOUSEEVENTF_MOVE, static_cast<int>(xAdjust), static_cast<int>(yAdjust), NULL, NULL);
}

int g_maxDeviance = 0;

int cLegit::GetClosestBone(CBaseEntity* Entity)
{
	auto AimBone = -1;
	float BestDist = Options.Legit.Aimbot.LFOV; // your FoV setting

	matrix3x4_t matrix[MAXSTUDIOBONES];

	if (!Entity->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, Engine->GetLastTimeStamp()))
		return -1;

	const model_t* pModel = Entity->GetModel();

	if (!pModel)
		return -1;

	auto pStudioModel = ModelInfo->GetStudioModel(pModel);

	if (!pStudioModel)
		return -1;

	auto set = pStudioModel->pHitboxSet(Entity->GetHitboxSet());

	if (!set)
		return -1;

	std::vector<int> Hitboxes;
	// Begin the main 20 hitboxes here.
	if (Options.Legit.Aimbot.Hitscan.Head)
		Hitboxes.emplace_back(HITBOX_HEAD);
	if (Options.Legit.Aimbot.Hitscan.Neck)
		Hitboxes.emplace_back(HITBOX_NECK);
	if (Options.Legit.Aimbot.Hitscan.LowerNeck)
		Hitboxes.emplace_back(HITBOX_LOWER_NECK);
	if (Options.Legit.Aimbot.Hitscan.Pelvis)
		Hitboxes.emplace_back(HITBOX_PELVIS);
	if (Options.Legit.Aimbot.Hitscan.Body)
		Hitboxes.emplace_back(HITBOX_BODY);
	if (Options.Legit.Aimbot.Hitscan.Thorax)
		Hitboxes.emplace_back(HITBOX_THORAX);
	if (Options.Legit.Aimbot.Hitscan.Chest)
		Hitboxes.emplace_back(HITBOX_CHEST);
	if (Options.Legit.Aimbot.Hitscan.UpperChest)
		Hitboxes.emplace_back(HITBOX_UPPER_CHEST);
	if (Options.Legit.Aimbot.Hitscan.RightThigh)
		Hitboxes.emplace_back(HITBOX_RIGHT_THIGH);
	if (Options.Legit.Aimbot.Hitscan.LeftThigh)
		Hitboxes.emplace_back(HITBOX_LEFT_THIGH);
	if (Options.Legit.Aimbot.Hitscan.RightCalf)
		Hitboxes.emplace_back(HITBOX_RIGHT_CALF);
	if (Options.Legit.Aimbot.Hitscan.LeftCalf)
		Hitboxes.emplace_back(HITBOX_LEFT_CALF);
	if (Options.Legit.Aimbot.Hitscan.RightFoot)
		Hitboxes.emplace_back(HITBOX_RIGHT_FOOT);
	if (Options.Legit.Aimbot.Hitscan.LeftFoot)
		Hitboxes.emplace_back(HITBOX_LEFT_FOOT);
	if (Options.Legit.Aimbot.Hitscan.RightHand)
		Hitboxes.emplace_back(HITBOX_RIGHT_HAND);
	if (Options.Legit.Aimbot.Hitscan.LeftHand)
		Hitboxes.emplace_back(HITBOX_LEFT_HAND);
	if (Options.Legit.Aimbot.Hitscan.RightUpperArm)
		Hitboxes.emplace_back(HITBOX_RIGHT_UPPER_ARM);
	if (Options.Legit.Aimbot.Hitscan.RightForeArm)
		Hitboxes.emplace_back(HITBOX_RIGHT_FOREARM);
	if (Options.Legit.Aimbot.Hitscan.LeftUpperArm)
		Hitboxes.emplace_back(HITBOX_LEFT_UPPER_ARM);
	if (Options.Legit.Aimbot.Hitscan.LeftForeArm)
		Hitboxes.emplace_back(HITBOX_LEFT_FOREARM);

	for (auto Hitbox : Hitboxes)
	{
		auto box = set->pHitbox(Hitbox);

		if (!box)
			continue;

		QAngle BAngles;
		auto EyePos = Global::LocalPlayer->GetEyePosition();
		auto BonePos = Vector(matrix[box->bone][0][3], matrix[box->bone][1][3], matrix[box->bone][2][3]);

		if (!Entity->IsHitboxVisible(Entity, BonePos))
			continue;

		CalcAngle(EyePos, BonePos, BAngles);
		auto FOV = GetFov(Global::pCmd->viewangles, BAngles);

		if (FOV <= BestDist)
		{
			BestDist = FOV;
			AimBone = box->bone;
		}
	}

	return AimBone;
}

void cLegit::subtleAim(CUserCmd* cmd, int bone)
{
	if (Options.Menu.Opened)
		return;

	static float lastIteration = 0;
	if (Globals->realtime - lastIteration > 0.2f)
		lastIteration = Globals->realtime;
	CBaseEntity* target;
	QAngle deviance;
	auto FinalBone = 0;

	auto localPlayerWep = Global::LocalPlayer->GetWeapon();

	auto gravityStrength = Options.Legit.Aimbot.AimSpeed;
	g_maxDeviance = Options.Legit.Aimbot.LFOV;

	if (localPlayerWep)
	{
		if (localPlayerWep->GetWeaponType() == WEPCLASS_INVALID || localPlayerWep->GetWeaponType() == WEPCLASS_KNIFE)
			return;
		if (localPlayerWep->GetWeaponType() == WEPCLASS_RIFLE || localPlayerWep->GetWeaponType() == WEPCLASS_MACHINEGUN || localPlayerWep->GetWeaponType() == WEPCLASS_SMG)
		{
			auto clip = *reinterpret_cast<int*>(DWORD(localPlayerWep) + offsets.m_iClip1);
			if (clip > 0 && cmd->buttons & IN_ATTACK)
			{
				gravityStrength *= Options.Legit.Aimbot.MultiplySpeed;
				g_maxDeviance += Options.Legit.Aimbot.FOVBOOST;
			}
		}
	}

	if (!(target = getTargetNearestCrosshair(cmd, &deviance)))
		return;

	if (Options.Legit.Aimbot.VisibleOnly)
	{
		if (Options.Legit.Aimbot.DynamicHBox)
		{
			FinalBone = g_pLegit->GetClosestBone(target);
			if (!target->IsVisible(FinalBone))
				return;
		}
		else
		{
			FinalBone = Options.Legit.Aimbot.Bone;
			if (!target->IsVisible(FinalBone))
				return;
		}
	}
	else
	{
		FinalBone = Options.Legit.Aimbot.Bone;
		if (!target->IsVisible(FinalBone))
			return;
	}

	auto desiredAngle = calcViewangleAdjustment(target, cmd, FinalBone, false) + cmd->viewangles;
	Vector targetPos, targetScrPos;
	AngleVectors(desiredAngle, &targetPos, nullptr, nullptr);
	targetPos += Global::LocalPlayer->GetEyePosition();
	if (!WorldToScreen(targetPos, targetScrPos))
		return;

	if (screenDifference(deviance) < g_maxDeviance)
		applyLinearAdjustment(targetScrPos.x, targetScrPos.y, gravityStrength, lastIteration);
	lastIteration = Globals->realtime;
}

int cLegit::GetTargetClosest()
{

	auto pFov = Options.Legit.Aimbot.Fov;
	auto iBestTarget = -1;
	for (auto i = 0; i <= Globals->maxClients; i++)
	{
		CBaseEntity* pTarget = nullptr;;
		QAngle Angles;
		if (!ValidEntity(i))
			continue;
		if (!(pTarget = ClientEntList->GetClientEntity(i)))
			continue;

		CalcAngle(Global::LocalPlayer->GetEyePosition(), pTarget->GetBonePosition(Options.Legit.Aimbot.Bone), Angles);
		auto fov = GetFov(Global::pCmd->viewangles, Angles);

		if (fov < pFov)
		{
			pFov = fov;
			iBestTarget = i;
		}
	}
	if (iBestTarget != -1)
		return iBestTarget;
	return -1;
}

QAngle AnglesToPixels(QAngle SourceAngles, QAngle FinalAngles, float sensitivity)
{
	QAngle delta = SourceAngles - FinalAngles;
	delta.Normalize();

	float xMove = (-delta.x) / (0.022f * sensitivity * 1);
	float yMove = (delta.y) / (0.022f * sensitivity * 1);

	return QAngle(yMove, xMove, 0.0f);
}

void cLegit::GoToTarget(CBaseEntity* pTarget)
{
	auto sensi = Cvar->FindVar(XorStr("sensitivity"));
	auto sensitivity = sensi->GetFloat();

	static QAngle qSetAngles;
	QAngle angles;
	Engine->GetViewAngles(qSetAngles);
	qSetAngles.Normalize();
	if (pTarget->GetHealth() <= 0)
		return;
	CalcAngle(Global::LocalPlayer->GetEyePosition(),
		pTarget->GetBonePosition(Options.Legit.Aimbot.Bone),
		Global::pCmd->viewangles);
	if (Options.Legit.Aimbot.RCS)
		Global::pCmd->viewangles -= Global::LocalPlayer->GetPunch() * 2.0f;

	auto qDelta = Global::pCmd->viewangles - qSetAngles;
	qDelta.Normalize();

	Global::pCmd->viewangles.x = qSetAngles.x + qDelta.x / Options.Legit.Aimbot.Smooth[0];
	Global::pCmd->viewangles.y = qSetAngles.y + qDelta.y / Options.Legit.Aimbot.Smooth[1];
	Global::pCmd->viewangles.Normalize();

	if (Options.AntiCheat.SMAC)
	{
		auto Pixels = AnglesToPixels(qSetAngles, Global::pCmd->viewangles, sensitivity);
		Global::pCmd->mousedx = Pixels.x;
		Global::pCmd->mousedy = Pixels.y;
	}

	if (!Options.Legit.Aimbot.SilentAim)
		Engine->SetViewAngles(Global::pCmd->viewangles);
	 

	/*static QAngle qSetAngles;
	Engine->GetViewAngles(qSetAngles);
	qSetAngles.Normalize();
	if (pTarget->GetHealth() <= 0)
		return;
	CalcAngle(Global::LocalPlayer->GetEyePosition(),
		pTarget->GetBonePosition(Options.Legit.Aimbot.Bone),
		Global::pCmd->viewangles);
	if (Options.Legit.Aimbot.RCS)
		Global::pCmd->viewangles -= Global::LocalPlayer->GetPunch() * 2.00f;
	auto qDelta = Global::pCmd->viewangles - qSetAngles;
	qDelta.Normalize();

	Global::pCmd->viewangles.x = qSetAngles.x + qDelta.x / Options.Legit.Aimbot.Smooth[0];
	Global::pCmd->viewangles.y = qSetAngles.y + qDelta.y / Options.Legit.Aimbot.Smooth[1];
	Global::pCmd->viewangles.Normalize();

	auto Pixels = AnglesToPixels(qSetAngles, Global::pCmd->viewangles, sensitivity);
	Global::pCmd->mousedx = Pixels.x;
	Global::pCmd->mousedy = Pixels.y;

	if (!Options.Legit.Aimbot.SilentAim)
		Engine->SetViewAngles(Global::pCmd->viewangles);*/
}

void cLegit::Aimbot()
{
	if (!Global::LocalPlayer->GetWeapon()->IsGun() || Global::LocalPlayer->GetWeapon()->IsEmpty() || Options.Legit.Aimbot.Fov <= 0)
		return;
	CBaseEntity* pTarget = nullptr;
	auto iTarget = -1;
	if (!(Global::pCmd->buttons & IN_ATTACK) || !pTarget)
		iTarget = this->GetTargetClosest();

	if (iTarget != -1)
		pTarget = ClientEntList->GetClientEntity(iTarget);

	if (pTarget && Global::pCmd->buttons & IN_ATTACK)
		GoToTarget(pTarget);
}

CBaseEntity* cLegit::getTargetUnderCrosshair(CUserCmd* cmd, bool enemiesOnly, bool visibleOnly, trace_t* trOut) const
{
	Vector vEnd;
	QAngle view;

	trace_t tr;
	Ray_t ray;

	CTraceFilter filter;
	filter.pSkip = Global::LocalPlayer;

	Engine->GetViewAngles(view);
	view += Global::LocalPlayer->GetPunch() * 2.0f;

	AngleVectors(view, &vEnd, nullptr, nullptr);

	vEnd = vEnd * 8192.0f + Global::LocalPlayer->GetEyePosition();

	ray.Init(Global::LocalPlayer->GetEyePosition(), vEnd);
	EngineTrace->TraceRay(ray, 0x46004003, &filter, &tr);

	if (!tr.m_pEnt)
		return nullptr;
	if (tr.m_pEnt->GetTeam() == Global::LocalPlayer->GetTeam() && enemiesOnly)
		return nullptr;
	if (tr.hitgroup <= 10 && tr.hitgroup > 0)
	{
		if (trOut)
			*trOut = tr;
		return tr.m_pEnt;
	}
	else
		return nullptr;
}

bool cLegit::isNotAbleToShoot(CBaseEntity* entity, CBaseCombatWeapon* weapon)
{
	auto serverTime = float(entity->GetTickBase()) * Globals->interval_per_tick;
	return (weapon->GetNextPrimaryAttack() > serverTime);
}

void cLegit::triggerbot(CUserCmd* cmd)
{
	if (!GetAsyncKeyState(Options.Legit.Trigger.Key)) return;
	CBaseEntity* target = nullptr;
	auto bShoot = false;
	auto localPlayerWep = Global::LocalPlayer->GetWeapon();
	if (!localPlayerWep)return;
	auto maxdist = localPlayerWep->GetCSWpnData()->m_flRange;//as far as a bullet can travel

	trace_t tr;
	if ((target = getTargetUnderCrosshair(cmd, Options.Legit.Trigger.TriggerFriends, true, &tr)))
	{
		auto vecToTarget = tr.endpos - Global::LocalPlayer->GetEyePosition();
		switch (Options.Legit.Trigger.Filter)
		{
		case FILTER_MOSTDAMAGE:
		{
			if (tr.hitgroup > HITGROUP_GENERIC && tr.hitgroup <= HITGROUP_STOMACH)
				bShoot = true;
			break;
		}
		case FILTER_BODYONLY:
		{
			if (tr.hitgroup > HITGROUP_HEAD && tr.hitgroup <= HITGROUP_RIGHTLEG)
				bShoot = true;
			break;
		}
		case FILTER_BODYNOARMS:
		{
			if (tr.hitgroup > HITGROUP_HEAD && tr.hitgroup <= HITGROUP_STOMACH)
				bShoot = true;
			break;
		}
		case FILTER_HEADONLY:
		{
			if (tr.hitgroup == HITGROUP_HEAD)
				bShoot = true;
			break;
		}
		case FILTER_ARMSONLY:
		{
			if (tr.hitgroup > HITGROUP_LEFTARM && tr.hitgroup <= HITGROUP_STOMACH)
				bShoot = true;
			break;
		}
		default:
			bShoot = true;
			break;
		}
		if (vecToTarget.Length() < maxdist && bShoot)
		{
			float nextPrimaryAttack = Global::LocalPlayer->GetWeapon()->GetNextPrimaryAttack();
			float tick = Global::LocalPlayer->GetTickBase() * Globals->interval_per_tick;

			if (nextPrimaryAttack > tick)
			{
				if (Global::LocalPlayer->GetWeapon()->GetItemDefinitionIndex() == WEAPON_REVOLVER)
					cmd->buttons &= ~IN_ATTACK2;
				else
					cmd->buttons &= ~IN_ATTACK;
			}
			else
			{

				if (Global::LocalPlayer->GetWeapon()->GetItemDefinitionIndex() == WEAPON_REVOLVER)
					cmd->buttons |= IN_ATTACK2;
				else
					cmd->buttons |= IN_ATTACK;
			}
		}
	}
}
