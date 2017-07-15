#include "Cheats.h"
cRage* g_pRage = new cRage;

void cRage::Invoke(CUserCmd* pCmd, bool& bSendThisPacket, bool bCanFire)
{
	CFixMove fixmove;
	this->MoniterNoSpread(pCmd);
	fixmove.Start();

	if (Options.Rage.AntiAim.Enabled && !(pCmd->buttons & IN_ATTACK))
		this->AntiAim(pCmd, bSendThisPacket);
	if (Options.Rage.Aimbot.Enabled)
	{
		this->EnginePred(pCmd);

		if (bCanFire)
			this->Aimbot(pCmd);
	}
	fixmove.End();

	//SetViewAngles(pCmd, pCmd->viewangles);
}      

//stole all of this to rewrite it later
bool cRage::GetHitbox(CBaseEntity* target, Hitbox* hitbox)
{
	matrix3x4a_t matrix[MAXSTUDIOBONES];

	if (!target->SetupBones(matrix, MAXSTUDIOBONES, BONE_USED_BY_HITBOX, 0))
		return false;

	studiohdr_t *hdr = ModelInfo->GetStudioModel(target->GetModel());

	if (!hdr) {

		return false;
	}
	mstudiohitboxset_t *hitboxSet = hdr->pHitboxSet(target->GetHitboxSet());
	mstudiobbox_t *untransformedBox = hitboxSet->pHitbox(hitbox->hitbox);

	Vector bbmin = untransformedBox->bbmin;
	Vector bbmax = untransformedBox->bbmax;
	// 80% of radius stops aiming outside of hitboxes at higher resolution
	if (untransformedBox->radius != -1.f)
	{
		bbmin -= Vector(untransformedBox->radius*.8, untransformedBox->radius*.8, untransformedBox->radius*.8);
		bbmax += Vector(untransformedBox->radius*.8, untransformedBox->radius*.8, untransformedBox->radius*.8);
	}

	Vector points[] = { ((bbmin + bbmax) * .5f),
		Vector(bbmin.x, bbmin.y, bbmin.z),
		Vector(bbmin.x, bbmax.y, bbmin.z),
		Vector(bbmax.x, bbmax.y, bbmin.z),
		Vector(bbmax.x, bbmin.y, bbmin.z),
		Vector(bbmax.x, bbmax.y, bbmax.z),
		Vector(bbmin.x, bbmax.y, bbmax.z),
		Vector(bbmin.x, bbmin.y, bbmax.z),
		Vector(bbmax.x, bbmin.y, bbmax.z) };

	for (int index = 1; index < 9; index++) // Skip first point (center of hitbox)
	{
		VectorTransform(points[index], matrix[untransformedBox->bone], hitbox->points[index]);
	}
	return true;
}



bool cRage::GetBestPoint(CBaseEntity* target, Hitbox* hitbox, BestPoint* point)
{
	for (int index = 0; index <= 8; ++index)
	{
		int temp_damage = g_pAutowall.GetDamage(hitbox->points[index]);
		if ((point->dmg < temp_damage)) // update best point across all if a higher damage point is found
		{
			point->dmg = temp_damage;
			point->point = hitbox->points[index];
			point->index = index;
		}
	}
	return (point->dmg > Options.Rage.AutoWall.MinDamage);
}

bool cRage::CustomMultipoint(CBaseEntity* target, Hitbox* hitbox, BestPoint* point)
{
	auto center = hitbox->points[0];

	if (hitbox->hitbox == HITBOX_HEAD)
	{
		auto high = ((hitbox->points[3] + hitbox->points[5]) * .5f);

		auto pitch = target->GetEyeAngles().x;
		if ((pitch > 0.f) && (pitch < 88.9f))
		{
			auto height = (((high - hitbox->points[0]) / 3) * 4);
			auto new_height = (hitbox->points[0] + (height * (pitch / 89.f)));

			hitbox->points[0] = new_height;
			point->flags |= FL_HIGH;
		}
		else if ((pitch < 292.5f) && (pitch > 270.9f))
		{
			hitbox->points[0] -= Vector(0.f, 0.f, 1.f);
			point->flags |= FL_LOW;
		}
	}
	if (Options.Rage.Aimbot.Hitscan.Point > 0)
	{


		for (auto index = 0; index < Options.Rage.Aimbot.Hitscan.Point; index++)
		{
			int temp_damage = g_pAutowall.bIsPointPenetrable(hitbox->points[index]);//GetDamage(hitbox->points[index]);

			if ((point->dmg < temp_damage))
			{
				point->dmg = temp_damage;
				point->point = hitbox->points[index];
				point->index = index;
			}
		}
	}
	else
	{
		point->dmg = g_pAutowall.bIsPointPenetrable(hitbox->points[0]);
		point->point = hitbox->points[0];
		point->index = 0;
	}
	return (point->dmg >= Options.Rage.AutoWall.MinDamage);
}

int hitboxes[8] =
{
	HITBOX_PELVIS,
	HITBOX_CHEST,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_HEAD
};

int Allhitboxs[21] =
{
	HITBOX_HEAD,
	HITBOX_NECK,
	HITBOX_LOWER_NECK,
	HITBOX_PELVIS,
	HITBOX_BODY,
	HITBOX_THORAX,
	HITBOX_CHEST,
	HITBOX_UPPER_CHEST,
	HITBOX_RIGHT_THIGH,
	HITBOX_LEFT_THIGH,
	HITBOX_RIGHT_CALF,
	HITBOX_LEFT_CALF,
	HITBOX_RIGHT_FOOT,
	HITBOX_LEFT_FOOT,
	HITBOX_RIGHT_HAND,
	HITBOX_LEFT_HAND,
	HITBOX_RIGHT_UPPER_ARM,
	HITBOX_RIGHT_FOREARM,
	HITBOX_LEFT_UPPER_ARM,
	HITBOX_LEFT_FOREARM,
	HITBOX_MAX		
};

