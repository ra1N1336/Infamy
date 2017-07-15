#include "Cheats.h"
#include "Accessors.h"
cVisuals* g_pVisuals = new cVisuals;



void cVisuals::Direct3D(IDirect3DDevice9* pDevice)
{
	for (auto i = 0; i <= ClientEntList->GetHighestEntityIndex(); i++)
	{
		if (this->ESPINFO.topx[i] == -1 ||
			this->ESPINFO.topy[i] == -1 ||
			this->ESPINFO.boty[i] == -1 ||
			this->ESPINFO.botx[i] == -1)
			continue;

	}
}
/*Normal Painttraverse Visuals*/
void cVisuals::PaintTraverse()
{
	for (auto i = 0; i <= ClientEntList->GetHighestEntityIndex(); i++)
	{
		auto pEnt = ClientEntList->GetClientEntity(i);

		if (pEnt == nullptr
			|| !pEnt->GetAlive()
			|| pEnt->GetDormant()
			|| pEnt->GetHealth() == 0)
			continue;
	if (Options.Visuals.ESP.AimPoint)
		this->DrawAimPoint(Color::Color(255, 165, 8), Global::LocalPlayer);
		if (Options.Visuals.ESP.EnemyOnly)
			if (pEnt->GetTeam() == Global::LocalPlayer->GetTeam())
				continue;
		auto bIsVisible = false;
		if (Options.Visuals.ESP.IsVisible == 0)
			bIsVisible = pEnt->IsVisible(6);
		else
			bIsVisible = pEnt->IsEntireVisible();
		if (Options.Visuals.ESP.bVisibleOnly && !bIsVisible)
			continue;

		auto pEntOrigin = pEnt->GetOrigin();
		auto vecEyeOffset = Vector(0, 0, *reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEnt) + offsets.m_flEyePos + 8));
		if (!vecEyeOffset.z)
			vecEyeOffset.z = 64;

		auto pEntEyePos = pEntOrigin + vecEyeOffset;
		Vector pEntScrPos, pEntEyeScrPos;

		if (WorldToScreen(pEntEyePos, pEntEyeScrPos))
			if (WorldToScreen(pEntOrigin, pEntScrPos))
			{
				int height = pEntScrPos.y - pEntEyeScrPos.y;
				auto width = height / 3;
				int centery = pEntEyeScrPos.y + (height / 2);
				int topx = pEntScrPos.x - width;
				int topy = centery - ((height / 2) * 1.3);
				int botx = pEntScrPos.x + width;
				int boty = (centery + ((height / 2) * 1.2));
				auto render_color_hidden = Color(255, 0, 0);
				auto render_color_visible = Color(255, 0, 0);
				auto render_color_final = bIsVisible ? render_color_visible : render_color_hidden;
				if (Options.Visuals.ESP.Box)
					this->DrawCleanBox(render_color_final, topx, topy, botx, boty);
				if (Options.Visuals.ESP.Name)
					this->DrawName(Color::White(), botx + 2, topy + 14 - Surface->GetFontTall(ESP), ESP, pEnt);
				switch(Options.Visuals.ESP.Health)
				{
					case 1:
						this->DrawHealth(Color::White(), botx + 2, topy + 24 - Surface->GetFontTall(ESP), ESP, pEnt);
						break;
					case 2:
						this->DrawHealthBar(pEnt);
						break;
				default: break;
				}
				if (Options.Visuals.ESP.Weapon)
					this->DrawWeapon(Color::White(), botx + 2, topy + 39 - Surface->GetFontTall(0xA1), 0xA1, pEnt);
				if (Options.Visuals.ESP.Bone)
					this->DrawBone(pEnt);
				if (Options.Visuals.ESP.Barrel)
					this->DrawTraceLine(Color(255,165,8), pEnt);
				if (Options.Visuals.ESP.DLight)
					this->DrawDLight(pEnt);
				if (Options.Visuals.ESP.LocationSpam)
					this->LocationSpam(pEnt);
				if (Options.Visuals.ESP.RankESP)
					this->ShowRank(pEnt);
				if (Options.Visuals.ESP.DrawDefuser)
					this->DrawBombDefuser(pEnt);
				if (Options.Visuals.ESP.Flashed && pEnt->IsFlashed())
					this->DrawFlashed(botx + 2, topy + 62 - Surface->GetFontTall(ESP), ESP, pEnt);
				if (Options.Visuals.ESP.DrawGlowS >= 1)
					this->DrawGlow(pEnt);
				if (Options.Visuals.ESP.Distance)
					this->DrawDistance(Color::White(), botx + 2, topy + 46 - Surface->GetFontTall(ESP), ESP, pEnt);
				if (Options.Visuals.ESP.Ammo)
					this->DrawAmmo(botx + 2, topy + 57 - Surface->GetFontTall(ESP), ESP, pEnt);
			}
	}
}


