#include "Cheats.h"
class_autowall g_pAutowall;
// Begin new autowall


float class_autowall::GetHitgroupDamage(int iHitgroup)
{
	switch (iHitgroup)
	{
	case HITGROUP_GENERIC:
		return 1.0f;
	case HITGROUP_HEAD:
		return 4.0f;
	case HITGROUP_CHEST:
		return 1.0f;
	case HITGROUP_STOMACH:
		return 1.5f;
	case HITGROUP_LEFTARM:
		return 1.0f;
	case HITGROUP_RIGHTARM:
		return 1.0f;
	case HITGROUP_LEFTLEG:
		return 0.75f;
	case HITGROUP_RIGHTLEG:
		return 0.75f;
	case HITGROUP_GEAR:
		return 1.0f;
	default:
		break;
	}
	return 1.0f;
}

bool class_autowall::TraceToExit(Vector& end, trace_t& tr, float x, float y, float z, float x2, float y2, float z2, trace_t* trace)
{
	typedef bool(__fastcall* TraceToExitFn)(Vector&, trace_t&, float, float, float, float, float, float, trace_t*);
	static auto TraceToExit = reinterpret_cast<TraceToExitFn>(Memory::FindPatternIDA("client.dll", "55 8B EC 83 EC 2C F3 0F 10 75 ? 33 C0"));

	if (!TraceToExit)
	{
		return false;
	}
	_asm
	{
		push trace
		push z2
		push y2
		push x2
		push z
		push y
		push x
		mov edx, tr
		mov ecx, end
		call TraceToExit
		add esp, 0x1C
	}
}
bool class_autowall::DidHitNonWorldEntity(CBaseEntity* m_pEnt)
{
	return m_pEnt != nullptr && m_pEnt == ClientEntList->GetClientEntity(0);
}

void class_autowall::ScaleDamage(int Hitgroup, CBaseEntity* pEntity, float weapon_armor_ratio, float& current_damage)
{
	if (!pEntity)
		return;

	current_damage *= GetHitgroupDamage(Hitgroup);
	auto Armor = pEntity->GetArmor();
	if (Armor > 0)
	{
		if (Hitgroup == HITGROUP_HEAD)
		{
			auto Helmet = pEntity->HasHelmet();
			if (Helmet)
				current_damage *= (weapon_armor_ratio * 1.5f);
		}
		else
		{
			current_damage *= (weapon_armor_ratio * 0.5f);
		}
	}
}

bool class_autowall::HandleBulletPenetration(WeaponInfo_t* wpn_data, FireBulletData& data)
{
	auto enter_surface_data = Physprops->GetSurfaceData(data.enter_trace.surface.surfaceProps);
	int enter_material = enter_surface_data->game.material;
	auto enter_surf_penetration_mod = *reinterpret_cast<float*>(DWORD(enter_surface_data) + 76);

	data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
	data.current_damage *= pow((wpn_data->m_flRangeModifier), (data.trace_length * 0.002));

	if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))
		data.penetrate_count = 0;

	if (data.penetrate_count <= 0)
		return false;

	Vector dummy;
	trace_t trace_exit;
	if (!TraceToExit(dummy, data.enter_trace, data.enter_trace.endpos.x, data.enter_trace.endpos.y, data.enter_trace.endpos.z, data.direction.x, data.direction.y, data.direction.z, &trace_exit))
		return false;


	auto exit_surface_data = Physprops->GetSurfaceData(trace_exit.surface.surfaceProps);
	int exit_material = exit_surface_data->game.material;

	auto exit_surf_penetration_mod = *reinterpret_cast<float*>(DWORD(exit_surface_data) + 76);
	auto final_damage_modifier = 0.16f;
	auto combined_penetration_modifier = 0.0f;

	if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71))
	{
		combined_penetration_modifier = 3.0f;
		final_damage_modifier = 0.05f;
	}
	else
	{
		combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
	}

	if (enter_material == exit_material)
	{
		if (exit_material == 87 || exit_material == 85)
			combined_penetration_modifier = 3.0f;
		else if (exit_material == 76)
			combined_penetration_modifier = 2.0f;
	}

	auto v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
	auto v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data->m_flPenetration) * 1.25f);
	auto thickness = (trace_exit.endpos - data.enter_trace.endpos).Length();

	thickness *= thickness;
	thickness *= v34;
	thickness /= 24.0f;

	auto lost_damage = fmaxf(0.0f, v35 + thickness);

	if (lost_damage > data.current_damage)
		return false;

	if (lost_damage >= 0.0f)
		data.current_damage -= lost_damage;

	if (data.current_damage < 1.0f)
		return false;

	data.src = trace_exit.endpos;
	data.penetrate_count--;

	return true;
}