bool cRage::BestAimPointAll(CBaseEntity* target, Vector& hitboxs)
{
	auto highest_damage = 0;
	for (auto i = 0; i < 8; i++)
	{
		BestPoint aim_point;
		if (Options.Rage.Aimbot.AAA.bDisableHead[target->index])
			if (i == HITBOX_HEAD)
				continue;
		Hitbox hitbox(hitboxes[i]);
		GetHitbox(target, &hitbox);

		if (!GetBestPoint(target, &hitbox, &aim_point)) {
			continue;
		}

		if (aim_point.dmg > highest_damage) {
			highest_damage = aim_point.dmg;
			hitboxs = aim_point.point;
		}
	}
	return(highest_damage > Options.Rage.AutoWall.MinDamage);

}

bool cRage::BestAimPoint(CBaseEntity* target, Vector& hitboxs)
{
	BestPoint aim_point;

	for (auto i = 0; i < 20; i++)
	{
		if (Options.Rage.Aimbot.AAA.bDisableHead[target->index])
			if (i == HITBOX_HEAD)
				continue;
		Hitbox hitbox(Allhitboxs[i]);
		GetHitbox(target, &hitbox);

		if (!GetBestPoint(target, &hitbox, &aim_point))
			continue;
	}

	if (aim_point.dmg > Options.Rage.AutoWall.MinDamage)
	{
		hitboxs = aim_point.point;
		return true;
	}


	return false;
}



bool cRage::BestAimPointHitbox(CBaseEntity* target, Vector& hitbox)
{
	BestPoint aim_point;

	auto hitboxnum = 0;

	switch (Options.Rage.Aimbot.Hitbox)
	{
	case 0:
		hitboxnum = 3;
		break;
	case 1:
		hitboxnum = 6;
		break;
	case 2:
		break;
	case 3:
		hitboxnum = 4;
		break;
	case 4:
		hitboxnum = 7;
		break;
	case 5:
		hitboxnum = 1;
		break;
	case 6:
		hitboxnum = 0;
		break;
	default:
		hitboxnum = 0;
		break;
	}
	if (Options.Rage.Aimbot.AAA.bDisableHead[target->index])
		if (hitboxnum == HITBOX_HEAD)
			hitboxnum == HITBOX_NECK;
	Hitbox hitboxx(hitboxnum);
	GetHitbox(target, &hitboxx);

	if (!GetBestPoint(target, &hitboxx, &aim_point))
		return false;

	if (aim_point.dmg > Options.Rage.AutoWall.MinDamage)
	{
		hitbox = aim_point.point;
		return true;
	}

	return false;
}

bool cRage::IsValidEntity(int iEnt)
{
	CBaseEntity* pEnt = nullptr; player_info_t pTemp;
		
	if ((pEnt = ClientEntList->GetClientEntity(iEnt)))
		if (Engine->GetPlayerInfo(iEnt,&pTemp))
			if (!(pEnt == Global::LocalPlayer))
			{
				auto vecTemp = pEnt->GetBonePosition(Options.Rage.Aimbot.Hitbox);
				if (Options.Rage.Aimbot.AAA.bone[iEnt] != 0)
					vecTemp = pEnt->GetBonePosition((Options.Rage.Aimbot.AAA.bone[iEnt] - 1));
				if (!(Options.Rage.Aimbot.EnemyOnly)
					|| pEnt->GetTeam() != Global::LocalPlayer->GetTeam())
					if (!pEnt->GetDormant())
						if (pEnt->GetHealth() > 0)
							if (!pEnt->GetImmune())
								if (Options.Rage.Aimbot.HitScans == 0 &&
									Options.Rage.AutoWall.MinDamage <=
									g_pAutowall.bIsPointPenetrable(vecTemp)
									|| Options.Rage.Aimbot.HitScans >= 1)
									return true;
			}
	return false;
}// this is dirty but it is compact
void SetupHitboxs(std::vector<int>&Hitboxes)
{
	if (Options.Rage.Aimbot.Hitscan.Head)
		Hitboxes.push_back(HITBOX_HEAD);
	if (Options.Rage.Aimbot.Hitscan.Neck)
		Hitboxes.push_back(HITBOX_NECK);
	if (Options.Rage.Aimbot.Hitscan.LowerNeck)
		Hitboxes.push_back(HITBOX_LOWER_NECK);
	if (Options.Rage.Aimbot.Hitscan.Pelvis)
		Hitboxes.push_back(HITBOX_PELVIS);
	if (Options.Rage.Aimbot.Hitscan.Body)
		Hitboxes.push_back(HITBOX_BODY);
	if (Options.Rage.Aimbot.Hitscan.Thorax)
		Hitboxes.push_back(HITBOX_THORAX);
	if (Options.Rage.Aimbot.Hitscan.Chest)
		Hitboxes.push_back(HITBOX_CHEST);
	if (Options.Rage.Aimbot.Hitscan.UpperChest)
		Hitboxes.push_back(HITBOX_UPPER_CHEST);
	if (Options.Rage.Aimbot.Hitscan.RightThigh)
		Hitboxes.push_back(HITBOX_RIGHT_THIGH);
	if (Options.Rage.Aimbot.Hitscan.LeftThigh)
		Hitboxes.push_back(HITBOX_LEFT_THIGH);
	if (Options.Rage.Aimbot.Hitscan.RightCalf)
		Hitboxes.push_back(HITBOX_RIGHT_CALF);
	if (Options.Rage.Aimbot.Hitscan.LeftCalf)
		Hitboxes.push_back(HITBOX_LEFT_CALF);
	if (Options.Rage.Aimbot.Hitscan.RightFoot)
		Hitboxes.push_back(HITBOX_RIGHT_FOOT);
	if (Options.Rage.Aimbot.Hitscan.LeftFoot)
		Hitboxes.push_back(HITBOX_LEFT_FOOT);
	if (Options.Rage.Aimbot.Hitscan.RightHand)
		Hitboxes.push_back(HITBOX_RIGHT_HAND);
	if (Options.Rage.Aimbot.Hitscan.LeftHand)
		Hitboxes.push_back(HITBOX_LEFT_HAND);
	if (Options.Rage.Aimbot.Hitscan.RightUpperArm)
		Hitboxes.push_back(HITBOX_RIGHT_UPPER_ARM);
	if (Options.Rage.Aimbot.Hitscan.RightForeArm)
		Hitboxes.push_back(HITBOX_RIGHT_FOREARM);
	if (Options.Rage.Aimbot.Hitscan.LeftUpperArm)
		Hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
	if (Options.Rage.Aimbot.Hitscan.LeftForeArm)
		Hitboxes.push_back(HITBOX_LEFT_UPPER_ARM);
}
bool cRage::CustomHitscans(CBaseEntity* target, Vector& hitboxs)
{
	BestPoint aim_point;
	std::vector<int>Hitboxs;
	Hitboxs.clear();
	SetupHitboxs(Hitboxs);
	for (auto i = 0; i < Hitboxs.size(); i++)
	{
		if (i > Hitboxs.size() - 1)
			continue;
		if (Options.Rage.Aimbot.AAA.bDisableHead[target->index])
			if (Hitboxs[i] == HITBOX_HEAD)
				continue;
		Hitbox hitbox(Hitboxs[i]);
		GetHitbox(target, &hitbox);
		if (!CustomMultipoint(target, &hitbox, &aim_point))
			continue;
	}

	if (aim_point.dmg > Options.Rage.AutoWall.MinDamage)
	{
		hitboxs = aim_point.point;
		return true;
	}


	return false;
}