void cVisuals::RunLoop()// this Should Run in another thread to save Frametime
{
	if (!(Engine->IsConnected() && Engine->IsInGame()))
		return;
	for (auto i = 0; i <= ClientEntList->GetHighestEntityIndex(); i++)
	{
		this->ESPINFO.topx[i] = -1;
		this->ESPINFO.topy[i] = -1;
		this->ESPINFO.botx[i] = -1;
		this->ESPINFO.boty[i] = -1;
		auto pEnt = ClientEntList->GetClientEntity(i); 
			if (pEnt == nullptr
			|| !pEnt->GetAlive())
			continue;
		if (Options.Visuals.ESP.EnemyOnly)
			if (pEnt->GetTeam() == Global::LocalPlayer->GetTeam())
				continue;
		this->RunMath(pEnt);
	}
}

void cVisuals::RunMath(CBaseEntity* pEnt)
{
	if (!pEnt->GetAlive() && pEnt->GetDormant())
		return;
	auto i = pEnt->index;
	this->ESPINFO.pEnt[i] = pEnt;// set the index for this entity
	/*now we do the math and set it as the index for the current entitiy*/
	auto pEntOrigin = pEnt->GetOrigin();
	auto vecEyeOffset = Vector(0, 0, *reinterpret_cast<float*>(reinterpret_cast<DWORD>(pEnt) + offsets.m_flEyePos + 8));
	if (!vecEyeOffset.z)
		vecEyeOffset.z = 64;
	auto pEntEyePos = pEntOrigin + vecEyeOffset;
	Vector pEntScrPos, pEntEyeScrPos;
	if(WorldToScreen(pEntEyePos,pEntEyeScrPos))
		if(WorldToScreen(pEntOrigin,pEntScrPos))
		{	
			
			int height = pEntScrPos.y - pEntEyeScrPos.y;
			auto width = height / 3;
			int centery = pEntEyeScrPos.y + (height / 2);
			this->ESPINFO.topx[i] = pEntScrPos.x - width;
			this->ESPINFO.topy[i] = pEntScrPos.x + width;
			this->ESPINFO.botx[i] = centery - ((height - 2) * 1.3);
			this->ESPINFO.boty[i] = (centery + ((height / 2) * 1.2));
		}
}
/*Generic Drawing Structure for the Loop*/

void cVisuals::DrawCleanBox(Color cColor, int topx, int topy, int botx, int boty)
{
	/*Color of inside layer*/
	Surface->DrawSetColor(cColor);
	/*Inside of box*/
	Surface->DrawOutlinedRect(topx, topy, botx, boty);
	/*Color of Outline*/
	Surface->DrawSetColor(0,0,0,255);
	/*Outlines*/
	Surface->DrawOutlinedRect(topx - 1, topy - 1, botx + 1, boty + 1);
	Surface->DrawOutlinedRect(topx + 1, topy + 1, botx - 1, boty - 1);
}

void cVisuals::RunTrace(CBaseEntity* pEnt, Vector& vecStart, Vector& vecForward)
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



	DebugOverlay->AddLineOverlay(tr.startpos, traceEndPos, 255, 165, 8, false, Globals->interval_per_tick);
	DebugOverlay->AddBoxOverlay(traceEndPos - Vector(0, 0, 0),  Vector(-2, -2, -2), Vector(2, 2, 2), pEnt->GetEyeAngles(), 255, 165, 8, 50, Globals->interval_per_tick);

}



