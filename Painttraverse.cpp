#include "Hooks.h"
#include "Globals.h"
#include "Cheats.h"
#include "HWID.h"
#include "Accessors.h"
#include "mouse.h"
#include "Menu.h"
#include "mouse.h"
#include "Framework.h"

int fAlphaToUse = 0.f;
PaintTraverseFn oPaintTraverse;
bool bMenu = false;

inline bool IsMousePressed()
{
	return (GetAsyncKeyState(0x01));
}


bool IsClicked2;
static bool once2 = false;
bool ClickedTick2;

void DrawMouse()
{
	auto ptMouse = Input->GetMousePos();

	int x, y;
	x = ptMouse.x;
	y = ptMouse.y;

	static float rainbow;
	rainbow += 0.002f;
	if (rainbow > 1.f) rainbow = 0.f;

	DrawRect(x, y, 1, 12, Color(0, 0, 0));
	DrawRect(x + 1, y, 1, 11, Color(0, 0, 0));
	DrawRect(x + 1, y + 11, 1, 1, Color(0, 0, 0));
	DrawRect(x + 2, y + 1, 1, 1, Color(0, 0, 0));
	DrawRect(x + 2, y + 10, 1, 1, Color(0, 0, 0));
	DrawRect(x + 3, y + 2, 1, 1, Color(0, 0, 0));
	DrawRect(x + 3, y + 9, 1, 1, Color(0, 0, 0));
	DrawRect(x + 4, y + 3, 1, 1, Color(0, 0, 0));
	DrawRect(x + 5, y + 4, 1, 1, Color(0, 0, 0));
	DrawRect(x + 6, y + 5, 1, 1, Color(0, 0, 0));
	DrawRect(x + 7, y + 6, 1, 1, Color(0, 0, 0));
	DrawRect(x + 8, y + 7, 1, 1, Color(0, 0, 0));
	DrawRect(x + 4, y + 8, 4, 1, Color(0, 0, 0));

	DrawRect(x + 1, y + 1, 1, 10, Color::FromHSB(rainbow, 0.60f, 0.75f));
	DrawRect(x + 2, y + 2, 1, 8, Color::FromHSB(rainbow, 0.60f, 0.75f));
	DrawRect(x + 3, y + 3, 1, 6, Color::FromHSB(rainbow, 0.60f, 0.75f));
	DrawRect(x + 4, y + 4, 1, 4, Color::FromHSB(rainbow, 0.60f, 0.75f));
	DrawRect(x + 5, y + 5, 1, 3, Color::FromHSB(rainbow, 0.60f, 0.75f));
	DrawRect(x + 6, y + 6, 1, 2, Color::FromHSB(rainbow, 0.60f, 0.75f));
	DrawRect(x + 7, y + 7, 1, 1, Color::FromHSB(rainbow, 0.60f, 0.75f));
}

