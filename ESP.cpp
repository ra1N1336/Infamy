#include "Cheats.h"
#include "Accessors.h"
cESP* g_pESP = new cESP;
CNadeTracer* NadeTracer = new CNadeTracer;

cESP::cESP()
{
	width = 0;
	height = 0;

	espColor = Color(0, 0, 0, 0);
	glowColor = Color(0, 0, 0, 0);
}

void cESP::think(CBaseEntity* local)
{
	if (!Options.Visuals.ESP.Enabled)
		return;

	for (auto i = 1; i <= ClientEntList->GetHighestEntityIndex(); i++)
	{
		if (i == local->GetIndex())
			continue;

		auto entity = ClientEntList->GetClientEntity(i);
		if (!entity
			|| entity->GetDormant())
			continue;

		if (Options.Visuals.ESP.World)
			drawWorld(entity);

		if (Options.Visuals.ESP.NadeTracer)
			drawNadeTracer(entity);

		if (entity->GetClientClass()->m_ClassID != 35
			|| !entity->GetAlive()
			|| !Engine->GetPlayerInfo(i, &info)
			|| entity->GetHealth() == 0)
			continue;

		if (Options.Visuals.ESP.EnemyOnly)
			if (entity->GetTeam() == Global::LocalPlayer->GetTeam())
				continue;

		if (Options.Visuals.ESP.AimPoint)
			DrawAimPoint(Color::Color(255, 165, 8), Global::LocalPlayer);

		drawPlayer(local, entity);
	}
	NadeTracer->Clear();

}

void cESP::getScreenSize()
{
	Engine->GetScreenSize(width, height);
}

bool cESP::isVisible(Vector& start, Vector& end, CBaseEntity* entity)
{
	trace_t trace;
	Ray_t ray;
	CTraceFilter filter;
	filter.pSkip = ClientEntList->GetClientEntity(Engine->GetLocalPlayer());

	ray.Init(start, end);
	EngineTrace->TraceRay(ray, 0x4600400B, &filter, &trace);

	return (trace.m_pEnt == entity || trace.fraction > 0.99f);
}