enum eTargeting
{
	TARGETBY_FOV,
	TARGETBY_HEALTH,
	TARGETBY_DISTANCE,
	TARGETBY_FIRSTVALID,
	TARGETBY_NEXTSHOT,
	TARGETBY_THREAT,
	TARGETBY_VISIBLEBONE,
	TARGETBY_DAMAGE
};
float cRage::AimNearPlayer(CBaseEntity* pEnt)
{
	auto src = pEnt->GetEyePosition();
	auto dst = Global::LocalPlayer->GetEyePosition();
	auto forward = src - dst;
	QAngle Product;
	VectorAngles(forward, Product);
	Product.Normalize();
	static auto flMaxDif = 180.f;
	auto fldif = Product.y;
	auto flPercent = 1.f - abs(fldif / flMaxDif);
	return flPercent;
}

void cRage::StopPlayer(CUserCmd* pCmd)
{
	auto vel = Global::LocalPlayer->GetVelocity().Length();
	if(Options.Rage.Aimbot.StopType == 1)
	{
		if (vel <= 60)
		{
			pCmd->sidemove = 0.00f;
			pCmd->forwardmove = 0.00f;
		}
		else
		{
			pCmd->sidemove = -pCmd->sidemove;
			pCmd->forwardmove = -pCmd->forwardmove;
		}
	}
	if (Options.Rage.Aimbot.StopType == 2)
	{
		if (vel <= 60)
		{
			pCmd->sidemove = 0.00f;
			pCmd->forwardmove = 0.00f;
		}
		else
		{
			pCmd->sidemove = -pCmd->sidemove;
			pCmd->forwardmove = -pCmd->forwardmove;
		}
		pCmd->buttons |= IN_DUCK;
	}
	if (Options.Rage.Aimbot.StopType == 3);
	{
		if (vel <= 60)
		{
			pCmd->sidemove = 0.00f;
			pCmd->forwardmove = 0.00f;
			pCmd->upmove = 0.00f;
		}
		else
		{
			pCmd->sidemove = -pCmd->sidemove;
			pCmd->forwardmove = -pCmd->forwardmove;
			pCmd->upmove = -pCmd->upmove;
		}
	}
	if (Options.Rage.Aimbot.StopType == 4)
	{

		if (vel <= 60)
		{
			pCmd->sidemove = 0.00f;
			pCmd->forwardmove = 0.00f;
			pCmd->upmove = 0.00f;
		}
		else
		{
			pCmd->sidemove = -pCmd->sidemove;
			pCmd->forwardmove = -pCmd->forwardmove;
			pCmd->upmove = -pCmd->upmove;
		}
		pCmd->buttons |= IN_DUCK;
	}
}