void DrawMenu()
{

	Input->GetClicked();
	MWindow* window = new MWindow(XorStr("INFAMYP2C - Self Leaked ZectixV1, rwby"), Vector2D(200, 200), Vector2D(675, 405));
	//categories
	MCategory* Rage = new MCategory(XorStr("Rage"), Vector2D(window->position.x, window->position.y + 30), window);
	MCategory* Legit = new MCategory(XorStr("Legit"), Vector2D(window->position.x, window->position.y + 60), window);
	MCategory* PlayerMods = new MCategory(XorStr("PlayerMods"), Vector2D(window->position.x, window->position.y + 90), window);
	MCategory* Visual = new MCategory(XorStr("Visuals"), Vector2D(window->position.x, window->position.y + 120), window);
	MCategory* Removals = new MCategory(XorStr("Removals"), Vector2D(window->position.x, window->position.y + 150), window);
	MCategory* AAC = new MCategory(XorStr("Anti-Cheats"), Vector2D(window->position.x, window->position.y + 180), window);
	MCategory* Skins = new MCategory(XorStr("Skins"), Vector2D(window->position.x, window->position.y + 210), window);
	MCategory* Playerlist = new MCategory(XorStr("PlayerList"), Vector2D(window->position.x, window->position.y + 240), window);
	MCategory* Colors = new MCategory(XorStr("Colors"), Vector2D(window->position.x, window->position.y + 270), window);

	MPlayerList* Player = new MPlayerList(Playerlist, XorStr("PlayerList"), Vector2D(window->position.x + 200, window->position.y + 30), Vector2D(245, 360));
	MCheckboxCategory* AAAToggle = new MCheckboxCategory(Playerlist, XorStr("Anti-Anti-Aim"), &Options.Rage.Aimbot.AntiAntiAim, Vector2D(window->position.x + 200, window->position.y + 20));
	Playerlist->AddChildControl(Player);
	Playerlist->AddChildControl(AAAToggle);


	// PlayerList CheckBoxes Only
	if (Global::CurrentPlayer > 0)
	{
		MCheckboxCategory* DisableHeadToggle = new MCheckboxCategory(Playerlist, XorStr("Disable Head"), &Options.Rage.Aimbot.AAA.bDisableHead[Global::CurrentPlayer], Vector2D(window->position.x + 460 + 10, window->position.y + 20 + 30));
		Playerlist->AddChildControl(DisableHeadToggle);
		std::vector<std::string> SelectBoneCorrection = { XorStr("Pelvis"), XorStr("Lower Body"), XorStr("Dick"), XorStr("Stomach"), XorStr("Chest"), XorStr("Neck"), XorStr("Head") };
		MComboCategory* BoneCorrectionCombo = new MComboCategory(Playerlist, XorStr("Bone Correction"), &Options.Rage.Aimbot.AAA.bone[Global::CurrentPlayer], Vector2D(window->position.x + 460 + 10, window->position.y + 20 + 110), SelectBoneCorrection, &Options.Menu.BoneSelectionCombo);
		Playerlist->AddChildControl(BoneCorrectionCombo);
		std::vector<std::string> AntiAimbotSelection = { XorStr("None"), XorStr("Level 1"), XorStr("Level 2"), XorStr("Level 3"), XorStr("Level 4"), XorStr("Level 5") };
		MComboCategory* AntiAimbotCombobox = new MComboCategory(Playerlist, XorStr("Anti-Aimbot Level"), &Options.Rage.Aimbot.AAA.Lisp[Global::CurrentPlayer], Vector2D(window->position.x + 460 + 10, window->position.y + 20 + 70), AntiAimbotSelection, &Options.Menu.AntiAimbotCombo);
		Playerlist->AddChildControl(AntiAimbotCombobox);
	}

	// Groupbox
	MGroup* RageGroup = new MGroup(Rage, XorStr("Ragebot"), Vector2D(window->position.x + 200, window->position.y + 30), Vector2D(226, 360));
	MGroup* RageGroup2 = new MGroup(Rage, XorStr("Etc"), Vector2D(window->position.x + 440, window->position.y + 30), Vector2D(227, 153));
	MGroup* RageGroup3 = new MGroup(Rage, XorStr("Anti-Aim"), Vector2D(window->position.x + 440, window->position.y + 200), Vector2D(228, 190));
	Rage->AddChildControl(RageGroup);
	Rage->AddChildControl(RageGroup2);
	Rage->AddChildControl(RageGroup3);

	//227,153
	MGroup* LegitGroup = new MGroup(Legit, XorStr("Legitbot"), Vector2D(window->position.x + 200, window->position.y + 30), Vector2D(226, 360));
	MGroup* TriggerGroup = new MGroup(Legit, XorStr("Triggerbot"), Vector2D(window->position.x + 440, window->position.y + 30), Vector2D(227, 153));

	MGroup* WeaponGroup = new MGroup(Legit, XorStr("Weapon-Settings"), Vector2D(window->position.x + 440, window->position.y + 200), Vector2D(228, 190));
	if (Engine->IsInGame())
	{

		if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_RIFLE)
		{
			MGroup* WeaponGroup = new MGroup(Legit, "Weapon-Settings (Rifle)", Vector2D(window->position.x + 440, window->position.y + 200), Vector2D(228, 190));
			Legit->AddChildControl(WeaponGroup);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_PISTOL)
		{
			MGroup* WeaponGroup = new MGroup(Legit, "Weapon-Settings (Pistol)", Vector2D(window->position.x + 440, window->position.y + 200), Vector2D(228, 190));
			Legit->AddChildControl(WeaponGroup);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SNIPER)
		{
			MGroup* WeaponGroup = new MGroup(Legit, "Weapon-Settings (Sniper)", Vector2D(window->position.x + 440, window->position.y + 200), Vector2D(228, 190));
			Legit->AddChildControl(WeaponGroup);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SMG)
		{
			MGroup* WeaponGroup = new MGroup(Legit, "Weapon-Settings (SMG)", Vector2D(window->position.x + 440, window->position.y + 200), Vector2D(228, 190));
			Legit->AddChildControl(WeaponGroup);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SHOTGUN)
		{
			MGroup* WeaponGroup = new MGroup(Legit, "Weapon-Settings (Shotgun)", Vector2D(window->position.x + 440, window->position.y + 200), Vector2D(228, 190));
			Legit->AddChildControl(WeaponGroup);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_MACHINEGUN)
		{
			MGroup* WeaponGroup = new MGroup(Legit, "Weapon-Settings (Machinegun)", Vector2D(window->position.x + 440, window->position.y + 200), Vector2D(228, 190));
			Legit->AddChildControl(WeaponGroup);
		}
	}
	Legit->AddChildControl(LegitGroup);
	Legit->AddChildControl(TriggerGroup);
	//Legit->AddChildControl(WeaponGroup);

	MGroup* pModsGroup = new MGroup(PlayerMods, XorStr("PlayerMods"), Vector2D(window->position.x + 200, window->position.y + 30), Vector2D(465, 360));
	PlayerMods->AddChildControl(pModsGroup);

	MGroup* VisualGroup = new MGroup(Visual, XorStr("Visuals"), Vector2D(window->position.x + 200, window->position.y + 30), Vector2D(465, 360));
	Visual->AddChildControl(VisualGroup);

	MGroup* RemovalGroup = new MGroup(Removals, XorStr("Removals"), Vector2D(window->position.x + 200, window->position.y + 30), Vector2D(465, 360));
	Removals->AddChildControl(RemovalGroup);

	//264,341
	//228,172

	MGroup* AACG = new MGroup(AAC, "Anti-Anti-Cheats", Vector2D(window->position.x + 200, window->position.y + 30), Vector2D(465, 360));
	AAC->AddChildControl(AACG);

	MGroup* SkinsGroup = new MGroup(Skins, "Skin-Changer", Vector2D(window->position.x + 200, window->position.y + 30), Vector2D(465, 360));
	Skins->AddChildControl(SkinsGroup);

	MGroup* ColorsGroup = new MGroup(Skins, "Colors", Vector2D(window->position.x + 200, window->position.y + 30), Vector2D(465, 360));
	Colors->AddChildControl(ColorsGroup);

	//add our categories to our windows as child controls

	// Rage
	MCheckbox* RageEnabled = new MCheckbox(RageGroup, "Enabled", &Options.Rage.Aimbot.Enabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 30));
	MCheckbox* AutowallToggle = new MCheckbox(RageGroup, "Autowall", &Options.Rage.Aimbot.Autowall, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 50));



	//MSlider*  SType = new MSlider(RageGroup, "StopType", &Options.Rage.Aimbot.StopType, 0, 5, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 170));
	MCheckbox* AScope = new MCheckbox(RageGroup, "Auto Scope", &Options.Rage.Aimbot.AutoScope, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 240));
	MCheckbox* EnemyOnlyR = new MCheckbox(RageGroup, "Enemy Only", &Options.Rage.Aimbot.EnemyOnly, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 260));
	MCheckbox* SAim = new MCheckbox(RageGroup, "Silent Aim", &Options.Rage.Aimbot.SilentAim, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 280));
	MCheckbox* pSAim = new MCheckbox(RageGroup, "pSilent(!wepconfigs)", &Options.Legit.Aimbot.PerfectSilentAim, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 300));
	MCheckbox* MMNSpread = new MCheckbox(RageGroup, "MM No Spread", &Options.Rage.Aimbot.PsuedoSpread, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 320));
	MCheckbox* AShoot = new MCheckbox(RageGroup, "Auto Shoot", &Options.Rage.Aimbot.AutoShoot, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 340));

	std::vector<std::string> RStype = { "None", "Stop", "StopCrouch", "Full-Stop", "Full-StopCrouch" };
	MCombo* SType = new MCombo(RageGroup, "Stoptype", &Options.Rage.Aimbot.StopType, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 210), RStype, &Options.Menu.StopTypeCombo);

	std::vector<std::string> TargetType = { "FOV", "Health", "Distance", "Threat", "Visible Bones", "Damage" };
	MCombo* Targeting = new MCombo(RageGroup, "Target Method", &Options.Rage.Aimbot.Targeting, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 170), TargetType, &Options.Menu.TargetTypeCombo);

	std::vector<std::string> HitScanType = { "Bones", "Multipoint", "Hitboxes", "Extreme", "Custom" };
	MCombo* HitScan = new MCombo(RageGroup, "Hitscans", &Options.Rage.Aimbot.HitScans, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 130), HitScanType, &Options.Menu.HitscanTypeCombo);

	std::vector<std::string> RHitboxes = { "Pelvis", "Lower Body", "Dick", "Stomach", "Chest", "Neck", "Head" };
	MCombo* Hitbox = new MCombo(RageGroup, "Hitbox", &Options.Rage.Aimbot.Hitbox, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 90), RHitboxes, &Options.Menu.RageHitboxCombo);

	MSliderFloat* MinDmg = new MSliderFloat(RageGroup2, "Min Damage", &Options.Rage.AutoWall.MinDamage, 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 30));
	MCheckbox* HitC = new MCheckbox(RageGroup2, "Hitchance", &Options.Rage.Aimbot.bHitchance, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 70));
	MCheckbox* HitCSniper = new MCheckbox(RageGroup2, "Hitchance Snipers", &Options.Rage.Aimbot.bHitchanceSnipers, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 90));
	MSliderFloat* HitchanceAmt = new MSliderFloat(RageGroup2, "Hitchance Amt", &Options.Rage.Aimbot.Hitchance, 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 110));

	MCheckbox* AAEnable = new MCheckbox(RageGroup3, "Enable Anti-Aim", &Options.Rage.AntiAim.Enabled, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 30));
	std::vector<std::string> AAYaws = { "Off", "Jitter", "Jitter-Synced", "Element", "Backwards", "Fake-Static", "Fake2", "Fake3", "Fake4", "Lisp-Backwards", "Lisp-Inverse" };
	MCombo* YawComboBox = new MCombo(RageGroup3, "Yaw", &Options.Rage.AntiAim.Yaw, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 110), AAYaws, &Options.Menu.AntiYawCombo);
	std::vector<std::string> AAPitchs = { "Off", "Emotion", "Lisp-Down", "Lisp-Up" };
	MCombo* PitchComboBox = new MCombo(RageGroup3, "Pitch", &Options.Rage.AntiAim.Pitch, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 70), AAPitchs, &Options.Menu.AntiPitchCombo);

	Rage->AddChildControl(RageEnabled);
	Rage->AddChildControl(AutowallToggle);
	Rage->AddChildControl(AShoot);
	Rage->AddChildControl(AScope);
	Rage->AddChildControl(EnemyOnlyR);
	Rage->AddChildControl(SAim);
	Rage->AddChildControl(pSAim);
	Rage->AddChildControl(MMNSpread);
	Rage->AddChildControl(MinDmg);
	Rage->AddChildControl(HitC);
	Rage->AddChildControl(HitCSniper);
	Rage->AddChildControl(HitchanceAmt);
	Rage->AddChildControl(AAEnable);
	Rage->AddChildControl(YawComboBox);
	Rage->AddChildControl(PitchComboBox);
	Rage->AddChildControl(SType);
	Rage->AddChildControl(Targeting);
	Rage->AddChildControl(HitScan);
	Rage->AddChildControl(Hitbox);

	auto lCheck = Options.AntiCheat.League;
	MCheckbox* LegitEnabled = new MCheckbox(LegitGroup, "Enabled", &Options.Legit.Aimbot.Enabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 30));
	MCheckbox* RCSToggle = new MCheckbox(LegitGroup, "Recoil Control System", &Options.Legit.Aimbot.RCS, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 50));
	Legit->AddChildControl(LegitEnabled);
	Legit->AddChildControl(RCSToggle);
	if (!lCheck)
	{
		MCheckbox* SilentAimLegit = new MCheckbox(LegitGroup, "SilentAim", &Options.Legit.Aimbot.SilentAim, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 70));
		MSliderFloat* FOVLegit = new MSliderFloat(LegitGroup, "FOV", &Options.Legit.Aimbot.Fov, 0.f, 180.f, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 90));
		MSliderFloat* SmoothX = new MSliderFloat(LegitGroup, "Smooth X", &Options.Legit.Aimbot.Smooth[0], 1.f, 100.f, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 120));
		MSliderFloat* SmoothY = new MSliderFloat(LegitGroup, "Smooth Y", &Options.Legit.Aimbot.Smooth[1], 1.f, 100.f, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 150));

		std::vector<std::string> LegitHitboxes = { "Pelvis", "Lower Body", "Dick", "Stomach", "Chest", "Neck", "Head" };
		MSelector* LegitHitbox = new MSelector(LegitGroup, "Hitbox", &Options.Legit.Aimbot.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 190), LegitHitboxes);

		if (Options.Legit.Aimbot.WeaponConfigs)
		{
			if (Engine->IsInGame())
			{

				if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_RIFLE)
				{
					std::vector<std::string> LeagueHitboxes = { "Pelvis", "Lower Body", "Dick", "Stomach", "Chest", "Neck", "Head" };
					MSelector* LeagueHitbox = new MSelector(LegitGroup, "Hitbox ( Rifle )", &Options.Legit.Aimbot.Configs.Rifles.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 190), LeagueHitboxes);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_PISTOL)
				{
					std::vector<std::string> LeagueHitboxes = { "Pelvis", "Lower Body", "Dick", "Stomach", "Chest", "Neck", "Head" };
					MSelector* LeagueHitbox = new MSelector(LegitGroup, "Hitbox ( Pistol )", &Options.Legit.Aimbot.Configs.Pistols.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 190), LeagueHitboxes);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SNIPER)
				{
					std::vector<std::string> LeagueHitboxes = { "Pelvis", "Lower Body", "Dick", "Stomach", "Chest", "Neck", "Head" };
					MSelector* LeagueHitbox = new MSelector(LegitGroup, "Hitbox ( Sniper )", &Options.Legit.Aimbot.Configs.Snipers.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 190), LeagueHitboxes);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SMG)
				{
					std::vector<std::string> LeagueHitboxes = { "Pelvis", "Lower Body", "Dick", "Stomach", "Chest", "Neck", "Head" };
					MSelector* LeagueHitbox = new MSelector(LegitGroup, "Hitbox ( SMG )", &Options.Legit.Aimbot.Configs.SMGs.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 190), LeagueHitboxes);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SHOTGUN)
				{
					std::vector<std::string> LeagueHitboxes = { "Pelvis", "Lower Body", "Dick", "Stomach", "Chest", "Neck", "Head" };
					MSelector* LeagueHitbox = new MSelector(LegitGroup, "Hitbox ( Shotgun )", &Options.Legit.Aimbot.Configs.Shotguns.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 190), LeagueHitboxes);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_MACHINEGUN)
				{
					std::vector<std::string> LeagueHitboxes = { "Pelvis", "Lower Body", "Dick", "Stomach", "Chest", "Neck", "Head" };
					MSelector* LeagueHitbox = new MSelector(LegitGroup, "Hitbox ( MG )", &Options.Legit.Aimbot.Configs.Machineguns.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 190), LeagueHitboxes);
					Legit->AddChildControl(LeagueHitbox);
				}
			}
		}
		MCheckbox* LegitEnemyOnly = new MCheckbox(LegitGroup, "Enemy Only", &Options.Legit.Aimbot.EnemyOnly, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 225));
		MCheckbox* ToggleWeaponConfigs = new MCheckbox(LegitGroup, "Weapon-Configs", &Options.Legit.Aimbot.WeaponConfigs, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 255));
		Legit->AddChildControl(SilentAimLegit);
		Legit->AddChildControl(FOVLegit);
		Legit->AddChildControl(SmoothX);
		Legit->AddChildControl(SmoothY);
		Legit->AddChildControl(LegitHitbox);
		Legit->AddChildControl(LegitEnemyOnly);
		Legit->AddChildControl(ToggleWeaponConfigs);
	}
	if (lCheck)
	{
		MSlider* FOVLeague = new MSlider(LegitGroup, "FOV", &Options.Legit.Aimbot.LFOV, 0, 180, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 70));
		MSlider* AimSmooth = new MSlider(LegitGroup, "Aim Speed", &Options.Legit.Aimbot.AimSpeed, 0, 300, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 100));
		MSlider* TimesSmooth = new MSlider(LegitGroup, "Multiply Smooth", &Options.Legit.Aimbot.MultiplySpeed, 0, 10, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 130));
		MSlider* FOVBoost = new MSlider(LegitGroup, "FOV Boost", &Options.Legit.Aimbot.FOVBOOST, 0, 10, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 160));
		//MKey* AimKey = new MKey(LegitGroup, "Aimbot Key", &Options.Legit.Aimbot.LKey, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 205));

		std::vector<std::string> TriggerFilter = { "None", "Most Damage", "Body Only", "No Arms or Head", "Head Only", "Arms Only" };
		MCombo* FilterTrigger = new MCombo(TriggerGroup, "Trigger Filter", &Options.Legit.Trigger.Filter, Vector2D(window->position.x + 440 + 25, window->position.y + 30 + 120), TriggerFilter, &Options.Menu.TriggerFilterCombo);
		MCheckbox* LeagueEnemyOnly = new MCheckbox(LegitGroup, "Enemy Only", &Options.Legit.Aimbot.EnemyOnly, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 255));
		MCheckbox* LeagueAngleNoise = new MCheckbox(LegitGroup, "Noise", &Options.Legit.Aimbot.RandomizeAngles, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 295));
		MSliderFloat* LeagueAngleNoiseAmt = new MSliderFloat(LegitGroup, "Noise Amount", &Options.Legit.Aimbot.AngleValue, 0.f, 20.f, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 315));
		MCheckbox* ToggleWeaponConfigs = new MCheckbox(LegitGroup, "Weapon-Configs", &Options.Legit.Aimbot.WeaponConfigs, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 275));



		Legit->AddChildControl(FOVLeague);
		Legit->AddChildControl(AimSmooth);
		Legit->AddChildControl(TimesSmooth);
		Legit->AddChildControl(FOVBoost);
		Legit->AddChildControl(LeagueEnemyOnly);
		Legit->AddChildControl(LeagueAngleNoise);
		Legit->AddChildControl(LeagueAngleNoiseAmt);
		Legit->AddChildControl(ToggleWeaponConfigs);

		std::vector<std::string> LeagueHitboxes = { "Pelvis", "Lower Body", "Dick", "Stomach", "Chest", "Neck", "Head" };
		if (!Options.Legit.Aimbot.WeaponConfigs)
		{
			MCombo* LeagueHitbox = new MCombo(LegitGroup, "Hitbox", &Options.Legit.Aimbot.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 225), LeagueHitboxes, &Options.Menu.LeagueHitboxCombo);
			Legit->AddChildControl(LeagueHitbox);
		}

		if (Options.Legit.Aimbot.WeaponConfigs)
		{
			if (Engine->IsInGame())
			{

				if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_RIFLE)
				{
					MCombo* LeagueHitbox = new MCombo(LegitGroup, "Hitbox ( Rifle )", &Options.Legit.Aimbot.Configs.Rifles.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 225), LeagueHitboxes, &Options.Menu.LeagueHitboxCombo);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_PISTOL)
				{
					MCombo* LeagueHitbox = new MCombo(LegitGroup, "Hitbox ( Pistol )", &Options.Legit.Aimbot.Configs.Pistols.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 225), LeagueHitboxes, &Options.Menu.LeagueHitboxCombo);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SNIPER)
				{
					MCombo* LeagueHitbox = new MCombo(LegitGroup, "Hitbox ( Sniper )", &Options.Legit.Aimbot.Configs.Snipers.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 225), LeagueHitboxes, &Options.Menu.LeagueHitboxCombo);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SMG)
				{
					MCombo* LeagueHitbox = new MCombo(LegitGroup, "Hitbox ( SMG )", &Options.Legit.Aimbot.Configs.SMGs.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 225), LeagueHitboxes, &Options.Menu.LeagueHitboxCombo);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SHOTGUN)
				{
					MCombo* LeagueHitbox = new MCombo(LegitGroup, "Hitbox ( Shotgun )", &Options.Legit.Aimbot.Configs.Shotguns.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 225), LeagueHitboxes, &Options.Menu.LeagueHitboxCombo);
					Legit->AddChildControl(LeagueHitbox);
				}
				else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_MACHINEGUN)
				{
					MCombo* LeagueHitbox = new MCombo(LegitGroup, "Hitbox ( MG )", &Options.Legit.Aimbot.Configs.Machineguns.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 225), LeagueHitboxes, &Options.Menu.LeagueHitboxCombo);
					Legit->AddChildControl(LeagueHitbox);
				}
			}
		}
	}

	MCheckbox* TriggerEnabled = new MCheckbox(TriggerGroup, "Enable", &Options.Legit.Trigger.Enabled, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 30));
	MCheckbox* TriggerFriends = new MCheckbox(TriggerGroup, "Enemy Only", &Options.Legit.Trigger.TriggerFriends, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 50));
	MKey* TriggerKey = new MKey(TriggerGroup, "Trigger Key", &Options.Legit.Trigger.Key, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 70));

	//MCheckbox* LegitEnabled = new MCheckbox(LegitGroup, "Enabled", &Options.PlayerMods.bhop.Enabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 30));

	Legit->AddChildControl(TriggerEnabled);
	Legit->AddChildControl(TriggerFriends);
	Legit->AddChildControl(TriggerKey);


	if (Engine->IsInGame())
	{

		if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_RIFLE)
		{
			MCheckbox* RifleTrigger = new MCheckbox(WeaponGroup, "Rifle Triggerbot", &Options.Legit.Aimbot.Configs.Rifles.Trigger, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 30));
			MCheckbox* RifleEnemyOnly = new MCheckbox(WeaponGroup, "Rifle Legitbot", &Options.Legit.Aimbot.Configs.Rifles.Enabled, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 40));
			MCheckbox* RifleRCS = new MCheckbox(WeaponGroup, "Rifle RCS", &Options.Legit.Aimbot.Configs.Rifles.RCS, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 50));

			if (!lCheck)
			{
				MCheckbox* RifleSilent = new MCheckbox(WeaponGroup, "Rifle SilentAim", &Options.Legit.Aimbot.Configs.Rifles.SilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MCheckbox* RiflepSilent = new MCheckbox(WeaponGroup, "Rifle pSilent", &Options.Legit.Aimbot.Configs.Rifles.PerfectSilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 70));
				MSliderFloat* RifleFOVLegit = new MSliderFloat(WeaponGroup, "Rifle FOV", &Options.Legit.Aimbot.Configs.Rifles.Fov, 0.f, 180.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSliderFloat* RifleSmoothX = new MSliderFloat(WeaponGroup, "Rifle Smooth X", &Options.Legit.Aimbot.Configs.Rifles.Smooth[0], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSliderFloat* RifleSmoothY = new MSliderFloat(WeaponGroup, "Rifle Smooth Y", &Options.Legit.Aimbot.Configs.Rifles.Smooth[1], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));


				Legit->AddChildControl(RifleSilent);
				Legit->AddChildControl(RiflepSilent);
				Legit->AddChildControl(RifleFOVLegit);
				Legit->AddChildControl(RifleSmoothX);
				Legit->AddChildControl(RifleSmoothY);
			}
			if (lCheck)
			{
				MSlider* RifleLeagueFOV = new MSlider(WeaponGroup, "Rifle FOV", &Options.Legit.Aimbot.Configs.Rifles.LFOV, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MSlider* RifleAimSpeed = new MSlider(WeaponGroup, "Rifle Aim Speed", &Options.Legit.Aimbot.Configs.Rifles.AimSpeed, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSlider* RifleMSpeed = new MSlider(WeaponGroup, "Rifle Multiply Speed", &Options.Legit.Aimbot.Configs.Rifles.MultiplySpeed, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSlider* RifleFOVBoost = new MSlider(WeaponGroup, "Rifle FOV Boost", &Options.Legit.Aimbot.Configs.Rifles.FOVBOOST, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));
				Legit->AddChildControl(RifleLeagueFOV);
				Legit->AddChildControl(RifleAimSpeed);
				Legit->AddChildControl(RifleMSpeed);
				Legit->AddChildControl(RifleFOVBoost);
			}

			Legit->AddChildControl(RifleTrigger);
			Legit->AddChildControl(RifleEnemyOnly);
			Legit->AddChildControl(RifleRCS);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_PISTOL)
		{
			MCheckbox* PistolTrigger = new MCheckbox(WeaponGroup, "Pistol Triggerbot", &Options.Legit.Aimbot.Configs.Pistols.Trigger, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 30));
			MCheckbox* PistolEnemyOnly = new MCheckbox(WeaponGroup, "Pistol Legitbot", &Options.Legit.Aimbot.Configs.Pistols.Enabled, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 40));
			MCheckbox* PistolRCS = new MCheckbox(WeaponGroup, "Pistol RCS", &Options.Legit.Aimbot.Configs.Pistols.RCS, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 50));

			if (!lCheck)
			{
				MCheckbox* PistolSilent = new MCheckbox(WeaponGroup, "Pistol SilentAim", &Options.Legit.Aimbot.Configs.Pistols.SilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MCheckbox* PistolpSilent = new MCheckbox(WeaponGroup, "Pistol pSilent", &Options.Legit.Aimbot.Configs.Pistols.PerfectSilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 70));
				MSliderFloat* PistolFOVLegit = new MSliderFloat(WeaponGroup, "Pistol FOV", &Options.Legit.Aimbot.Configs.Pistols.Fov, 0.f, 180.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSliderFloat* PistolSmoothX = new MSliderFloat(WeaponGroup, "Pistol Smooth X", &Options.Legit.Aimbot.Configs.Pistols.Smooth[0], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSliderFloat* PistolSmoothY = new MSliderFloat(WeaponGroup, "Pistol Smooth Y", &Options.Legit.Aimbot.Configs.Pistols.Smooth[1], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));


				Legit->AddChildControl(PistolSilent);
				Legit->AddChildControl(PistolpSilent);
				Legit->AddChildControl(PistolFOVLegit);
				Legit->AddChildControl(PistolSmoothX);
				Legit->AddChildControl(PistolSmoothY);
			}
			if (lCheck)
			{
				MSlider* PistolLeagueFOV = new MSlider(WeaponGroup, "Pistol FOV", &Options.Legit.Aimbot.Configs.Pistols.LFOV, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MSlider* PistolAimSpeed = new MSlider(WeaponGroup, "Pistol Aim Speed", &Options.Legit.Aimbot.Configs.Pistols.AimSpeed, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSlider* PistolMSpeed = new MSlider(WeaponGroup, "Pistol Multiply Speed", &Options.Legit.Aimbot.Configs.Pistols.MultiplySpeed, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSlider* PistolFOVBoost = new MSlider(WeaponGroup, "Pistol FOV Boost", &Options.Legit.Aimbot.Configs.Pistols.FOVBOOST, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));
				Legit->AddChildControl(PistolLeagueFOV);
				Legit->AddChildControl(PistolAimSpeed);
				Legit->AddChildControl(PistolMSpeed);
				Legit->AddChildControl(PistolFOVBoost);
			}

			Legit->AddChildControl(PistolTrigger);
			Legit->AddChildControl(PistolEnemyOnly);
			Legit->AddChildControl(PistolRCS);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SNIPER)
		{
			MCheckbox* SniperTrigger = new MCheckbox(WeaponGroup, "Sniper Triggerbot", &Options.Legit.Aimbot.Configs.Snipers.Trigger, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 30));
			MCheckbox* SniperEnemyOnly = new MCheckbox(WeaponGroup, "Sniper Legitbot", &Options.Legit.Aimbot.Configs.Snipers.Enabled, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 40));
			MCheckbox* SniperRCS = new MCheckbox(WeaponGroup, "Sniper RCS", &Options.Legit.Aimbot.Configs.Snipers.RCS, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 50));

			if (!lCheck)
			{
				MCheckbox* SniperSilent = new MCheckbox(WeaponGroup, "Sniper SilentAim", &Options.Legit.Aimbot.Configs.Snipers.SilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MCheckbox* SniperpSilent = new MCheckbox(WeaponGroup, "Sniper pSilent", &Options.Legit.Aimbot.Configs.Snipers.PerfectSilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 70));
				MSliderFloat* SniperFOVLegit = new MSliderFloat(WeaponGroup, "Sniper FOV", &Options.Legit.Aimbot.Configs.Snipers.Fov, 0.f, 180.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSliderFloat* SniperSmoothX = new MSliderFloat(WeaponGroup, "Sniper Smooth X", &Options.Legit.Aimbot.Configs.Snipers.Smooth[0], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSliderFloat* SniperSmoothY = new MSliderFloat(WeaponGroup, "Sniper Smooth Y", &Options.Legit.Aimbot.Configs.Snipers.Smooth[1], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));


				Legit->AddChildControl(SniperSilent);
				Legit->AddChildControl(SniperpSilent);
				Legit->AddChildControl(SniperFOVLegit);
				Legit->AddChildControl(SniperSmoothX);
				Legit->AddChildControl(SniperSmoothY);
			}
			if (lCheck)
			{
				MSlider* SniperLeagueFOV = new MSlider(WeaponGroup, "Sniper FOV", &Options.Legit.Aimbot.Configs.Snipers.LFOV, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MSlider* SniperAimSpeed = new MSlider(WeaponGroup, "Sniper Aim Speed", &Options.Legit.Aimbot.Configs.Snipers.AimSpeed, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSlider* SniperMSpeed = new MSlider(WeaponGroup, "Sniper Multiply Speed", &Options.Legit.Aimbot.Configs.Snipers.MultiplySpeed, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSlider* SniperFOVBoost = new MSlider(WeaponGroup, "Sniper FOV Boost", &Options.Legit.Aimbot.Configs.Snipers.FOVBOOST, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));
				Legit->AddChildControl(SniperLeagueFOV);
				Legit->AddChildControl(SniperAimSpeed);
				Legit->AddChildControl(SniperMSpeed);
				Legit->AddChildControl(SniperFOVBoost);
			}

			Legit->AddChildControl(SniperTrigger);
			Legit->AddChildControl(SniperEnemyOnly);
			Legit->AddChildControl(SniperRCS);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SMG)
		{
			MCheckbox* SMGTrigger = new MCheckbox(WeaponGroup, "SMG Triggerbot", &Options.Legit.Aimbot.Configs.SMGs.Trigger, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 30));
			MCheckbox* SMGEnemyOnly = new MCheckbox(WeaponGroup, "SMG Legitbot", &Options.Legit.Aimbot.Configs.SMGs.Enabled, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 40));
			MCheckbox* SMGRCS = new MCheckbox(WeaponGroup, "SMG RCS", &Options.Legit.Aimbot.Configs.SMGs.RCS, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 50));

			if (!lCheck)
			{
				MCheckbox* SMGSilent = new MCheckbox(WeaponGroup, "SMG SilentAim", &Options.Legit.Aimbot.Configs.SMGs.SilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MCheckbox* SMGpSilent = new MCheckbox(WeaponGroup, "SMG pSilent", &Options.Legit.Aimbot.Configs.SMGs.PerfectSilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 70));
				MSliderFloat* SMGFOVLegit = new MSliderFloat(WeaponGroup, "SMG FOV", &Options.Legit.Aimbot.Configs.SMGs.Fov, 0.f, 180.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSliderFloat* SMGSmoothX = new MSliderFloat(WeaponGroup, "SMG Smooth X", &Options.Legit.Aimbot.Configs.SMGs.Smooth[0], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSliderFloat* SMGSmoothY = new MSliderFloat(WeaponGroup, "SMG Smooth Y", &Options.Legit.Aimbot.Configs.SMGs.Smooth[1], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));


				Legit->AddChildControl(SMGSilent);
				Legit->AddChildControl(SMGpSilent);
				Legit->AddChildControl(SMGFOVLegit);
				Legit->AddChildControl(SMGSmoothX);
				Legit->AddChildControl(SMGSmoothY);
			}
			if (lCheck)
			{
				MSlider* SMGLeagueFOV = new MSlider(WeaponGroup, "SMG FOV", &Options.Legit.Aimbot.Configs.SMGs.LFOV, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MSlider* SMGAimSpeed = new MSlider(WeaponGroup, "SMG Aim Speed", &Options.Legit.Aimbot.Configs.SMGs.AimSpeed, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSlider* SMGMSpeed = new MSlider(WeaponGroup, "SMG Multiply Speed", &Options.Legit.Aimbot.Configs.SMGs.MultiplySpeed, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSlider* SMGFOVBoost = new MSlider(WeaponGroup, "SMG FOV Boost", &Options.Legit.Aimbot.Configs.SMGs.FOVBOOST, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));
				Legit->AddChildControl(SMGLeagueFOV);
				Legit->AddChildControl(SMGAimSpeed);
				Legit->AddChildControl(SMGMSpeed);
				Legit->AddChildControl(SMGFOVBoost);
			}

			Legit->AddChildControl(SMGTrigger);
			Legit->AddChildControl(SMGEnemyOnly);
			Legit->AddChildControl(SMGRCS);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_SHOTGUN)
		{
			MCheckbox* SHOTGUNTrigger = new MCheckbox(WeaponGroup, "Shotguns Triggerbot", &Options.Legit.Aimbot.Configs.Shotguns.Trigger, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 30));
			MCheckbox* SHOTGUNEnemyOnly = new MCheckbox(WeaponGroup, "Shotguns Legitbot", &Options.Legit.Aimbot.Configs.Shotguns.Enabled, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 40));
			MCheckbox* SHOTGUNRCS = new MCheckbox(WeaponGroup, "Shotguns RCS", &Options.Legit.Aimbot.Configs.Shotguns.RCS, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 50));

			if (!lCheck)
			{
				MCheckbox* SHOTGUNSilent = new MCheckbox(WeaponGroup, "Shotgun SilentAim", &Options.Legit.Aimbot.Configs.Shotguns.SilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MCheckbox* SHOTGUNpSilent = new MCheckbox(WeaponGroup, "Shotgun pSilent", &Options.Legit.Aimbot.Configs.Shotguns.PerfectSilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 70));
				MSliderFloat* SHOTGUNFOVLegit = new MSliderFloat(WeaponGroup, "Shotgun FOV", &Options.Legit.Aimbot.Configs.Shotguns.Fov, 0.f, 180.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSliderFloat* SHOTGUNSmoothX = new MSliderFloat(WeaponGroup, "Shotgun Smooth X", &Options.Legit.Aimbot.Configs.Shotguns.Smooth[0], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSliderFloat* SHOTGUNSmoothY = new MSliderFloat(WeaponGroup, "Shotgun Smooth Y", &Options.Legit.Aimbot.Configs.Shotguns.Smooth[1], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));


				Legit->AddChildControl(SHOTGUNSilent);
				Legit->AddChildControl(SHOTGUNpSilent);
				Legit->AddChildControl(SHOTGUNFOVLegit);
				Legit->AddChildControl(SHOTGUNSmoothX);
				Legit->AddChildControl(SHOTGUNSmoothY);
			}
			if (lCheck)
			{
				MSlider* SHOTGUNLeagueFOV = new MSlider(WeaponGroup, "Shotgun FOV", &Options.Legit.Aimbot.Configs.Shotguns.LFOV, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MSlider* SHOTGUNAimSpeed = new MSlider(WeaponGroup, "Shotgun Aim Speed", &Options.Legit.Aimbot.Configs.Shotguns.AimSpeed, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSlider* SHOTGUNMSpeed = new MSlider(WeaponGroup, "Shotgun Multiply Speed", &Options.Legit.Aimbot.Configs.Shotguns.MultiplySpeed, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSlider* SHOTGUNFOVBoost = new MSlider(WeaponGroup, "Shotgun FOV Boost", &Options.Legit.Aimbot.Configs.Shotguns.FOVBOOST, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));
				Legit->AddChildControl(SHOTGUNLeagueFOV);
				Legit->AddChildControl(SHOTGUNAimSpeed);
				Legit->AddChildControl(SHOTGUNMSpeed);
				Legit->AddChildControl(SHOTGUNFOVBoost);
			}

			Legit->AddChildControl(SHOTGUNTrigger);
			Legit->AddChildControl(SHOTGUNEnemyOnly);
			Legit->AddChildControl(SHOTGUNRCS);
		}
		else if (Global::LocalPlayer->GetWeapon()->GetWeaponType() == WEPCLASS_MACHINEGUN)
		{
			MCheckbox* MACHINEGUNTrigger = new MCheckbox(WeaponGroup, "MG Triggerbot", &Options.Legit.Aimbot.Configs.Machineguns.Trigger, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 30));
			MCheckbox* MACHINEGUNEnemyOnly = new MCheckbox(WeaponGroup, "MG Legitbot", &Options.Legit.Aimbot.Configs.Machineguns.Enabled, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 40));
			MCheckbox* MACHINEGUNRCS = new MCheckbox(WeaponGroup, "MG RCS", &Options.Legit.Aimbot.Configs.Machineguns.RCS, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 50));

			if (!lCheck)
			{
				MCheckbox* MACHINEGUNSilent = new MCheckbox(WeaponGroup, "MG SilentAim", &Options.Legit.Aimbot.Configs.Machineguns.SilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MCheckbox* MACHINEGUNpSilent = new MCheckbox(WeaponGroup, "MG pSilent", &Options.Legit.Aimbot.Configs.Machineguns.PerfectSilentAim, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 70));
				MSliderFloat* MACHINEGUNFOVLegit = new MSliderFloat(WeaponGroup, "MG FOV", &Options.Legit.Aimbot.Configs.Machineguns.Fov, 0.f, 180.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSliderFloat* MACHINEGUNSmoothX = new MSliderFloat(WeaponGroup, "MG Smooth X", &Options.Legit.Aimbot.Configs.Machineguns.Smooth[0], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSliderFloat* MACHINEGUNSmoothY = new MSliderFloat(WeaponGroup, "MG Smooth Y", &Options.Legit.Aimbot.Configs.Machineguns.Smooth[1], 1.f, 100.f, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));


				Legit->AddChildControl(MACHINEGUNSilent);
				Legit->AddChildControl(MACHINEGUNpSilent);
				Legit->AddChildControl(MACHINEGUNFOVLegit);
				Legit->AddChildControl(MACHINEGUNSmoothX);
				Legit->AddChildControl(MACHINEGUNSmoothY);
			}
			if (lCheck)
			{
				MSlider* MACHINEGUNLeagueFOV = new MSlider(WeaponGroup, "MG FOV", &Options.Legit.Aimbot.Configs.Machineguns.LFOV, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 60));
				MSlider* MACHINEGUNAimSpeed = new MSlider(WeaponGroup, "MG Aim Speed", &Options.Legit.Aimbot.Configs.Machineguns.AimSpeed, 1, 300, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 90));
				MSlider* MACHINEGUNMSpeed = new MSlider(WeaponGroup, "MG Multiply Speed", &Options.Legit.Aimbot.Configs.Machineguns.MultiplySpeed, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 120));
				MSlider* MACHINEGUNFOVBoost = new MSlider(WeaponGroup, "MG FOV Boost", &Options.Legit.Aimbot.Configs.Machineguns.FOVBOOST, 1, 10, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 190 + 150));
				Legit->AddChildControl(MACHINEGUNLeagueFOV);
				Legit->AddChildControl(MACHINEGUNAimSpeed);
				Legit->AddChildControl(MACHINEGUNMSpeed);
				Legit->AddChildControl(MACHINEGUNFOVBoost);
			}

			Legit->AddChildControl(MACHINEGUNTrigger);
			Legit->AddChildControl(MACHINEGUNEnemyOnly);
			Legit->AddChildControl(MACHINEGUNRCS);
		}

	}

	std::vector<std::string> TriggerFilter = { "None", "Most Damage", "Body Only", "No Arms or Head", "Head Only", "Arms Only" };
	MCombo* FilterTrigger = new MCombo(TriggerGroup, "Trigger Filter", &Options.Legit.Trigger.Filter, Vector2D(window->position.x + 440 + 25, window->position.y + 30 + 100), TriggerFilter, &Options.Menu.TriggerFilterCombo);
	Legit->AddChildControl(FilterTrigger);

	// PlayerMods
	MCheckbox* BHop = new MCheckbox(pModsGroup, "Bunnyhop", &Options.PlayerMods.bhop.Enabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 30));
	MCheckbox* AutoStrafe = new MCheckbox(pModsGroup, "Autostrafe", &Options.PlayerMods.AutoStrafe.Enabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 50));
	MCheckbox* RAutoStrafe = new MCheckbox(pModsGroup, "Rage Autostrafe", &Options.PlayerMods.AutoStrafe.REnabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 70));
	MCheckbox* AirStuck = new MCheckbox(pModsGroup, "Airstuck", &Options.PlayerMods.AirStuck.Enabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 90));
	MKey* AirStuckKey = new MKey(pModsGroup, "Airstuck Key", &Options.PlayerMods.AirStuck.Key, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 110));

	std::vector<std::string> ClanTagType = { "Off", "Infamy", "Valve" };
	MSelector* ClanTags = new MSelector(pModsGroup, "ClanTags", &Options.PlayerMods.ClanTags.Enabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 140), ClanTagType);

	std::vector<std::string> FlashAmt = { "Off", "10%", "20%", "30%", "40%", "50%", "60%", "70%", "80%", "90%", "100%" };
	MSelector* CustomFlash = new MSelector(pModsGroup, "Custom No-Flash", &Options.PlayerMods.Flash, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 180), FlashAmt);

	MSliderFloat* ESPR = new MSliderFloat(ColorsGroup, "ESP Red", &Options.Visuals.ESP.VisibleColor[0], 0, 255, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 30));
	MSliderFloat* ESPG = new MSliderFloat(ColorsGroup, "ESP Green", &Options.Visuals.ESP.VisibleColor[1], 0, 255, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 60));
	MSliderFloat* ESPB = new MSliderFloat(ColorsGroup, "ESP Blue", &Options.Visuals.ESP.VisibleColor[2], 0, 255, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 90));

	MSliderFloat* ESPRN = new MSliderFloat(ColorsGroup, "ESP Red Non-Vis", &Options.Visuals.ESP.NonVisibleColor[0], 0, 255, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 120));
	MSliderFloat* ESPGN = new MSliderFloat(ColorsGroup, "ESP Green Non-Vis", &Options.Visuals.ESP.NonVisibleColor[1], 0, 255, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 150));
	MSliderFloat* ESPBN = new MSliderFloat(ColorsGroup, "ESP Blue Non-Vis", &Options.Visuals.ESP.NonVisibleColor[2], 0, 255, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 180));

	MSliderFloat* ChamsR = new MSliderFloat(ColorsGroup, "Chams Red", &Options.Visuals.Chams.EnemyColor[0], 0, 255, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 210));
	MSliderFloat* ChamsG = new MSliderFloat(ColorsGroup, "Chams Green", &Options.Visuals.Chams.EnemyColor[1], 0, 255, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 240));
	MSliderFloat* ChamsB = new MSliderFloat(ColorsGroup, "Chams Blue", &Options.Visuals.Chams.EnemyColor[2], 0, 255, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 20 + 270));

	MSliderFloat* ChamsRN = new MSliderFloat(ColorsGroup, "Chams Red Non-Vis", &Options.Visuals.Chams.EnemyColorWall[0], 0, 255, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 30));
	MSliderFloat* ChamsGN = new MSliderFloat(ColorsGroup, "Chams Green Non-Vis", &Options.Visuals.Chams.EnemyColorWall[1], 0, 255, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 60));
	MSliderFloat* ChamsBN = new MSliderFloat(ColorsGroup, "Chams Blue Non-Vis", &Options.Visuals.Chams.EnemyColorWall[2], 0, 255, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 90));

	MSliderFloat* GlowR = new MSliderFloat(ColorsGroup, "Glow Red", &Options.Visuals.Glow.TeamColor[0], 0, 255, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 120));
	MSliderFloat* GlowG = new MSliderFloat(ColorsGroup, "Glow Green", &Options.Visuals.Glow.TeamColor[1], 0, 255, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 150));
	MSliderFloat* GlowB = new MSliderFloat(ColorsGroup, "Glow Blue", &Options.Visuals.Glow.TeamColor[2], 0, 255, 150, Vector2D(window->position.x + 440 + 25, window->position.y + 20 + 180));

	Colors->AddChildControl(ESPR);
	Colors->AddChildControl(ESPG);
	Colors->AddChildControl(ESPB);

	Colors->AddChildControl(ESPRN);
	Colors->AddChildControl(ESPGN);
	Colors->AddChildControl(ESPBN);

	Colors->AddChildControl(ChamsR);
	Colors->AddChildControl(ChamsG);
	Colors->AddChildControl(ChamsB);

	Colors->AddChildControl(ChamsRN);
	Colors->AddChildControl(ChamsGN);
	Colors->AddChildControl(ChamsBN);

	Colors->AddChildControl(GlowR);
	Colors->AddChildControl(GlowG);
	Colors->AddChildControl(GlowB);

	PlayerMods->AddChildControl(BHop);
	PlayerMods->AddChildControl(AutoStrafe);
	PlayerMods->AddChildControl(RAutoStrafe);
	PlayerMods->AddChildControl(AirStuck);
	PlayerMods->AddChildControl(AirStuckKey);
	PlayerMods->AddChildControl(ClanTags);
	PlayerMods->AddChildControl(CustomFlash);

	// Visuals
	MCheckbox* ESPEnabled = new MCheckbox(VisualGroup, "Enabled", &Options.Visuals.ESP.Enabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 30));
	MCheckbox* EnemyOnly = new MCheckbox(VisualGroup, "EnemyOnly", &Options.Visuals.ESP.EnemyOnly, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 50));
	MCheckbox* Box = new MCheckbox(VisualGroup, "Box", &Options.Visuals.ESP.Box, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 70));
	MSlider*  HealthOption = new MSlider(VisualGroup, "Health", &Options.Visuals.ESP.Health, 0, 2, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 90));
	MCheckbox* Name = new MCheckbox(VisualGroup, "Name", &Options.Visuals.ESP.Name, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 130));
	MCheckbox* Weapon = new MCheckbox(VisualGroup, "Weapon", &Options.Visuals.ESP.Weapon, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 150));
	MCheckbox* Distance = new MCheckbox(VisualGroup, "Distance", &Options.Visuals.ESP.Distance, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 170));
	MCheckbox* Bone = new MCheckbox(VisualGroup, "Bone", &Options.Visuals.ESP.Bone, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 190));
	MCheckbox* Flashed = new MCheckbox(VisualGroup, "Flashed", &Options.Visuals.ESP.Flashed, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 210));
	MCheckbox* Ammo = new MCheckbox(VisualGroup, "Ammo", &Options.Visuals.ESP.Ammo, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 230));
	MCheckbox* Callout = new MCheckbox(VisualGroup, "Callout", &Options.Visuals.ESP.Callout, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 250));
	MCheckbox* World = new MCheckbox(VisualGroup, "World", &Options.Visuals.ESP.World, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 270));
	MCheckbox* C4Timer = new MCheckbox(VisualGroup, "C4 Timer", &Options.Visuals.ESP.DrawBomb, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 290));
	MCheckbox* C4Defuser = new MCheckbox(VisualGroup, "C4 Defuser", &Options.Visuals.ESP.DrawDefuser, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 310));
	MSlider* FOVView = new MSlider(VisualGroup, "Viewmodel FOV", &Options.Visuals.ESP.FOV2, 1, 40, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 325));

	MCheckbox* AimPoint = new MCheckbox(VisualGroup, "AimPoint", &Options.Visuals.ESP.AimPoint, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 30));
	MCheckbox* Barrel = new MCheckbox(VisualGroup, "Barrel", &Options.Visuals.ESP.Barrel, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 50));
	MCheckbox* HitMarker = new MCheckbox(VisualGroup, "Hitmarker", &Options.Visuals.ESP.Hitmarker, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 70));
	MCheckbox* DamageIndicator = new MCheckbox(VisualGroup, "Damage Indicator", &Options.Visuals.ESP.DamageIndicator, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 90));
	MCheckbox* RecoilCrosshair = new MCheckbox(VisualGroup, "Recoil Crosshair", &Options.Visuals.ESP.RecoilCrosshair, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 110));
	MCheckbox* AutoAccept = new MCheckbox(VisualGroup, "Auto Accept", &Options.Visuals.ESP.AutoAccept, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 130));
	MCheckbox* RevealAll = new MCheckbox(VisualGroup, "Reveal Ranks", &Options.Visuals.ESP.RankESP, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 150));
	MSlider*  FOVS = new MSlider(VisualGroup, "FOV", &Options.Visuals.ESP.FOV, 0, 40, 150, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 170));
	MSlider*  Glow = new MSlider(VisualGroup, "Glow", &Options.Visuals.ESP.DrawGlowS, 0, 2, 150, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 200));
	MCheckbox* Chams = new MCheckbox(VisualGroup, "Chams", &Options.Visuals.Chams.Enabled, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 240));
	MSlider*  ChamsType = new MSlider(VisualGroup, "Chams Type", &Options.Visuals.Chams.Mode, 0, 2, 150, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 260));
	MCheckbox* ChamsXQZ = new MCheckbox(VisualGroup, "Chams XQZ", &Options.Visuals.Chams.XQZ, Vector2D(window->position.x + 460 + 25,   window->position.y + 30 + 300));
	MCheckbox* DLight = new MCheckbox(VisualGroup, "DLights", &Options.Visuals.ESP.DLight, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 320));
	MCheckbox* GrenadeTracer = new MCheckbox(VisualGroup, "NadeTracer", &Options.Visuals.ESP.NadeTracer, Vector2D(window->position.x + 460 + 25, window->position.y + 30 + 340));

	VisualGroup->AddChildControl(ESPEnabled);
	VisualGroup->AddChildControl(EnemyOnly);
	VisualGroup->AddChildControl(Box);
	VisualGroup->AddChildControl(HealthOption);
	VisualGroup->AddChildControl(Name);
	VisualGroup->AddChildControl(Weapon);
	VisualGroup->AddChildControl(Distance);
	VisualGroup->AddChildControl(Bone);
	VisualGroup->AddChildControl(Flashed);
	VisualGroup->AddChildControl(Ammo);
	VisualGroup->AddChildControl(Callout);
	VisualGroup->AddChildControl(World);
	VisualGroup->AddChildControl(C4Timer);
	VisualGroup->AddChildControl(C4Defuser);
	VisualGroup->AddChildControl(FOVView);

	VisualGroup->AddChildControl(AimPoint);
	VisualGroup->AddChildControl(Barrel);
	VisualGroup->AddChildControl(HitMarker);
	VisualGroup->AddChildControl(DamageIndicator);
	VisualGroup->AddChildControl(RecoilCrosshair);
	VisualGroup->AddChildControl(AutoAccept);
	VisualGroup->AddChildControl(RevealAll);
	VisualGroup->AddChildControl(FOVS);
	VisualGroup->AddChildControl(Glow);
	VisualGroup->AddChildControl(Chams);
	VisualGroup->AddChildControl(ChamsType);
	VisualGroup->AddChildControl(ChamsXQZ);
	VisualGroup->AddChildControl(DLight);
	VisualGroup->AddChildControl(GrenadeTracer);


	// Removals
	MCheckbox* NHands = new MCheckbox(RemovalGroup, "No Hands", &Options.Visuals.Removals.Hands, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 30));
	MCheckbox* WHands = new MCheckbox(RemovalGroup, "Wireframe Hands", &Options.Visuals.Removals.WireframeHands, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 50));
	MCheckbox* NWeapon = new MCheckbox(RemovalGroup, "No Weapon", &Options.Visuals.Removals.Weapon, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 70));
	MCheckbox* WWeapon = new MCheckbox(RemovalGroup, "Wireframe Weapons", &Options.Visuals.Removals.WireframeWep, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 90));
	MCheckbox* NoVis = new MCheckbox(RemovalGroup, "No Visual Recoil", &Options.Visuals.Removals.VisualRecoil, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 110));
	MCheckbox* NoRecoil = new MCheckbox(RemovalGroup, "No Recoil", &Options.Visuals.Removals.Recoil, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 130));
	MCheckbox* NoFlash = new MCheckbox(RemovalGroup, "No Flash", &Options.Visuals.Removals.Flash, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 150));

	Removals->AddChildControl(NHands);
	Removals->AddChildControl(WHands);
	Removals->AddChildControl(NWeapon);
	Removals->AddChildControl(WWeapon);
	Removals->AddChildControl(NoVis);
	Removals->AddChildControl(NoRecoil);
	Removals->AddChildControl(NoFlash);



	// Anti-Anti-Cheats
	MCheckbox* VAC = new MCheckbox(pModsGroup, "Prevent Valve Anti-Cheat bans", &Options.AntiCheat.VAC, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 30));
	MCheckbox* Untrusted = new MCheckbox(pModsGroup, "Prevent Untrusted bans", &Options.AntiCheat.MM, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 50));
	MCheckbox* SMAC = new MCheckbox(pModsGroup, "Prevent Sourcemod Anti-Cheat bans", &Options.AntiCheat.SMAC, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 70));
	MCheckbox* LAC = new MCheckbox(pModsGroup, "Prevent League Anti-Cheat bans", &Options.AntiCheat.League, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 90));

	AAC->AddChildControl(VAC);
	AAC->AddChildControl(Untrusted);
	AAC->AddChildControl(SMAC);
	AAC->AddChildControl(LAC);


	MCheckbox* SkinsToggle = new MCheckbox(SkinsGroup, "Enabled", &Options.Skins.Enabled, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 30));
	MCheckbox* LeftHandKnifeToggle = new MCheckbox(SkinsGroup, "Enable Left Hand Knife", &Options.Skins.LeftHandKnife, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 50));

	std::vector<std::string> KnifeSelect = { "Off", "Bayonet", "Flip-Knife", "Gut-Knife", "Karambit", "M9-Bayonet", "Huntsman Knife", "Butterfly Knife", "Falchion Knife", "Shadow Daggers", "Bowie Knife" };
	MSelector* DesiredKnife = new MSelector(SkinsGroup, "Select a Knife", &Options.Skins.KnifeSelect, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 80), KnifeSelect);
	MSlider* StatTrakNum = new MSlider(SkinsGroup, "StatTrak Amount", &Options.Skins.StatTrak, 0, 9999, 150, Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 110));
	MButtonGroup* ForceUpdateButton = new MButtonGroup(SkinsGroup, "Update Skins", Vector2D(window->position.x + 200 + 25, window->position.y + 30 + 150), Vector2D(150, 30));
	MString* SkinNotice = new MString(SkinsGroup, "Trying to edit skins? You can edit them on the Web Config Panel.", Vector2D(window->position.x + 200 + 185, window->position.y + 30 + 200));

	if (Options.Menu.Skins)
	{
		if (Input->Clicked(window->position.x + 200 + 25, window->position.y + 30 + 150, 150, 30))
		{
			ConVar *clfullupdate = Cvar->FindVar(XorStr("cl_fullupdate"));
			clfullupdate->nFlags = FCVAR_NONE;
			Engine->ClientCmd_Unrestricted(XorStr("cl_fullupdate"));
		}
	}

	Skins->AddChildControl(SkinsToggle);
	Skins->AddChildControl(LeftHandKnifeToggle);
	Skins->AddChildControl(DesiredKnife);
	Skins->AddChildControl(StatTrakNum);
	Skins->AddChildControl(ForceUpdateButton);
	Skins->AddChildControl(SkinNotice);
	//Skins->AddChildControl(SkinPanelButton);



	MButton* Load = new MButton(XorStr("Load"), Vector2D(window->position.x + 20, window->position.y + 340), Vector2D(170, 10));
	MButton* Save = new MButton(XorStr("Save"), Vector2D(window->position.x + 20, window->position.y + 360), Vector2D(170, 10));
	MButton* WebConfigs = new MButton(XorStr("Web Config Panel"), Vector2D(window->position.x + 20, window->position.y + 380), Vector2D(170, 10));

	std::vector<std::string> Configs = { XorStr("Default"), XorStr("Legit"), XorStr("Rage"), XorStr("League") };
	MComboNoParent* ConfigsType = new MComboNoParent("Selected Config", &Options.Config.Current, Vector2D(window->position.x + 20, window->position.y + 320), Configs, &Options.Menu.ConfigCombo);

	if (Input->Clicked(window->position.x + 20, window->position.y + 340, 170, 10) && !Options.Menu.ConfigCombo)
	{
		ConSys->LoadConfig();
	}
	if (Input->Clicked(window->position.x + 20, window->position.y + 360, 170, 10) && !Options.Menu.ConfigCombo)
	{
		ConSys->SaveConfig();
	}
	if (Input->Clicked(window->position.x + 20, window->position.y + 380, 170, 10) && !Options.Menu.ConfigCombo)
	{
		ShellExecute(nullptr, XorStr("open"), XorStr("bigwebsitetouseniceconfigs"), nullptr, nullptr, SW_SHOWNORMAL);
	}
	// tabs
	window->AddChildControl(Rage);
	window->AddChildControl(Legit);
	window->AddChildControl(PlayerMods);
	window->AddChildControl(Visual);
	window->AddChildControl(Removals);
	window->AddChildControl(AAC);
	window->AddChildControl(Skins);
	window->AddChildControl(Playerlist);
	window->AddChildControl(Colors);
	window->AddChildControl(Load);
	window->AddChildControl(Save);
	window->AddChildControl(WebConfigs);
	window->AddChildControl(ConfigsType);

	//Buttons->DrawButton("Load", window->position.x + 20, window->position.y + 280, 150, 30);
	//Buttons->DrawButton("Save", window->position.x + 20, window->position.y + 320, 150, 30);

	Rage->active = Options.Menu.Ragebot;
	Legit->active = Options.Menu.Legitbot;
	PlayerMods->active = Options.Menu.PlayerMods;
	Visual->active = Options.Menu.Visuals;
	Removals->active = Options.Menu.Removals;
	AAC->active = Options.Menu.AAC;
	Skins->active = Options.Menu.Skins;
	Playerlist->active = Options.Menu.PlayerList;
	Colors->active = Options.Menu.VisualColors;

	//ragebot
	if (Input->Clicked(window->position.x + 20, window->position.y + 20, GetStringWidth(Impact, "Rage"), 30))
	{
		Options.Menu.Ragebot = true;
		Options.Menu.PlayerMods = false;
		Options.Menu.Legitbot = false;
		Options.Menu.Visuals = false;
		Options.Menu.Removals = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
		Options.Menu.PlayerList = false;
		Options.Menu.VisualColors = false;
	}

	if (Input->Clicked(window->position.x + 20, window->position.y + 50, GetStringWidth(Impact, "Legit"), 30))
	{
		Options.Menu.Legitbot = true;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Visuals = false;
		Options.Menu.Removals = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
		Options.Menu.PlayerList = false;
		Options.Menu.VisualColors = false;
	}

	if (Input->Clicked(window->position.x + 20, window->position.y + 80, GetStringWidth(Impact, "PlayerMods"), 30))
	{
		Options.Menu.PlayerMods = true;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.Visuals = false;
		Options.Menu.Removals = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
		Options.Menu.PlayerList = false;
		Options.Menu.VisualColors = false;
	}

	if (Input->Clicked(window->position.x + 20, window->position.y + 110, GetStringWidth(Impact, "Visuals"), 30))
	{
		Options.Menu.Visuals = true;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.Removals = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
		Options.Menu.PlayerList = false;
		Options.Menu.VisualColors = false;
	}

	if (Input->Clicked(window->position.x + 20, window->position.y + 140, GetStringWidth(Impact, "Removals"), 30))
	{
		Options.Menu.Removals = true;
		Options.Menu.Visuals = false;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
		Options.Menu.PlayerList = false;
		Options.Menu.VisualColors = false;
	}

	if (Input->Clicked(window->position.x + 20, window->position.y + 170, GetStringWidth(Impact, "Anti-Cheats"), 30))
	{
		Options.Menu.AAC = true;
		Options.Menu.Removals = false;
		Options.Menu.Visuals = false;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.Skins = false;
		Options.Menu.PlayerList = false;
		Options.Menu.VisualColors = false;
	}

	if (Input->Clicked(window->position.x + 20, window->position.y + 200, GetStringWidth(Impact, "Skins"), 30))
	{
		Options.Menu.Skins = true;
		Options.Menu.AAC = false;
		Options.Menu.Removals = false;
		Options.Menu.Visuals = false;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.PlayerList = false;
		Options.Menu.VisualColors = false;
	}
	if (Input->Clicked(window->position.x + 20, window->position.y + 230, GetStringWidth(Impact, "PlayerList"), 30))
	{
		Options.Menu.PlayerList = true;
		Options.Menu.Skins = false;
		Options.Menu.AAC = false;
		Options.Menu.Removals = false;
		Options.Menu.Visuals = false;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.VisualColors = false;
	}
	if (Input->Clicked(window->position.x + 20, window->position.y + 260, GetStringWidth(Impact, "Colors"), 30))
	{
		Options.Menu.VisualColors = true;
		Options.Menu.PlayerList = false;
		Options.Menu.Skins = false;
		Options.Menu.AAC = false;
		Options.Menu.Removals = false;
		Options.Menu.Visuals = false;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
	}

	window->Draw();
}