void cVisuals::DrawAimPoint(Color cColor, CBaseEntity* pEnt)
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
		DebugOverlay->AddBoxOverlay(tr.endpos - Vector(0, 0, 0), Vector(-2, -2, -2), Vector(2, 2, 2), pEnt->GetEyeAngles(), 255, 0,0, 50, Globals->interval_per_tick);
	else if (surfacemat == 89 || surfacemat == 71 || surfacemat == 87 || surfacemat == 85 || surfacemat == 76 )
		DebugOverlay->AddBoxOverlay(tr.endpos - Vector(0, 0, 0), Vector(-2, -2, -2), Vector(2, 2, 2), pEnt->GetEyeAngles(), 0, 255, 50, 50, Globals->interval_per_tick);
	else
		DebugOverlay->AddBoxOverlay(tr.endpos - Vector(0, 0, 0), Vector(-2, -2, -2), Vector(2, 2, 2), pEnt->GetEyeAngles(), 255, 165, 8, 50, Globals->interval_per_tick);

}
void cVisuals::DrawTraceLine(Color cColor, CBaseEntity* pEnt)// pretty easy to make actually lmaoo
{
	Vector vTraceStart;
	auto bones = 0;
	auto pStudioModel = ModelInfo->GetStudioModel(pEnt->GetModel());
	std::string plyModel = ModelInfo->GetModelName(pEnt->GetModel());

	if (plyModel.find("ctm_fbi", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("ctm_fbi_variant", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("ctm_st6", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("ctm_st6_custom", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("ctm_st6_variant", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("ctm_swat", 0) != std::string::npos)
		bones = 77;
	if (plyModel.find("ctm_swat_variant", 0) != std::string::npos)
		bones = 76;
	if (plyModel.find("ctm_sas", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("ctm_sas_variant", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("ctm_gign", 0) != std::string::npos)
		bones = 79;
	if (plyModel.find("ctm_gign_variant", 0) != std::string::npos)
		bones = 79;
	if (plyModel.find("ctm_idf", 0) != std::string::npos)
		bones = 80;
	if (plyModel.find("ctm_idf_variant", 0) != std::string::npos)
		bones = 80;
	if (plyModel.find("tm_leet", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("tm_leet_variant", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("tm_phoenix", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("tm_phoenix_variant", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("tm_pirate", 0) != std::string::npos)
		bones = 77;
	if (plyModel.find("tm_pirate_variant", 0) != std::string::npos)
		bones = 77;
	if (plyModel.find("tm_pirate_custom", 0) != std::string::npos)
		bones = 77;
	if (plyModel.find("tm_professional", 0) != std::string::npos)
		bones = 80;
	if (plyModel.find("tm_professional_var", 0) != std::string::npos)
		bones = 80;
	if (plyModel.find("tm_anarchist", 0) != std::string::npos)
		bones = 79;
	if (plyModel.find("tm_anarchist_variant", 0) != std::string::npos)
		bones = 79;
	if (plyModel.find("tm_balkan", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("tm_balkan_variant", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("tm_separatist", 0) != std::string::npos)
		bones = 75;
	if (plyModel.find("tm_separatist_variant", 0) != std::string::npos)
		bones = 75;

	vTraceStart = pEnt->GetBonePosition(bones);
	Vector vTraceForward;
	AngleVectors(pEnt->GetEyeAngles(), &vTraceForward);

	// Run Trace and Draw
	this->RunTrace(pEnt, vTraceStart, vTraceForward);
}

#define clamp(val,min,max) (((val) > (max)) ? (max): (((val) < (min)) ? (min): (val)))

void DrawHeader(int x, int y, int w, Color color, int HealthBarWidth)
{
	auto i = 0;
	auto xCoord = x;
	auto yCoord = y;

	for (i = 0; i < 5; i++)
	{
		DrawRect(x - i, y + i, w, 1, Color(0, 0, 0, 255));
		DrawRect(x - i, y + i, HealthBarWidth + 2, 1, color);
		DrawRect(x - 3, y + 3, HealthBarWidth + 2, 1, color);
		DrawRect(x - 4, y + 4, HealthBarWidth + 2, 1, color);
	}

	DrawRect(x, y, w, 1, Color(255, 255, 255, 255));
	DrawRect((x + 1) - 5, y + 5, w, 1, Color(255, 255, 255, 255));

	for (i = 0; i < 5; i++)
	{
		DrawRect(x, y, 1, 1, Color(255, 255, 255, 255));
		x--;
		y++;
	}

	x = xCoord;
	y = yCoord;

	for (i = 0; i < 5; i++)
	{
		if (i != 0)
			DrawRect(x + w, y, 1, 1, Color(255, 255, 255, 255));

		x--;
		y++;
	}
}

void cVisuals::DrawHealth(Color cColor, int topx, int topy, HFont hFont, CBaseEntity* pEnt)
{
	/*Concat Strings*/
	DrawString(hFont, topx, topy, cColor, FONT_LEFT, XorStr("Health: %d"), pEnt->GetHealth());
}

void cVisuals::DrawDistance(Color cColor, int topx, int topy, HFont hFont, CBaseEntity* pEnt)
{
	/*Concat Strings*/
	int dist = VectorDistance(Global::LocalPlayer->GetOrigin(), pEnt->GetOrigin());

	DrawString(hFont, topx, topy, cColor, FONT_LEFT, XorStr("Distance: %d"), dist);
}

void cVisuals::DrawHealthBar(CBaseEntity* pEnt)
{
	/*Concat Strings*/
	auto iHealth = clamp(pEnt->GetHealth(), 0, 100);
	//auto armor = *reinterpret_cast<int*>(DWORD(pEnt) + offsets.Armor);
	auto iFlags = pEnt->GetFlags();
	auto vPlayerFoot = pEnt->GetOrigin();
	Vector vPlayerHead;
	if (iFlags & FL_DUCKING)
		vPlayerHead = vPlayerFoot + Vector(0, 0, 52);
	else
		vPlayerHead = vPlayerFoot + Vector(0, 0, 72);

	Vector vPlayerFootScreen, vPlayerHeadScreen;
	WorldToScreen(vPlayerFoot, vPlayerFootScreen);
	WorldToScreen(vPlayerHead, vPlayerHeadScreen);

	auto width = (vPlayerFootScreen.y - vPlayerHeadScreen.y) / 4;
	auto height = (vPlayerFootScreen.x - vPlayerHeadScreen.x) / 4;
	int h = vPlayerFootScreen.y - vPlayerHeadScreen.y;

	if (WorldToScreen(pEnt->GetEyePosition(), vPlayerHead))
	{

		Color color;
		if (pEnt->GetDormant()) {
			color.SetColor(84, 84, 84);
		}
		else {
			color.SetColor(int(255.0f * (1.0f - (float(iHealth) / 100.0f))),
				int(255.0f * (float(iHealth) / 100.0f)),
				0);
		}

		DrawHeader(vPlayerHeadScreen.x - width + 2, vPlayerFootScreen.y + 5, width * 2, color, (iHealth / (100 / (width * 2))) - 2);
	}
}

void cVisuals::DrawWeapon(Color cColor, int topx, int topy, HFont hFont, CBaseEntity* pEnt)
{
	/*Sanity Checks*/
	auto pWeapon = pEnt->GetWeapon();
	if (!pWeapon) return;
	/*Declare*/
	auto WeaponIcon = pWeapon->GetCSWpnData()->m_pHudTexture_Weapon->charinFont;
	/*Concat Strings*/
	DrawString(hFont, topx, topy, cColor, FONT_LEFT, XorStr("%c"), WeaponIcon);
}

void cVisuals::DrawName(Color cColor, int topx, int topy, HFont hFont, CBaseEntity* pEnt)
{
	player_info_t info;
	info = pEnt->GetPlayerInfo();
	/*Concat Strings*/
	DrawString(hFont, topx, topy, cColor, FONT_LEFT, info.name);
}

void cVisuals::DrawBombDefuser(CBaseEntity* pEnt)
{
	static itemTimer bombDefuseTimer(10.f);
	if (!Global::IsPlayerDefusing) {
		bombDefuseTimer.setMaxTime(pEnt->HasDefuser() ? 5.f : 10.f);
		bombDefuseTimer.startTimer();
	}
	else {
		int screenw, screenh;
		Engine->GetScreenSize(screenw, screenh);
		auto x = 16;
		auto y = screenh - 90;
		char dettime[64];
		sprintf_s(dettime, 64, "Bomb will be defused in: %.1f", ((int)(100 * bombDefuseTimer.getTimeRemaining()) / 100.0));
		DrawString(BombStuff, x, y, Color(0, 255, 255, 255), FONT_LEFT, "%s", dettime);
	}
}

void cVisuals::DrawGlow(CBaseEntity* pEnt)
{

	Color glowColor;
	static GlowObjectPointer_t getGlowObjectPointer = (GlowObjectPointer_t)(Memory::FindPatternAlt(XorStr("client.dll"), (PBYTE)XorStr("\xA1\x00\x00\x00\x00\xA8\x01\x75\x4E\x33"), XorStr("x????xxxx"),0,0));
	static void* glowObjectPointer = getGlowObjectPointer();

	UINT32 glowIndex = *(UINT32*)((uintptr_t)pEnt + 0xA2F8 + 0x18);
	CGlowObjectManager::GlowObjectDefinition_t* glowObjectArray = *(CGlowObjectManager::GlowObjectDefinition_t**)glowObjectPointer;
	CGlowObjectManager::GlowObjectDefinition_t* glowObject = &glowObjectArray[glowIndex];

	switch(Options.Visuals.ESP.DrawGlowS)
	{
	case 1:
		if (pEnt->GetTeam() == 2)
			glowColor = Color(223, 175, 86, 153);
		else if (pEnt->GetTeam() == 3)
			glowColor = Color(113, 154, 220, 153);
		break;
	case 2:
		if (pEnt->GetTeam() == 2)
			glowColor = Color(int(Options.Visuals.Glow.TeamColor[0] * 255), int(Options.Visuals.Glow.TeamColor[1] * 255), int(Options.Visuals.Glow.TeamColor[2] * 255), 153);
		else if (pEnt->GetTeam() == 3)
			glowColor = Color(int(Options.Visuals.Glow.TeamColor[0] * 255), int(Options.Visuals.Glow.TeamColor[1] * 255), int(Options.Visuals.Glow.TeamColor[2] * 255), 153);
		break;
	default: break;
	}

	glowObject->glowColor = Vector((1.f / 255.f) * glowColor.r(), (1.f / 255.f) * glowColor.g(), (1.f / 255.f) * glowColor.b());
	glowObject->glowAlpha = (1.f / 255.f) * glowColor.a();
	glowObject->shouldGlow = true;
	glowObject->isUnknown = false;
}

void cVisuals::RunEntityGlow(CBaseEntity* pEnt)
{
	CGlowObjectEntityManager* GlowObjectManager = (CGlowObjectEntityManager*)offsets.GlowManager;

	for (int i = 0; i < GlowObjectManager->size; ++i)
	{
		CGlowObjectEntityManager::GlowObjectEntityDefinition_t* glowEntity = &GlowObjectManager->m_GlowObjectDefinitions[i];
		CBaseEntity* Entity = glowEntity->getEntity();

		if (glowEntity->IsEmpty() || !Entity)
			continue;

		if (Options.Visuals.ESP.DrawGrenadesGlow && strstr(Entity->GetClientClass()->m_pNetworkName, "Projectile"))
			glowEntity->set(Color(255, 138, 46, 250));

		if (Options.Visuals.ESP.DrawWeaponsGlow && strstr(Entity->GetClientClass()->m_pNetworkName, "CWeapon"))
			glowEntity->set(Color(255, 138, 46, 250));

		if (Options.Visuals.ESP.DrawWeaponsGlow && strstr(Entity->GetClientClass()->m_pNetworkName, "AK47"))
			glowEntity->set(Color(255, 138, 46, 250));
	
		if (Options.Visuals.ESP.DrawWeaponsGlow && strstr(Entity->GetClientClass()->m_pNetworkName, "Deagle"))
			glowEntity->set(Color(255, 138, 46, 250));
	}
}


void cVisuals::DrawDLight(CBaseEntity* pEnt)
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

void cVisuals::DrawFlashed(int topx, int topy, HFont hFont, CBaseEntity* pEnt)
{
	/*Concat Strings*/
	DrawString(hFont, topx, topy, Color::Red(), FONT_LEFT, XorStr("FLASHED"));
}

void cVisuals::DrawAmmo(int topx, int topy, HFont hFont, CBaseEntity* pEnt)
{

	auto wep = pEnt->GetWeapon();
	auto AmmoCount = *reinterpret_cast<int*>(DWORD(wep) + offsets.m_iClip1);

	/*Concat Strings*/
	DrawString(hFont, topx, topy, Color::White(), FONT_LEFT, XorStr("Ammo: %i"), AmmoCount);
}

void cVisuals::ShowRank(CBaseEntity* pEnt)
{
	using tServerRankRevealAllFn = bool(__cdecl*)(float*);
	static auto ServerRankRevealAll = reinterpret_cast<tServerRankRevealAllFn>(Memory::FindPatternIDA("client.dll", "55 8B EC 8B 0D ? ? ? ? 68"));
	static float fArray[3] = { 0,0,0 };

	ServerRankRevealAll(fArray);
}

static char weaponNames[54][32] = {
	"None",
	"Desert Eagle",
	"Dual Barettas",
	"Five-SeveN",
	"Glock-18",
	"Unknown (5)",
	"Unknown (6)",
	"AK-47",
	"AUG",
	"AWP",
	"FAMAS",
	"G3SG1 (Auto Sniper)",
	"Unknown (12)",
	"Galil",
	"M249",
	"Unknown (15)",
	"M4A4",
	"Mac-10",
	"Unknown (18)",
	"P90",
	"Unknown (20)",
	"Unknown (21)",
	"Unknown (22)",
	"Unknown (23)",
	"UMP-45",
	"XM1014 (Auto Shotgun)",
	"PP-Bizon",
	"MAG-7",
	"Negev",
	"Sawed-Off Shotgun",
	"Tec-9",
	"Zeus x27 (Taser)",
	"P2000",
	"MP7",
	"MP9",
	"Nova",
	"P250",
	"Unknown (37)",
	"SCAR-20",
	"SG-553 (Automatic Rifle)",
	"SSG-08 (\"Scout\")",
	"Unknown (41)",
	"Knife",
	"Flashbang",
	"HE Grenade",
	"Smoke Grenade",
	"Molotov",
	"Decoy Grenade",
	"Incendiary Grenade",
	"C4 Explosive",
	"M4A1-S",
	"USP-S",
	"CZ-75 Auto",
	"Knife"
};

char* cVisuals::WeaponIDName(int weaponID) {
	char* name = nullptr;
	switch (weaponID)
	{
	case 59:
		name = weaponNames[53];
		break;
	case 60:
		name = weaponNames[50];
		break;
	case 61:
		name = weaponNames[51];
		break;
	case 63:
		name = weaponNames[53];
		break;
	}
	if (!name) //none of the above
		name = weaponNames[weaponID];
	return name;
}

void cVisuals::LocationSpam(CBaseEntity* pEnt)
{
	auto wep = pEnt->GetWeapon();
	auto weaponID = *reinterpret_cast<int*>(DWORD(wep) + offsets.m_iItemDefinitionIndex);
	auto Location = reinterpret_cast<char*>(DWORD(pEnt) + offsets.m_szLastPlaceName);
	auto Health = *reinterpret_cast<int*>(DWORD(pEnt) + offsets.m_iHealth);
	auto weaponName = WeaponIDName(weaponID);


	player_info_t info;
	info = pEnt->GetPlayerInfo();

	static auto iDelay = 0;
	iDelay++;

	if (iDelay > 1000)
		iDelay = 0;

	if (iDelay == 1000)
	{
		char pszBuffer[6969];
		sprintf_s(pszBuffer, "say_team Player: %s | Health: %d HP | Location: %s | Weapon: %s", info.name, Health, Location, weaponName);

		Engine->ClientCmd(pszBuffer);
	}
}

void cVisuals::DrawBone(CBaseEntity* pEnt)
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