int cRage::TargetSelection(CUserCmd* pCmd)
{
	auto flFOV = 360.f;
	auto flDistance = 8192.f;
	auto flThreatLevel = 0.f;
	auto flHealth = 101.f;
	auto flDamage = 0.f;
	auto iBestTarget = -1;
	for(auto i = 0; i <= ClientEntList->GetHighestEntityIndex();i++)
	{
		if (!this->IsValidEntity(i))
			continue;
		auto pEnt = ClientEntList->GetClientEntity(i);
		auto vecHitbox = pEnt->GetBonePosition(Options.Rage.Aimbot.Hitbox);
		if (Options.Rage.Aimbot.AAA.bone[iBestTarget] != 0)
			vecHitbox = pEnt->GetBonePosition(Options.Rage.Aimbot.AAA.bone[iBestTarget] - 1);
		if ( Options.Rage.Aimbot.Targeting ==  0)
		{
			QAngle TempTargetAbs;
			CalcAngle(Global::LocalPlayer->GetEyePosition(), vecHitbox, TempTargetAbs);
			auto flTempFOV = GetFov(pCmd->viewangles, TempTargetAbs);
			if(flTempFOV < flFOV)
			{
				Vector TempHitbox;
				if (Options.Rage.Aimbot.HitScans == 0
					|| Options.Rage.Aimbot.HitScans == 1 && BestAimPointAll(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 2 && BestAimPointHitbox(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 3 && BestAimPoint(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 4 && CustomHitscans(pEnt, TempHitbox))
				{
					flFOV = flTempFOV;
					iBestTarget = i;
				}
			}
		}
		if ( Options.Rage.Aimbot.Targeting ==  1)
		{
			auto flTempHealth = pEnt->GetHealth();
			if(flTempHealth < flHealth)
			{
				Vector TempHitbox;
				if (Options.Rage.Aimbot.HitScans == 0
					|| Options.Rage.Aimbot.HitScans == 1 && BestAimPointAll(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 2 && BestAimPointHitbox(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 3 && BestAimPoint(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 4 && CustomHitscans(pEnt, TempHitbox))
				{
					flHealth = flTempHealth;
					iBestTarget = i;
				}
			}
		}
		if ( Options.Rage.Aimbot.Targeting ==  2)
		{
			QAngle TempTargetAbs;
			CalcAngle(Global::LocalPlayer->GetEyePosition(), vecHitbox, TempTargetAbs);
			auto flTempFOVs = GetFov(pCmd->viewangles, TempTargetAbs);// shouldnt these be skipped by the if ( Options.Rage.Aimbot.Targeting ==  label? o well gey names inc
			auto flTempDistance = VectorDistance(Global::LocalPlayer->GetOrigin(), pEnt->GetOrigin());
			if(flTempDistance < flDistance && flTempFOVs < flFOV)
			{
				Vector TempHitbox;
				if (Options.Rage.Aimbot.HitScans == 0
					|| Options.Rage.Aimbot.HitScans == 1 && BestAimPointAll(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 2 && BestAimPointHitbox(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 3 && BestAimPoint(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 4 && CustomHitscans(pEnt, TempHitbox))
				{
					flFOV = flTempFOVs;
					flDistance = flTempDistance;
					iBestTarget = i;
				}
				
			}
		}
		if ( Options.Rage.Aimbot.Targeting ==  3)// Saw this on UC a bit ago so Im gonna improve it a bit;
		{
			auto flTempdistance = VectorDistance(Global::LocalPlayer->GetOrigin(), pEnt->GetOrigin());
			auto flTempHealths = pEnt->GetHealth();
			auto flTempThreat = flTempHealths / flTempdistance;
			flTempThreat += static_cast<int>(this->AimNearPlayer(pEnt));
			if (pEnt->IsTargetingLocal())
				flTempThreat += 100;
			if(flTempThreat > flThreatLevel)
			{
				Vector TempHitbox;
				if (Options.Rage.Aimbot.HitScans == 0
					|| Options.Rage.Aimbot.HitScans == 1 && BestAimPointAll(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 2 && BestAimPointHitbox(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 3 && BestAimPoint(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 4 && CustomHitscans(pEnt, TempHitbox))
				{
					flThreatLevel = flTempThreat;
					iBestTarget = i;
				}
			
			}
		}// now its p :D
		if ( Options.Rage.Aimbot.Targeting ==  4)// prob should of said "Hitable bone" but eh
		{
			if (Options.Rage.AutoWall.MinDamage <= g_pAutowall.bIsPointPenetrable(vecHitbox))
				iBestTarget = i; 
		}
		if ( Options.Rage.Aimbot.Targeting ==  5)
		{
			auto flTempDamage = g_pAutowall.bIsPointPenetrable(vecHitbox);
			if(flTempDamage > flDamage)
			{
				Vector TempHitbox;
				if (Options.Rage.Aimbot.HitScans == 0
					|| Options.Rage.Aimbot.HitScans == 1 && BestAimPointAll(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 2 && BestAimPointHitbox(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 3 && BestAimPoint(pEnt, TempHitbox)
					|| Options.Rage.Aimbot.HitScans == 4 && CustomHitscans(pEnt, TempHitbox))
				{
					flDamage = flTempDamage;
					iBestTarget = i;
				}
			}
		}
	}
	return iBestTarget;
}// 8 targeting methods? dank
enum AAPitch
{
	PITCH_NONE,
	PITCH_EMOTION,
	PITCH_ANGELDOWN,
	PITCH_ANGELUP,
	
};
enum AAYAW
{
	YAW_NONE,
	YAW_FJITTER,
	YAW_DYNAMIC,
	YAW_ELEMENT,
	YAW_BACKWARD,
	YAW_STATIC,
	YAW_FAKE1,
	YAW_FAKE2,
	YAW_FAKE3,
	YAW_ANGELBACKWARD,
	YAW_ANGELINVERSE,
};
void cRage::EnginePred(CUserCmd* pCmd)// Perfect Engine Pred thanks kelse
{
	auto MoveData = *reinterpret_cast<void**>(reinterpret_cast<DWORD>(g_pMovement) + 0x8);
	if (!g_pMoveHelper)return;
	if (!Engine->IsInGame() && !Engine->IsConnected()) return;
	if (!MoveData) return;

	//Set Your Old Frametime
	auto oldFrame = Globals->frametime;
	Globals->frametime = Globals->interval_per_tick;

	//Set Host to local Player
	g_pMoveHelper->SetHost(Global::LocalPlayer);
	Prediction->SetupMove(Global::LocalPlayer, pCmd, nullptr,MoveData);
	g_pMovement->ProcessMovement(Global::LocalPlayer, MoveData);
	Prediction->FinishMove(Global::LocalPlayer, pCmd, MoveData);

	//restore original
	g_pMoveHelper->SetHost(nullptr);
	Globals->frametime = oldFrame;
}

void cRage::MoniterNoSpread(CUserCmd* pCmd)
{
	if (!Options.Rage.Aimbot.PsuedoSpread)
	{
		this->IsStopped = true;
		return;
	}
	if (!Global::LocalPlayer->GetWeapon())return;
	auto flMaxSpeed = Global::LocalPlayer->GetWeapon()->GetCSWpnData()->m_flMaxPlayerSpeed * 0.34;
	auto flVel = Global::LocalPlayer->GetVelocity().Length();
	if (flVel > flMaxSpeed)
	{
		this->IsStopped = false;
		if (this->IsAimbotting)
		{
			pCmd->forwardmove = flMaxSpeed - 20.f;
			pCmd->sidemove = 0.f;
		}
	}
	else
	{
		this->IsStopped = true;
	}
}


bool Edge(CBaseEntity* pLocalBaseEntity, CUserCmd* cmd, float flWall, float flCornor)
{
	Ray_t ray;
	trace_t tr;

	CTraceFilter traceFilter;
	traceFilter.pSkip = pLocalBaseEntity;

	auto bRetVal = false;
	auto vecCurPos = pLocalBaseEntity->GetEyePosition();

	for (float i = 0; i < 360; i++)
	{
		Vector vecDummy(10.f, cmd->viewangles.y, 0.f);
		vecDummy.y += i;

		NormalizeAngles2D(vecDummy);

		Vector vecForward;
		AngleVectors2D(vecDummy, vecForward);

		auto flLength = ((19.f) + ((19.f) * sin(DEG2RAD(10.f)))) + 7.f;
		vecForward *= flLength;

		ray.Init(vecCurPos, (vecCurPos + vecForward));
		EngineTrace->TraceRay(ray, MASK_SHOT, static_cast<CTraceFilter*>(&traceFilter), &tr);

		if (tr.fraction != 1.0f)
		{
			Vector qAngles;
			auto vecNegate = tr.plane.normal;

			vecNegate *= -1.f;
			VectorAngles2D(vecNegate, qAngles);

			vecDummy.y = qAngles.y;

			NormalizeAngles2D(vecDummy);
			trace_t leftTrace, rightTrace;

			Vector vecLeft;
			AngleVectors2D(vecDummy + Vector(0.f, 30.f, 0.f), vecLeft);

			Vector vecRight;
			AngleVectors2D(vecDummy - Vector(0.f, 30.f, 0.f), vecRight);

			vecLeft *= (flLength + (flLength * sin(DEG2RAD(30.f))));
			vecRight *= (flLength + (flLength * sin(DEG2RAD(30.f))));

			ray.Init(vecCurPos, (vecCurPos + vecLeft));
			EngineTrace->TraceRay(ray, MASK_SHOT, static_cast<CTraceFilter*>(&traceFilter), &leftTrace);

			ray.Init(vecCurPos, (vecCurPos + vecRight));
			EngineTrace->TraceRay(ray, MASK_SHOT, static_cast<CTraceFilter*>(&traceFilter), &rightTrace);

			if ((leftTrace.fraction == 1.f) && (rightTrace.fraction != 1.f))
				vecDummy.y -= flCornor; // left
			else if ((leftTrace.fraction != 1.f) && (rightTrace.fraction == 1.f))
				vecDummy.y += flCornor; // right			

			cmd->viewangles.y = vecDummy.y;
			cmd->viewangles.y -= flWall;
			bRetVal = true;
		}
	}
	return bRetVal;
}
void BackwardsTarget(CUserCmd* pCmd)
{
	for (auto i = 0; i <= ClientEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* target = nullptr;
		if (!(target = ClientEntList->GetClientEntity(i)))
			continue;
		if (target == Global::LocalPlayer)
				continue;
		if (Options.Rage.Aimbot.EnemyOnly
			&& target->GetTeam() == Global::LocalPlayer->GetTeam())
				continue;
			if (target->GetDormant())
				continue;
			if (target->GetHealth() <= 0)
				continue;
			if (target->GetTeam() == 0) // Make sure we dont aim at those tied bastards.
				continue;
		if (Global::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || Global::LocalPlayer->GetMoveType() == MOVETYPE_LADDER) 
			return;
		
		
		QAngle adjustment;
		CalcAngle(Global::LocalPlayer->GetEyePosition(), target->GetEyePosition(), adjustment);
		QAngle tmp;
		tmp.y = adjustment.y;


		static auto iChoked = -1;
		iChoked++;
		static auto jit = -1;
		jit++;

		if (iChoked < 14)
		{
			pCmd->viewangles.y = (tmp.y);

			if (jit <= 1)
			{
				pCmd->viewangles.y += 30.f;
			}
			else if (jit > 1 && jit <= 3)
			{
				pCmd->viewangles.y -= 30.f;
			}
			else
			{
				jit = -1;
			}
		}
		else
		{
			iChoked = -1;
		}
		pCmd->viewangles.y += 180;
	}
}
void Backwards(CUserCmd* pCmd)
{
	for (auto i = 0; i <= ClientEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* target = nullptr;
		if (!(target = ClientEntList->GetClientEntity(i)))
			continue;
		if (target == Global::LocalPlayer)
			continue;
		if (Options.Rage.Aimbot.EnemyOnly
			&& target->GetTeam() == Global::LocalPlayer->GetTeam())
			continue;
		if (target->GetDormant())
			continue;
		if (target->GetHealth() <= 0)
			continue;
		if (target->GetTeam() == 0) // Make sure we dont aim at those tied bastards.
			continue;
		if (Global::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || Global::LocalPlayer->GetMoveType() == MOVETYPE_LADDER)
			return;


		QAngle adjustment;
		CalcAngle(Global::LocalPlayer->GetEyePosition(), target->GetEyePosition(), adjustment);
		QAngle tmp;
		tmp.y = adjustment.y;

	
		pCmd->viewangles.y = (tmp.y);
		pCmd->viewangles.y += 180;
	}
}
void Element(CUserCmd* pCmd, bool& bSentThisPacket)
{

	for (auto i = 0; i <= ClientEntList->GetHighestEntityIndex(); i++)
	{
		CBaseEntity* target = nullptr;
		if (!(target = ClientEntList->GetClientEntity(i)))
			continue;
		if (target == Global::LocalPlayer)
			continue;
		if (Options.Rage.Aimbot.EnemyOnly
			&& target->GetTeam() == Global::LocalPlayer->GetTeam())
			continue;
		if (target->GetDormant())
			continue;
		if (target->GetHealth() <= 0)
			continue;
		if (Global::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || Global::LocalPlayer->GetMoveType() == MOVETYPE_LADDER) 
			return;

		QAngle adjustment;
		QAngle tmp;
		CalcAngle(Global::LocalPlayer->GetEyePosition(), target->GetEyePosition(), adjustment);
		tmp.y = adjustment.y;

		if (pCmd->tick_count % 3)
		{
			bSentThisPacket = false;
			pCmd->viewangles.y = (tmp.y + 200.f);
		}
		else
		{
			bSentThisPacket = true;
			pCmd->viewangles.y = (tmp.y + 180.f);
		}
		/*Short and Sweet*/
	}
}

float RandomFloatAA(float min, float max)
{
	return min + static_cast<float>(rand()) / (static_cast<float>(RAND_MAX / (max - min)));
}

bool bullettime() {
	if (!Global::LocalPlayer) return false;
	float flServerTime = (float)Global::LocalPlayer->GetTickBase() * Globals->interval_per_tick;
	float flNextPrimaryAttack = Global::LocalPlayer->GetWeapon()->GetNextPrimaryAttack();

	bool BulletTime = true;

	if (flNextPrimaryAttack > flServerTime) BulletTime = false;

	return BulletTime;
}

void cRage::AntiAim(CUserCmd* pCmd, bool& bSendThisPacket)
{
	auto pWeapon = Global::LocalPlayer->GetWeapon();
	if (pWeapon->GetWeaponType() == WEPCLASS_KNIFE) return;
	if (pCmd->buttons & IN_USE) return;
	if (pWeapon->GetWeaponType() == WEPCLASS_INVALID) return;
	if (Global::LocalPlayer->GetMoveType() == MOVETYPE_NOCLIP || Global::LocalPlayer->GetMoveType() == MOVETYPE_LADDER) return;
	switch (Options.Rage.AntiAim.Pitch)
	{
	case PITCH_EMOTION:
		pCmd->viewangles.x = 89.0000f;
		break;
	case PITCH_ANGELDOWN:
		pCmd->viewangles.x = 36000088.000000f;
		break;
	case PITCH_ANGELUP:
		if (pCmd->tick_count % 3)
		{
			bSendThisPacket = false;
			pCmd->viewangles.x = 89.000000;
		}
		else
		{
			bSendThisPacket = true;
			pCmd->viewangles.x = 35999912.000000;
		}
		break;
	
	}

	static auto jitter = -1;
	static auto fStatic = -1;
	static auto pJitter = 0;
	static auto pJitter2 = 0;
	static auto jitterangle = 0;
	float AACurAdjust = (Globals->curtime * 5000.0);
	float AAAdjustment = (Globals->curtime * 5000.0);
	float cCurTime = Globals->curtime * 1000.0;
	float cCurTime1 = Globals->curtime * 5000.0;
	float cCurTime2 = Globals->curtime * 5000.0;
	auto OriginalAA = pCmd->viewangles;
	static auto iChoked = -1;
	static auto jit = -1;
	switch (Options.Rage.AntiAim.Yaw)
	{
	case YAW_FJITTER:
		if (jitter <= 2)
		{
			bSendThisPacket = false;
			pCmd->viewangles.y -= 160.f;
			jitter++;
		}
		else if ( jitter > 2 && jitter  <= 3)
		{
			bSendThisPacket = true;
			pCmd->viewangles.y += 200.f;
			jitter++;
		}
		else if (jitter > 3 && jitter <= 5)
		{
			bSendThisPacket = false;
			pCmd->viewangles.y -= 180.f;
			jitter++;
		}
		else
		{
			jitter = 0;
		}
		break;
	case YAW_DYNAMIC:
		iChoked++;
		jit++;

		if (iChoked < 14)
		{
			pCmd->viewangles.y = (OriginalAA.y);

			if (jit <= 1)
			{
				pCmd->viewangles.y += 30.f;
			}
			else if (jit > 1 && jit <= 3)
			{
				pCmd->viewangles.y -= 30.f;
			}
			else
			{
				jit = -1;
			}
		}
		else
		{
			iChoked = -1;
		}
		pCmd->viewangles.y += 180;
		break;
	case YAW_ELEMENT:
		if (pCmd->tick_count % 3)
		{
			bSendThisPacket = false;
			pCmd->viewangles.y = OriginalAA.y + 200.f;
		}
		else
		{
			bSendThisPacket = true;
			pCmd->viewangles.y = OriginalAA.y + 180.f;
		}
		break;
	case YAW_BACKWARD:
		pCmd->viewangles.y += 180;
		break;
	case YAW_STATIC:
		if (fStatic <= 1)
		{
			bSendThisPacket = false;
			pCmd->viewangles.y += 90;
		}
		else if (fStatic > 1 && fStatic <= 3)
		{
			bSendThisPacket = true;
			pCmd->viewangles.y += 180;
		}
		else
		{
			fStatic = 0;
		}
		fStatic++;
		break;
	case YAW_FAKE1:
		if (pJitter <= 1)
		{
			pCmd->viewangles.x = 88;
			pCmd->viewangles.y += 135;
		}
		else if (pJitter > 1 && pJitter <= 3)
		{
			pCmd->viewangles.x = 88;
			pCmd->viewangles.y += 225;
		}
		if (pCmd->tick_count % 3)
		{
			bSendThisPacket = false;
			if (pJitter <= 1)
			{
				pCmd->viewangles.y += 45;
				pJitter += 1;
			}
			else if (pJitter > 1 && pJitter <= 3)
			{
				pCmd->viewangles.y -= 45;
				pJitter += 1;
			}
			else
			{
				pJitter = 0;
			}
		}
		else
		{
			bSendThisPacket = true;
		}
		break;
	case YAW_FAKE2:
		if (jitterangle <= 1)
		{
			pCmd->viewangles.x = 88;
			pCmd->viewangles.y += 90;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			pCmd->viewangles.x = 88;
			pCmd->viewangles.y -= 90;
		}
		if (pCmd->tick_count % 3)
		{
			bSendThisPacket = false;
			if (jitterangle <= 1)
			{
				pCmd->viewangles.y += 179;
				jitterangle += 1;
			}
			else if (jitterangle > 1 && jitterangle <= 3)
			{
				pCmd->viewangles.y -= 179;
				jitterangle += 1;
			}
			else
			{
				jitterangle = 0;
			}
		}
		else
		{
			bSendThisPacket = true;
		}
		break;
	case YAW_FAKE3:
		if (jitterangle <= 1)
		{
			pCmd->viewangles.x = 87;
			pCmd->viewangles.y += 90 + OriginalAA.y;
		}
		else if (jitterangle > 1 && jitterangle <= 3)
		{
			OriginalAA += bSendThisPacket ? 5.f : 9.f;
			pCmd->viewangles.x = 87;
			pCmd->viewangles.y -= 90 - OriginalAA.y;
		}
		if (pCmd->tick_count % 3)
		{
			bSendThisPacket = false;
			if (jitterangle <= 1)
			{
				pCmd->viewangles.y += 180 + 28 + OriginalAA.y;
				jitterangle += 1;
			}
			else if (jitterangle > 1 && jitterangle <= 3)
			{
				pCmd->viewangles.y -= 180 + OriginalAA.y ;
				jitterangle += 1;
			}
			else
			{
				jitterangle = 0;
			}
		}
		else
		{
			bSendThisPacket = true;
		}
		break;
	case YAW_ANGELBACKWARD:
		pCmd->viewangles.y = OriginalAA.y + 36000180.0;
		break;
	case YAW_ANGELINVERSE:
		pCmd->viewangles.y = 36000180.000000;
		break;
	}
	if (!Options.Rage.AntiAim.Yaw == 9 || !Options.Rage.AntiAim.Yaw == 10 || !Options.Rage.AntiAim.Pitch == 2 || !Options.Rage.AntiAim.Pitch == 3)
	Edge(Global::LocalPlayer, pCmd, 360, 45.f);
	
}
bool Hitchance()
{
	auto hitchance = 75.f + (Options.Rage.Aimbot.Hitchance / 4);
	if (Options.Rage.Aimbot.bHitchance || Options.Rage.Aimbot.bHitchanceSnipers && Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SNIPER)
	if ((1.0f - Global::LocalPlayer->GetWeapon()->GetAccuracyPenalty()) * 100.f >= hitchance)
		return true;
	if (!Options.Rage.Aimbot.bHitchance && !Options.Rage.Aimbot.bHitchanceSnipers)
		return true;
	if (Options.Rage.Aimbot.bHitchanceSnipers &&  Global::LocalPlayer->GetWeapon()->GetWeaponType() != WEPCLASS_SNIPER)
		return true;
	return false;
}

void cRage::Aimbot(CUserCmd* pCmd)
{
	/* Declarations */
	this->IsAimbotting = false;

	float server_time = Global::LocalPlayer->GetTickBase() * Globals->interval_per_tick;

	CBaseCombatWeapon* weapon = Global::LocalPlayer->GetWeapon();
	QAngle angle = pCmd->viewangles;

	auto iBestTarget = this->TargetSelection(pCmd);
	auto pWeapon = Global::LocalPlayer->GetWeapon();
	auto iClip = *reinterpret_cast<int*>(reinterpret_cast<DWORD>(pWeapon) + offsets.m_iClip1);
	//=================================
	/* Sanity Checks*/
	if (!(iClip > 0)) return;
	if (pWeapon->GetWeaponType() == WEPCLASS_KNIFE) return;
	if(iBestTarget != -1)
	{
		auto BestTarget = ClientEntList->GetClientEntity(iBestTarget);
	//=================================
		/* Hitbox Selection */
		Vector hitbox;
		if (Options.Rage.Aimbot.HitScans == 0)
			hitbox = BestTarget->GetBonePosition(Options.Rage.Aimbot.Hitbox);
		if (Options.Rage.Aimbot.HitScans == 1)
			BestAimPointAll(BestTarget, hitbox);
		if (Options.Rage.Aimbot.HitScans == 2)
			BestAimPointHitbox(BestTarget, hitbox);
		if (Options.Rage.Aimbot.HitScans == 3)
			BestAimPoint(BestTarget, hitbox);
		if (Options.Rage.Aimbot.HitScans == 4)
		CustomHitscans(BestTarget, hitbox);
		if (Options.Rage.Aimbot.AAA.bone[iBestTarget] != 0)
			hitbox = BestTarget->GetBonePosition(Options.Rage.Aimbot.AAA.bone[iBestTarget] - 1);
		//=================================

		if (hitbox != Vector(0, 0, 0))
		{
			BestTarget->GetPredicted(hitbox);

			QAngle qTarget;
			CalcAngle(Global::LocalPlayer->GetEyePosition(), hitbox, qTarget);

			auto switchback = pCmd->viewangles;
			qTarget - pCmd->viewangles;
			qTarget.Normalize();

			if(Options.Rage.Aimbot.AutoScope)
				if (!Global::LocalPlayer->IsScoped() && pWeapon->IsScopedWeapon())
					pCmd->buttons |= IN_ATTACK2;
			
			if(Options.Rage.Aimbot.AutoScope && pWeapon->IsScopedWeapon() 
				&& Global::LocalPlayer->IsScoped() || !pWeapon->IsScopedWeapon() 
				|| !Options.Rage.Aimbot.AutoScope)
			{
				//auto flSpread = pWeapon->GetWeaponSpread();

				if (Options.Rage.Aimbot.StopType > 0)
					this->StopPlayer(pCmd);
				if(IsStopped)
				if(Hitchance())
				{
					if (!Options.Rage.Aimbot.AutoShoot && pCmd->buttons & IN_ATTACK || Options.Rage.Aimbot.AutoShoot)
					{
						pCmd->viewangles = qTarget;
						if (!Options.Rage.Aimbot.SilentAim)
							Engine->SetViewAngles(pCmd->viewangles);
						pCmd->viewangles -= Global::LocalPlayer->GetPunch() * 2.00f;
						pCmd->viewangles.Normalize();
						this->IsAimbotting = true;
					}
					target = iBestTarget;
					//AimStep(BestTarget, qTarget, pCmd); // Test
					//pCmd->viewangles = qTarget;
					if (Options.Rage.Aimbot.AutoShoot)
					{
						float nextPrimaryAttack = Global::LocalPlayer->GetWeapon()->GetNextPrimaryAttack();
						float tick = Global::LocalPlayer->GetTickBase() * Globals->interval_per_tick;
						if (nextPrimaryAttack > tick)
						{
							if (Global::LocalPlayer->GetWeapon()->GetItemDefinitionIndex() == WEAPON_REVOLVER)
								pCmd->buttons &= ~IN_ATTACK2;
							else
								pCmd->buttons &= ~IN_ATTACK;
						}
						else
						{
							if (Global::LocalPlayer->GetWeapon()->GetItemDefinitionIndex() == WEAPON_REVOLVER)
								pCmd->buttons |= IN_ATTACK2;
							else
								pCmd->buttons |= IN_ATTACK;
						}
					}
				}
			}
			else
			{
				if (!Global::LocalPlayer->IsScoped() && pWeapon->IsScopedWeapon())
					pCmd->buttons |= IN_ATTACK2;
			}
		}
	}

}
void CFixMove::Start()
{
	m_oldangle = Global::pCmd->viewangles;
	m_oldforward = Global::pCmd->forwardmove;
	m_oldsidemove = Global::pCmd->sidemove;
}

void CFixMove::End()
{
	auto yaw_delta = Global::pCmd->viewangles.y - m_oldangle.y;
	float f1;
	float f2;

	if (m_oldangle.y < 0.f)
		f1 = 360.0f + m_oldangle.y;
	else
		f1 = m_oldangle.y;

	if (Global::pCmd->viewangles.y < 0.0f)
		f2 = 360.0f + Global::pCmd->viewangles.y;
	else
		f2 = Global::pCmd->viewangles.y;

	if (f2 < f1)
		yaw_delta = abs(f2 - f1);
	else
		yaw_delta = 360.0f - abs(f1 - f2);
	yaw_delta = 360.0f - yaw_delta;

	Global::pCmd->forwardmove = cos(DEG2RAD(yaw_delta)) * m_oldforward + cos(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
	Global::pCmd->sidemove = sin(DEG2RAD(yaw_delta)) * m_oldforward + sin(DEG2RAD(yaw_delta + 90.f)) * m_oldsidemove;
}