void __fastcall Game::hkdPaintTraverse(void* ecx, void* edx, unsigned int vguiPanel, bool forceRepaint, bool allowForce)
{
	oPaintTraverse(ecx, edx, vguiPanel, forceRepaint, allowForce);
	static unsigned int MatTopPanel;
	if (!MatTopPanel)
	{
		auto cName = VPanel->GetName(vguiPanel);
		if (!strcmp(cName, XorStr("MatSystemTopPanel")))
		{
			MatTopPanel = vguiPanel;
		}
	}
	if (MatTopPanel == vguiPanel)
	{

		static auto doOnce = false;

		if (!doOnce)
		{
			Cvar->ConsoleColorPrintf(Color(0, 255, 0, 255), XorStr("InfamyP2C - Self Leaked by ZectixV1, and rwby\n"));
			Cvar->ConsoleColorPrintf(Color(0, 255, 0, 255), XorStr("Last Updated: %s %s\n"), __DATE__, __TIME__);
			doOnce = true;
		}

		if (Options.Visuals.ESP.Enabled && Options.Visuals.ESP.Watermark)
		{
			DrawString(Watermark, 5, 11, Color(0, 255, 0, 255), FONT_LEFT, "%s", XorStr("Infamy - Created by rwby"));
		}

		if (GetAsyncKeyState(VK_HOME))
		{
			Options.Cheat.Uninject = true;
		}

		if (Engine->IsInGame() && Engine->IsConnected() && !Engine->IsTakingScreenshot())
		{
			Global::LocalPlayer = GetLocalPlayer();
			if (Options.Visuals.ESP.Enabled)
			{
				g_pESP->getScreenSize();
				g_pESP->think(Global::LocalPlayer);
			}

			Global::CurrTime = Globals->interval_per_tick * (Global::LocalPlayer->GetTickBase() + 1);

			if (Options.Visuals.ESP.Enabled && Options.Visuals.ESP.RecoilCrosshair)
			{
				int width;
				int height;
				Engine->GetScreenSize(width, height);
				 
				auto FixedWidth = width - 5;
				auto FixedHeight = height - 5;
				auto Punch = Global::LocalPlayer->GetPunch() * 9;
				DrawString(MemeRC, FixedWidth / 2 - Punch.y, FixedHeight / 2 + Punch.x, Color(255, 255, 0, 255), false, XorStr("+"));
			}

			if (Options.Visuals.ESP.Enabled && Options.Visuals.ESP.RankESP)
			{
				using tServerRankRevealAllFn = bool(__cdecl*)(float*);
				static auto ServerRankRevealAll = reinterpret_cast<tServerRankRevealAllFn>(Memory::FindPatternIDA("client.dll", "55 8B EC 8B 0D ? ? ? ? 68"));
				static float fArray[3] = { 0,0,0 };

				ServerRankRevealAll(fArray);
			}

			if (Options.Visuals.ESP.Enabled && Options.Visuals.ESP.DrawBomb)
			{
				static itemTimer bombTimer(40.f);
				if (!Global::isBombPlanted) { //if bomb isn't planted, just reset the time to now
					bombTimer.setMaxTime(40.f);
					bombTimer.startTimer();
				}
				else { //if planted, stop resetting time and draw timer
					int screenw, screenh;
					Engine->GetScreenSize(screenw, screenh);
					auto x = 16;
					auto y = screenh - 70;
					char dettime[64];
					XorCompileTime::w_sprintf_s(dettime, 64, "C4 Explodes in: %.1f", ((int)(100 * bombTimer.getTimeRemaining()) / 100.0));
					DrawString(BombStuff, x, y, Color(0, 255, 255, 255), FONT_LEFT, dettime);
				}
			}

			if (Options.Visuals.ESP.Enabled && Options.Visuals.ESP.SniperCrosshair)
			{
				auto LocalWep = Global::LocalPlayer->GetWeapon();

				if (LocalWep->GetWeaponType() == WEPCLASS_SNIPER)
				{

					int width;
					int height;
					Engine->GetScreenSize(width, height);
					auto MidX = width / 2;
					auto MidY = height / 2;
					DrawLine(MidX - 4, MidY - 4, MidX + 4, MidY + 4, Color(0, 255, 0, 255));
					DrawLine(MidX + 4, MidY - 4, MidX - 4, MidY + 4, Color(0, 255, 0, 255));
				}
			}

			DrawRect(1, 1, 1, 1, Color(0, 0, 0, 1)); // Fix for menu not drawing without net_graph 1
			if (Options.Visuals.ESP.Enabled && Options.Visuals.ESP.Hitmarker)
			{
				auto curtime = Globals->curtime;
				auto lineSize = 8;

				if (Global::flHurtTime + 0.25f >= curtime) {
					int screenSizeX, screenCenterX;
					int screenSizeY, screenCenterY;
					Engine->GetScreenSize(screenSizeX, screenSizeY);

					screenCenterX = screenSizeX / 2;
					screenCenterY = screenSizeY / 2;

					Surface->DrawSetColor(200, 200, 200, 255);
					Surface->DrawLine(screenCenterX - lineSize, screenCenterY - lineSize, screenCenterX - (lineSize / 4), screenCenterY - (lineSize / 4));
					Surface->DrawLine(screenCenterX - lineSize, screenCenterY + lineSize, screenCenterX - (lineSize / 4), screenCenterY + (lineSize / 4));
					Surface->DrawLine(screenCenterX + lineSize, screenCenterY + lineSize, screenCenterX + (lineSize / 4), screenCenterY + (lineSize / 4));
					Surface->DrawLine(screenCenterX + lineSize, screenCenterY - lineSize, screenCenterX + (lineSize / 4), screenCenterY - (lineSize / 4));
				}
			}

			if (Options.Visuals.ESP.Enabled && Options.Visuals.ESP.DamageIndicator)
			{
				if (!Global::DamageHit.empty())
				{
					for (auto it = Global::DamageHit.begin(); it != Global::DamageHit.end();) {
						if (Global::CurrTime > it->ExpireTime) { 
							it = Global::DamageHit.erase(it);
							continue;
						}
						it->Draw();
						++it;
					}
				}
			}
		}

		static auto isDown = false;
		static auto isClicked = false;
		if (InputSystem->IsButtonDown(KEY_INSERT))
		{
			isClicked = false;
			isDown = true;
		}
		else if (!InputSystem->IsButtonDown(KEY_INSERT) && isDown)
		{
			isClicked = true;
			isDown = false;
		}
		else
		{
			isClicked = false;
			isDown = false;
		}
		if (isClicked)      
		{
			Options.Menu.Opened = !Options.Menu.Opened;

			static auto cl_mouseenable = Cvar->FindVar(XorStr("cl_mouseenable"));

			cl_mouseenable->SetValue(!Options.Menu.Opened);
		}
		if (Options.Menu.Opened)
		{
			DrawMenu();
			DrawMouse();

			//Surface->DrawTexturedPolygon(4, pVertex, true);

			//static float rainbow;
			//rainbow += 0.002f;
			//if (rainbow > 1.f) rainbow = 0.f;

			//DrawPolygon(3, mouseShape, Color::FromHSB(rainbow, 0.60f, 0.75f));
		}

		/*if (Options.Menu.PlayerList)
		{
			DrawRect(400, 230, 245, 360, Color(50, 50, 50, 255));
			DrawOutlinedRect(400 - 1, 230 - 1 , 245 + 2, 360 + 2, Color::Black()); //inner gray

			if (Engine->IsInGame() && Engine->IsConnected())
			{
				for (auto i = 0; i < ClientEntList->GetHighestEntityIndex(); i++)
				{
					auto plClient = ClientEntList->GetClientEntity(i);
					player_info_t plInfo;
					if (plClient == Global::LocalPlayer)
						continue;

					if (plClient && Engine->GetPlayerInfo(i, &plInfo))
					{
						DrawString(Verdana, 200 + 200 + 25, 200 + 30 + 220, Color(255, 255, 255), FONT_LEFT, plInfo.name);
					}

				}
			}


		}*/

	}
}