void cESP::drawPlayer(CBaseEntity* local, CBaseEntity* entity)
{
	auto& trans = *reinterpret_cast<matrix3x4a_t*>(DWORD(entity) + offsets.m_rgflCoordinateFrame);

	auto collision = static_cast<ICollideable*>(entity->GetCollideable());
	if (!collision)
		return;

	auto min = collision->OBBMins();
	auto max = collision->OBBMaxs();

	Vector pointList[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector transformed[8];

	for (auto i = 0; i < 8; i++)
		VectorTransform(pointList[i], trans, transformed[i]);

	Vector flb, brt, blb, frt, frb, brb, blt, flt;

	if (!WorldToScreen(transformed[3], flb)
		|| !WorldToScreen(transformed[0], blb)
		|| !WorldToScreen(transformed[2], frb)
		|| !WorldToScreen(transformed[6], blt)
		|| !WorldToScreen(transformed[5], brt)
		|| !WorldToScreen(transformed[4], frt)
		|| !WorldToScreen(transformed[1], brb)
		|| !WorldToScreen(transformed[7], flt))
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	auto left = flb.x;
	auto top = flb.y;
	auto right = flb.x;
	auto bottom = flb.y;

	for (auto i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}

	auto x = left;
	auto y = bottom;
	auto w = right - left;
	auto h = top - bottom;

	auto IsVisible = isVisible(local->GetEyePosition(), entity->GetEyePosition(), entity);

	

	if (IsVisible)
	{
		if (entity->GetTeam() == 2)
			espColor = Color(int(Options.Visuals.ESP.VisibleColor[0]), int(Options.Visuals.ESP.VisibleColor[1]), int(Options.Visuals.ESP.VisibleColor[2]));
		else if (entity->GetTeam() == 3)
			espColor = Color(int(Options.Visuals.ESP.VisibleColor[0]), int(Options.Visuals.ESP.VisibleColor[1]), int(Options.Visuals.ESP.VisibleColor[2]));
	}
	else
	{
		if (entity->GetTeam() == 2)
			espColor = Color(int(Options.Visuals.ESP.NonVisibleColor[0]), int(Options.Visuals.ESP.NonVisibleColor[1]), int(Options.Visuals.ESP.NonVisibleColor[2]));
		else if (entity->GetTeam() == 3)
			espColor = Color(int(Options.Visuals.ESP.NonVisibleColor[0]), int(Options.Visuals.ESP.NonVisibleColor[1]), int(Options.Visuals.ESP.NonVisibleColor[2]));
	}

	if (Options.Visuals.ESP.Box)
		drawOutlinedBox(x, y, w, h, espColor, Color(0, 0, 0));
	
	if (Options.Visuals.ESP.Health == 2)
		drawBar(x - 4, y + h / 2 - 1, 4, h + 1, Color(255.0f - entity->GetHealth() * 2.55f, entity->GetHealth() * 2.55f, 0), entity->GetHealth());

	if (Options.Visuals.ESP.Name)
		DrawStringN(ESP, true, x + w / 2, y - 16, Color(255, 255, 255), info.name);

	if (Options.Visuals.ESP.Weapon)
	{
		auto weapon = entity->GetWeapon();
		if (weapon)
		{
			auto WeaponIcon = weapon->GetCSWpnData()->m_pHudTexture_Weapon->charinFont;

			DrawStringN(0xA1, true, x + w / 2, top + 2, Color(255, 255, 255), XorStr("%c"), WeaponIcon);
		}
	}

	auto place = 0;

	if (Options.Visuals.ESP.Health == 1)
		DrawStringN(ESP, false, x + w + 5, y - 4 + (place++ * 11), Color(255, 255, 255), XorStr("%i HP"), entity->GetHealth());

	if (Options.Visuals.ESP.Ammo)
	{
		auto wep = entity->GetWeapon();
		if (wep)
		{
			if (wep->GetWeaponType() == WEPCLASS_KNIFE || wep->GetWeaponType() == WEPCLASS_INVALID)
			{
				DrawStringN(ESP, false, x + w + 5, y - 4 + (place++ * 11), Color(255, 255, 255), XorStr("NONE"));
			}
			else
			{
				DrawStringN(ESP, false, x + w + 5, y - 4 + (place++ * 11), Color(255, 255, 255), XorStr("%i bullets left"), entity->GetAmmo(wep));
			}
		}
		
	}

	if (Options.Visuals.ESP.Distance)
		DrawStringN(ESP, false, x + w + 5, y - 4 + (place++ * 11), Color(255, 255, 255), XorStr("%i units"), entity->GetDistance());

	if (Options.Visuals.ESP.Flashed && entity->IsFlashed())
		DrawStringN(ESP, true, x + w / 2, y - 26, Color(255, 0, 0), XorStr("FLASHED"));

	if (Options.Visuals.ESP.Bone)
		DrawBone(entity);

	if (Options.Visuals.ESP.Barrel)
		DrawTraceLine(Color(0, 255, 0), entity);
	
	if (Options.Visuals.ESP.DrawDefuser && entity->IsDefusing())
		DrawStringN(ESP, false, x + w + 5, y - 4 + (place++ * 11), Color(0, 255, 255), XorStr("Defusing"));

	if (Options.Visuals.ESP.DrawGlowS >= 1)
		DrawGlow(entity);

	if (Options.Visuals.ESP.DLight)
		DrawDLight(entity);
		
	if (Options.Visuals.ESP.Callout)
		DrawStringN(ESP, false, x + w + 5, y - 4 + (place++ * 11), Color(0, 255, 0), entity->GetLastPlace());
}

void cESP::DrawBone(CBaseEntity* pEnt)
{
	auto pStudioHdr = ModelInfo->GetStudioModel(pEnt->GetModel());

	if (!pStudioHdr)
		return;

	Vector vParent, vChild, sParent, sChild;

	for (auto j = 0; j < pStudioHdr->numbones; j++)
	{
		auto pBone = pStudioHdr->pBone(j);

		if (pBone && (pBone->flags & BONE_USED_BY_HITBOX) && (pBone->parent != -1))
		{
			vChild = pEnt->GetBonePosition(j);
			vParent = pEnt->GetBonePosition(pBone->parent);

			if (WorldToScreen(vParent, sParent) && WorldToScreen(vChild, sChild))
			{
				Surface->DrawSetColor(255, 255, 255, 255);
				Surface->DrawLine(sParent[0], sParent[1], sChild[0], sChild[1]);
			}
		}
	}

	Vector cross = pEnt->GetBonePosition(6), screen;
	static auto Scale = 2;
	if (WorldToScreen(cross, screen))
	{
		DrawRect(screen.x - Scale, screen.y - (Scale * 2), (Scale * 2), (Scale * 4), Color(20, 20, 20, 160));
		DrawRect(screen.x - (Scale * 2), screen.y - Scale, (Scale * 4), (Scale * 2), Color(20, 20, 20, 160));
		DrawRect(screen.x - Scale - 1, screen.y - (Scale * 2) - 1, (Scale * 2) - 2, (Scale * 4) - 2, Color(250, 250, 250, 160));
		DrawRect(screen.x - (Scale * 2) - 1, screen.y - Scale - 1, (Scale * 4) - 2, (Scale * 2) - 2, Color(250, 250, 250, 160));
	}
}

void cESP::DrawAimPoint(Color cColor, CBaseEntity* pEnt)
{
	auto view = Global::pCmd->viewangles;
	if (!Global::bSendPacket) return;
	auto pWeapon = pEnt->GetWeapon();
	if (!pWeapon) return;

	auto sWeaponInfo = pWeapon->GetCSWpnData();

	Vector vEnd, vForward(Global::LocalPlayer->GetEyePosition());

	trace_t tr;
	Ray_t ray;

	CTraceFilter filter;
	filter.pSkip = Global::LocalPlayer;
	AngleVectors(view, &vEnd);

	vEnd = vEnd * sWeaponInfo->m_flRange + vForward;

	ray.Init(vForward, vEnd);
	EngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);

	auto surfacemat = -1;
	auto surfaceData = Physprops->GetSurfaceData(tr.surface.surfaceProps);
	if (surfaceData)
		surfacemat = surfaceData->game.material;

	if (tr.hitgroup <= 7 && tr.hitgroup > 0)
		DebugOverlay->AddBoxOverlay(tr.endpos - Vector(0, 0, 0), Vector(-2, -2, -2), Vector(2, 2, 2), pEnt->GetEyeAngles(), 0, 255, 0, 50, Globals->interval_per_tick);
	else if (surfacemat == 89 || surfacemat == 71 || surfacemat == 87 || surfacemat == 85 || surfacemat == 76)
		DebugOverlay->AddBoxOverlay(tr.endpos - Vector(0, 0, 0), Vector(-2, -2, -2), Vector(2, 2, 2), pEnt->GetEyeAngles(), 0, 255, 0, 50, Globals->interval_per_tick);
	else
		DebugOverlay->AddBoxOverlay(tr.endpos - Vector(0, 0, 0), Vector(-2, -2, -2), Vector(2, 2, 2), pEnt->GetEyeAngles(), 0, 255, 0, 50, Globals->interval_per_tick);

}