/*bool class_autowall::HandleBulletPenetration(WeaponInfo_t* wpn_data, FireBulletData& data)
{
	auto enter_surface_data = Physprops->GetSurfaceData(data.enter_trace.surface.surfaceProps);
	int enter_material = enter_surface_data->game.material;
	auto enter_surf_penetration_mod = *reinterpret_cast<float*>(DWORD(enter_surface_data) + 76);

	data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
	data.current_damage *= pow(wpn_data->m_flRangeModifier, (data.trace_length * 0.002));

	if ((data.trace_length > 3000.f) || (enter_surf_penetration_mod < 0.1f))
		data.penetrate_count = 0;

	if (data.penetrate_count <= 0)
		return false;

	Vector dummy;
	trace_t trace_exit;
	if (!TraceToExit(dummy, data.enter_trace, data.enter_trace.endpos.x, data.enter_trace.endpos.y, data.enter_trace.endpos.z, data.direction.x, data.direction.y, data.direction.z, &trace_exit))
		return false;


	auto exit_surface_data = Physprops->GetSurfaceData(trace_exit.surface.surfaceProps);
	int exit_material = exit_surface_data->game.material;

	auto exit_surf_penetration_mod = exit_surface_data->game.flPenetrationModifier;
	auto final_damage_modifier = 0.16f;
	auto combined_penetration_modifier = 0.0f;

	if (((data.enter_trace.contents & CONTENTS_GRATE) != 0) || (enter_material == 89) || (enter_material == 71))
	{
		combined_penetration_modifier = 3.0f;
		final_damage_modifier = 0.05f;
	}
	else
	{
		combined_penetration_modifier = (enter_surf_penetration_mod + exit_surf_penetration_mod) * 0.5f;
	}

	if (enter_material == exit_material)
	{
		if (exit_material == 87 || exit_material == 85)
			combined_penetration_modifier = 3.0f;
		else if (exit_material == 76)
			combined_penetration_modifier = 2.0f;
	}

	auto v34 = fmaxf(0.f, 1.0f / combined_penetration_modifier);
	auto v35 = (data.current_damage * final_damage_modifier) + v34 * 3.0f * fmaxf(0.0f, (3.0f / wpn_data->m_flPenetration) * 1.25f);
	auto thickness = (trace_exit.endpos - data.enter_trace.endpos).Length();

	thickness *= thickness;
	thickness *= v34;
	thickness /= 24.0f;

	auto lost_damage = fmaxf(0.0f, v35 + thickness);

	if (lost_damage > data.current_damage)
		return false;

	if (lost_damage >= 0.0f)
		data.current_damage -= lost_damage;

	if (data.current_damage < 1.0f)
		return false;

	data.src = trace_exit.endpos;
	data.penetrate_count--;

	return true;
}*/


bool class_autowall::SimulateFireBullet(CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon, FireBulletData& data)
{
	if (!pLocal || !pWeapon)
		return false;

	data.penetrate_count = 4;
	data.trace_length = 0.0f;

	auto wpn_data = pWeapon->GetCSWpnData();
	if (!wpn_data)
		return false;

	data.current_damage = static_cast<float>(wpn_data->m_iDamage);

	while ((data.penetrate_count > 0) && (data.current_damage >= 1.0f))
	{
		data.trace_length_remaining = wpn_data->m_flRange - data.trace_length;
		auto vecEnd = data.src + data.direction * 40.f;

		Ray_t ray;
		ray.Init(data.src, vecEnd + data.direction * data.trace_length_remaining);
		EngineTrace->TraceRay(ray, 0x4600400B, &data.filter, &data.enter_trace);

		if (data.enter_trace.fraction == 1.0f)
			break;

		if ((data.enter_trace.hitgroup <= 7) && (data.enter_trace.hitgroup > 0) && pLocal->GetTeam() != data.enter_trace.m_pEnt->GetTeam())
		{
			data.trace_length += data.enter_trace.fraction * data.trace_length_remaining;
			data.current_damage *= static_cast<float>(pow(wpn_data->m_flRangeModifier, data.trace_length * 0.002));
			ScaleDamage(data.enter_trace.hitgroup, data.enter_trace.m_pEnt, wpn_data->m_flArmorRatio, data.current_damage);

			return true;
		}

		if (!HandleBulletPenetration(wpn_data, data))
			break;
	}

	return false;
}

void sinCos2(float radians, PFLOAT sine, PFLOAT cosine)
{
	__asm
	{
		fld dword ptr[radians]
		fsincos
		mov edx, dword ptr[cosine]
		mov eax, dword ptr[sine]
		fstp dword ptr[edx]
		fstp dword ptr[eax]
	}
}

void angleVectors2(QAngle angles, Vector& f)
{
	float sp, sy, sr, cp, cy, cr;

	sinCos2(DEG2RAD(angles[0]), &sp, &cp);
	sinCos2(DEG2RAD(angles[1]), &sy, &cy);
	sinCos2(DEG2RAD(angles[2]), &sr, &cr);

	f[0] = cp * cy;
	f[1] = cp * sy;
	f[2] = -sp;
}

class_autowall::class_autowall()
{
	this->IsFuckingAutowalling = false;
}

bool class_autowall::AutoWall(CBaseEntity* pLocal, CBaseCombatWeapon* pWeapon, Vector& point)
{
	if (!pLocal)
		return false;
	if (!pLocal->GetAlive())
		return false;

	FireBulletData data;
	data.src = pLocal->GetEyePosition();
	data.filter.pSkip = pLocal;

	QAngle vecAngles;
	CalcAngle(data.src, point, vecAngles);
	angleVectors2(vecAngles, data.direction);
	data.direction.NormalizeInPlace();

	if (!SimulateFireBullet(pLocal, pWeapon, data))
		return false;

	return (data.current_damage >= Options.Rage.AutoWall.MinDamage);
}

float class_autowall::GetDamage(Vector& point)
{
	if (!Global::LocalPlayer)
		return false;
	if (!Global::LocalPlayer->GetAlive())
		return false;
	auto pWeapon = Global::LocalPlayer->GetWeapon();
	FireBulletData data;
	data.src = Global::LocalPlayer->GetEyePosition();
	data.filter.pSkip = Global::LocalPlayer;

	QAngle vecAngles;
	CalcAngle(data.src, point, vecAngles);
	angleVectors2(vecAngles, data.direction);
	data.direction.NormalizeInPlace();

	if (!SimulateFireBullet(Global::LocalPlayer, pWeapon, data))
		return false;
	return data.current_damage;
}
trace_t trace;
trace_t trace2;
float class_autowall::bIsPointPenetrable( Vector vEnd)
{
	if (Options.Rage.Aimbot.Autowall)
		return this->GetDamage(vEnd);
}