void cESP::RunTrace(CBaseEntity* pEnt, Vector& vecStart, Vector& vecForward)
{
	Vector traceEndPos;
	auto pWeapon = pEnt->GetWeapon();
	if (!pWeapon) return;

	auto sWeaponInfo = pWeapon->GetCSWpnData();

	auto vTraceEnd = vecStart + (vecForward * sWeaponInfo->m_flRange);

	Ray_t ray;
	trace_t tr;
	CTraceFilter filter;
	filter.pSkip = pEnt;

	ray.Init(vecStart, vTraceEnd);
	EngineTrace->TraceRay(ray, 0x4600400B, &filter, &tr);

	traceEndPos = tr.endpos;



	DebugOverlay->AddLineOverlay(tr.startpos, traceEndPos, 0, 255, 0, false, Globals->interval_per_tick);
	DebugOverlay->AddBoxOverlay(traceEndPos - Vector(0, 0, 0), Vector(-2, -2, -2), Vector(2, 2, 2), pEnt->GetEyeAngles(), 0, 255, 0, 50, Globals->interval_per_tick);

}

void cESP::DrawTraceLine(Color cColor, CBaseEntity* pEnt)// pretty easy to make actually lmaoo
{
	Vector vTraceStart;
	auto bones = 0;
	auto pStudioModel = ModelInfo->GetStudioModel(pEnt->GetModel());
	std::string plyModel = ModelInfo->GetModelName(pEnt->GetModel());

	if (plyModel.find(XorStr("ctm_fbi"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("ctm_fbi_variant"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("ctm_st6"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("ctm_st6_custom"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("ctm_st6_variant"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("ctm_swat"), 0) != std::string::npos)
		bones = 77;
	if (plyModel.find(XorStr("ctm_swat_variant"), 0) != std::string::npos)
		bones = 76;
	if (plyModel.find(XorStr("ctm_sas"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("ctm_sas_variant"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("ctm_gign"), 0) != std::string::npos)
		bones = 79;
	if (plyModel.find(XorStr("ctm_gign_variant"), 0) != std::string::npos)
		bones = 79;
	if (plyModel.find(XorStr("ctm_idf"), 0) != std::string::npos)
		bones = 80;
	if (plyModel.find(XorStr("ctm_idf_variant"), 0) != std::string::npos)
		bones = 80;
	if (plyModel.find(XorStr("tm_leet"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("tm_leet_variant"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("tm_phoenix"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("tm_phoenix_variant"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("tm_pirate"), 0) != std::string::npos)
		bones = 77;
	if (plyModel.find(XorStr("tm_pirate_variant"), 0) != std::string::npos)
		bones = 77;
	if (plyModel.find(XorStr("tm_pirate_custom"), 0) != std::string::npos)
		bones = 77;
	if (plyModel.find(XorStr("tm_professional"), 0) != std::string::npos)
		bones = 80;
	if (plyModel.find(XorStr("tm_professional_var"), 0) != std::string::npos)
		bones = 80;
	if (plyModel.find(XorStr("tm_anarchist"), 0) != std::string::npos)
		bones = 79;
	if (plyModel.find(XorStr("tm_anarchist_variant"), 0) != std::string::npos)
		bones = 79;
	if (plyModel.find(XorStr("tm_balkan"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("tm_balkan_variant"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("tm_separatist"), 0) != std::string::npos)
		bones = 75;
	if (plyModel.find(XorStr("tm_separatist_variant"), 0) != std::string::npos)
		bones = 75;

	vTraceStart = pEnt->GetBonePosition(bones);
	Vector vTraceForward;
	AngleVectors(pEnt->GetEyeAngles(), &vTraceForward);

	// Run Trace and Draw
	this->RunTrace(pEnt, vTraceStart, vTraceForward);
}

void cESP::DrawGlow(CBaseEntity* pEnt)
{

	Color glowColor;
	static GlowObjectPointer_t getGlowObjectPointer = reinterpret_cast<GlowObjectPointer_t>(Memory::FindPatternAlt(XorStr("client.dll"), (PBYTE)XorStr("\xA1\x00\x00\x00\x00\xA8\x01\x75\x4E\x33"), XorStr("x????xxxx"), 0, 0));
	static void* glowObjectPointer = getGlowObjectPointer();

	auto glowIndex = *reinterpret_cast<UINT32*>(uintptr_t(pEnt) + 0xA308 + 0x18);
	auto glowObjectArray = *static_cast<CGlowObjectManager::GlowObjectDefinition_t**>(glowObjectPointer);
	auto glowObject = &glowObjectArray[glowIndex];

	switch (Options.Visuals.ESP.DrawGlowS)
	{
	case 1:
		if (pEnt->GetTeam() == 2)
			glowColor = Color(223, 175, 86, 153);
		else if (pEnt->GetTeam() == 3)
			glowColor = Color(113, 154, 220, 153);
		break;
	case 2:
		if (pEnt->GetTeam() == 2)
			glowColor = Color(int(Options.Visuals.Glow.TeamColor[0]), int(Options.Visuals.Glow.TeamColor[1]), int(Options.Visuals.Glow.TeamColor[2]), 153);
		else if (pEnt->GetTeam() == 3)
			glowColor = Color(int(Options.Visuals.Glow.TeamColor[0]), int(Options.Visuals.Glow.TeamColor[1]), int(Options.Visuals.Glow.TeamColor[2]), 153);
		break;
	default: break;
	}

	glowObject->glowColor = Vector((1.f / 255.f) * glowColor.r(), (1.f / 255.f) * glowColor.g(), (1.f / 255.f) * glowColor.b());
	glowObject->glowAlpha = (1.f / 255.f) * glowColor.a();
	glowObject->shouldGlow = true;
	glowObject->isUnknown = false;
}

void cESP::DrawDLight(CBaseEntity* pEnt)
{
	if (pEnt->GetTeam() == Global::LocalPlayer->GetTeam())
	{
		auto pDlight = g_pEffects->CL_AllocDlight(pEnt->index);

		pDlight->origin = pEnt->GetOrigin();
		pDlight->radius = 10.0f * Options.Visuals.ESP.DLightRadius;
		pDlight->color = Color(0, 255, 0, 5);
		pDlight->die = Globals->curtime + 0.05f;
		pDlight->decay = pDlight->radius / 5.0f;
		pDlight->key = pEnt->index;


		auto pElight = g_pEffects->CL_AllocElight(pEnt->index);
		pElight->origin = pEnt->GetOrigin() + Vector(0.0f, 0.0f, 35.0f);
		pElight->radius = 100.0f;
		pElight->color = Color(0, 255, 0, 5);
		pElight->die = Globals->curtime + 0.05f;
		pElight->decay = pElight->radius / 5.0f;
		pElight->key = pEnt->index;
	}
	else
	{
		auto pDlight = g_pEffects->CL_AllocDlight(pEnt->index);

		pDlight->origin = pEnt->GetOrigin();
		pDlight->radius = 10.0f * Options.Visuals.ESP.DLightRadius;
		pDlight->color = Color(255, 0, 0, 5);
		pDlight->die = Globals->curtime + 0.05f;
		pDlight->decay = pDlight->radius / 5.0f;
		pDlight->key = pEnt->index;

		auto pElight = g_pEffects->CL_AllocElight(pEnt->index);
		pElight->origin = pEnt->GetOrigin() + Vector(0.0f, 0.0f, 35.0f);
		pElight->radius = 100.0f;
		pElight->color = Color(255, 0, 0, 5);
		pElight->die = Globals->curtime + 0.05f;
		pElight->decay = pElight->radius / 5.0f;
		pElight->key = pEnt->index;
	}
}

void cESP::drawNadeTracer(CBaseEntity* entity) // Beginning of our nade tracer. :D
{
	if (entity->GetTeam() != Global::LocalPlayer->GetTeam())
		return;

	if (strstr(entity->GetClientClass()->m_pNetworkName, "GrenadeProjectile"))
	{
		NadeTracer->AddTracer(entity, Color(255, 0, 0), 60);
		NadeTracer->Draw();
	}

}

void cESP::drawWorld(CBaseEntity* entity)
{
	if (entity->GetAbsAngles().x == 0.0f && entity->GetAbsAngles().z == 0.0f)
		return;

	std::string modelName = ModelInfo->GetModelName(entity->GetModel());
	if (modelName.find(XorStr("models/weapons/w_pist_")) != std::string::npos && modelName.find(XorStr("_dropped.mdl")) != std::string::npos
		|| modelName.find(XorStr("models/weapons/w_rif_")) != std::string::npos && modelName.find(XorStr("_dropped.mdl")) != std::string::npos
		|| modelName.find(XorStr("models/weapons/w_mach_")) != std::string::npos && modelName.find(XorStr("_dropped.mdl")) != std::string::npos
		|| modelName.find(XorStr("models/weapons/w_snip_")) != std::string::npos && modelName.find(XorStr("_dropped.mdl")) != std::string::npos
		|| modelName.find(XorStr("models/weapons/w_eq_")) != std::string::npos && modelName.find(XorStr("_dropped.mdl")) != std::string::npos
		|| modelName.find(XorStr("models/weapons/w_shot_")) != std::string::npos && modelName.find(XorStr("_dropped.mdl")) != std::string::npos
		|| modelName.find(XorStr("models/weapons/w_smg_")) != std::string::npos && modelName.find(XorStr("_dropped.mdl")) != std::string::npos)
	{
		modelName.erase(0, modelName.find_first_of("_", std::string(XorStr("abc")).length()) + 1); // General stuff
		modelName.erase(0, modelName.find_first_of("_", std::string(XorStr("eq")).length()) + 1); // Grenades
		modelName.erase(modelName.find_last_of("_"), 12);
		modelName.erase(0, modelName.find_first_of("_", std::string(XorStr("abc")).length()) + 1); // General stuff
		modelName.erase(0, modelName.find_first_of("_", std::string(XorStr("eq")).length()) + 1); // Grenades

		if (!strcmp(modelName.c_str(), XorStr("ied")))
			modelName = XorStr("c4");
		else if (!strcmp(modelName.c_str(), XorStr("223")))
			modelName = XorStr("usp-s");
		else if (!strcmp(modelName.c_str(), XorStr("75")))
			modelName = XorStr("cz75");
		else if (!strcmp(modelName.c_str(), XorStr("s")))
			modelName = XorStr("m4a1-s");

		drawBoundingBox(entity, Color(0, 255, 0), modelName.c_str());
	}
}

void cESP::drawBoundingBox(CBaseEntity* entity, Color color, const char* text)
{
	auto& trans = *reinterpret_cast<matrix3x4a_t*>(DWORD(entity) + offsets.m_rgflCoordinateFrame);

	auto collision = static_cast<ICollideable*>(entity->GetCollideable());
	if (!collision)
		return;

	auto min = collision->OBBMins();
	auto max = collision->OBBMaxs();

	Vector pointList[] = {
		Vector(min.x, min.y, min.z),
		Vector(min.x, max.y, min.z),
		Vector(max.x, max.y, min.z),
		Vector(max.x, min.y, min.z),
		Vector(max.x, max.y, max.z),
		Vector(min.x, max.y, max.z),
		Vector(min.x, min.y, max.z),
		Vector(max.x, min.y, max.z)
	};

	Vector transformed[8];

	for (auto i = 0; i < 8; i++)
		VectorTransform(pointList[i], trans, transformed[i]);

	Vector flb, brt, blb, frt, frb, brb, blt, flt;

	if (!WorldToScreen(transformed[3], flb) ||
		!WorldToScreen(transformed[0], blb) ||
		!WorldToScreen(transformed[2], frb) ||
		!WorldToScreen(transformed[6], blt) ||
		!WorldToScreen(transformed[5], brt) ||
		!WorldToScreen(transformed[4], frt) ||
		!WorldToScreen(transformed[1], brb) ||
		!WorldToScreen(transformed[7], flt))
		return;

	Vector arr[] = { flb, brt, blb, frt, frb, brb, blt, flt };

	auto left = flb.x;
	auto top = flb.y;
	auto right = flb.x;
	auto bottom = flb.y;

	for (auto i = 0; i < 8; i++)
	{
		if (left > arr[i].x)
			left = arr[i].x;
		if (top < arr[i].y)
			top = arr[i].y;
		if (right < arr[i].x)
			right = arr[i].x;
		if (bottom > arr[i].y)
			bottom = arr[i].y;
	}

	auto h = bottom - top;
	auto w = right - left;

	DrawLine(left, bottom, left, top, color);
	DrawLine(left - 1, bottom - 1, left - 1, top + 2, Color(0, 0, 0));
	DrawLine(left + 1, bottom + 1, left + 1, top + 2, Color(0, 0, 0));

	DrawLine(right, top, right, bottom, color);
	DrawLine(right + 1, top + 1, right + 1, bottom - 1, Color(0, 0, 0));
	DrawLine(right - 1, top - 1, right - 1, bottom + 1, Color(0, 0, 0));

	DrawLine(left, top, right, top, color);
	DrawLine(left + 1, top - 1, right + 1, top - 1, Color(0, 0, 0));
	DrawLine(left, top + 1, right + 1, top + 1, Color(0, 0, 0));

	DrawLine(right, bottom, left, bottom, color);
	DrawLine(right + 1, bottom - 1, left - 1, bottom - 1, Color(0, 0, 0));
	DrawLine(right - 1, bottom + 1, left + 1, bottom + 1, Color(0, 0, 0));

	if (text)
		DrawStringN(ESP, true, left + w / 2, top - 15, color, text);
}