#include "Globals.h"
#include "Config.h"
#include "Accessors.h"
#define IMGUI_DEFINE_MATH_OPERATORS

extern IMGUI_API LRESULT ImGui_ImplDX9_WndProcHandler(HWND, UINT msg, WPARAM wParam, LPARAM lParam);
bool CurKey[256] = {};
void GUI_Init(IDirect3DDevice9* pDevice);
tReset oResetScene;
tEndScene oEndScene;
cOptions Options;
#define IM_NEWLINE "\r\n"
LRESULT __stdcall Game::hkdWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	//Captures the keys states
	auto& io = ImGui::GetIO();
	switch (uMsg)
	{

	case WM_LBUTTONDOWN:
		CurKey[VK_LBUTTON] = true;
		break;
	case WM_LBUTTONUP:
		CurKey[VK_LBUTTON] = false;
		break;
	case WM_RBUTTONDOWN:
		CurKey[VK_RBUTTON] = true;
		break;
	case WM_RBUTTONUP:
		CurKey[VK_RBUTTON] = false;
		break;
	case WM_KEYDOWN:
		CurKey[wParam] = true;
		break;
	case WM_KEYUP:
		CurKey[wParam] = false;
		break;
	case WM_MOUSEMOVE:
		io.MousePos.x = static_cast<signed short>(lParam);
		io.MousePos.y = static_cast<signed short>(lParam >> 16);
		break;
	default: break;
	}
	{

	}
	if (Global::Init && Options.Menu.Opened && ImGui_ImplDX9_WndProcHandler(hWnd, uMsg, wParam, lParam))
		return true;
	return CallWindowProc(Global::oWndProc, hWnd, uMsg, wParam, lParam);
}

#pragma region Arrays
const char* ChamsType[] =
{
	"Flat",
	"Textured"
};
const char* Keys[] =
{
	"",
	"Mouse 1",
	"Mouse 2",
	"Cancel",
	"Middle Mouse",
	"Mouse 4",
	"Mouse 5",
	"",
	"Backspace",
	"Tab",
	"",
	"",
	"Clear",
	"Enter",
	"",
	"",
	"Shift",
	"Control",
	"Alt",
	"Pause",
	"Caps",
	"",
	"",
	"",
	"",
	"",
	"",
	"Escape",
	"",
	"",
	"",
	"",
	"Space",
	"Page Up",
	"Page Down",
	"End",
	"Home",
	"Left",
	"Up",
	"Right",
	"Down",
	"",
	"",
	"",
	"Print",
	"Insert",
	"Delete",
	"",
	"0",
	"1",
	"2",
	"3",
	"4",
	"5",
	"6",
	"7",
	"8",
	"9",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"A",
	"B",
	"C",
	"D",
	"E",
	"F",
	"G",
	"H",
	"I",
	"J",
	"K",
	"L",
	"M",
	"N",
	"O",
	"P",
	"Q",
	"R",
	"S",
	"T",
	"U",
	"V",
	"W",
	"X",
	"Y",
	"Z",
	"",
	"",
	"",
	"",
	"",
	"Numpad 0",
	"Numpad 1",
	"Numpad 2",
	"Numpad 3",
	"Numpad 4",
	"Numpad 5",
	"Numpad 6",
	"Numpad 7",
	"Numpad 8",
	"Numpad 9",
	"Multiply",
	"Add",
	"",
	"Subtract",
	"Decimal",
	"Divide",
	"F1",
	"F2",
	"F3",
	"F4",
	"F5",
	"F6",
	"F7",
	"F8",
	"F9",
	"F10",
	"F11",
	"F12",

};
const char* Filter[] =
{
	"None",
	"Most Damage",
	"Body Only",
	"No Arms or Head",
	"Head Only",
	"Arms Only"
};

const char* Bones[] =
{
	"Pelvis",
	"Lower Body",
	"Crotch",
	"Stomach",
	"Chest",
	"Neck",
	"Head"
};

const char* Knifes[] =
{
	"No Knife",
	"Bayonet",
	"Flip Knife",
	"Gut Knife",
	"Karambit",
	"M9 Bayonet",
	"Huntsman Knife",
	"Butterfly Knife",
	"Falchion Knife",
	"Shadow Daggers",
	"Bowie Knife"
};

const char* PercentFlash[] =
{
	"None",
	"10%",
	"20%",
	"30%",
	"40%",
	"50%",
	"60%",
	"70%",
	"80%",
	"90%",
	"100%"
};

const char* DyanmicHBoxList[] =
{
	"None",
	"Head",
	"Neck",
	"Lower Neck",
	"Pelvis",
	"Body",
	"Thorax",
	"Chest",
	"Upper Chest",
	"Right Thigh",
	"Left Thigh",
	"Right Calf",
	"Left Calf",
	"Right Foot",
	"Left Foot",
	"Right Hand",
	"Left Hand",
	"Right Upper Arm",
	"Right Forearm",
	"Left Upper Arm",
	"Left Forearm"

};

#pragma endregion 

HRESULT __stdcall Game::hkdEndScene(IDirect3DDevice9* pDevice)
{

	if (!Global::Init)
		GUI_Init(pDevice);
	else
	{

		if (Engine->IsInGame() && Engine->IsConnected())
			ImGui::GetIO().MouseDrawCursor = Options.Menu.Opened;
		else
			ImGui::GetIO().MouseDrawCursor = true;
		ImGui_ImplDX9_NewFrame();
		ImVec2 Pos;
		if (Options.Menu.Opened)
		{
			ImGui::Begin(XorStr(" "), &Options.Menu.Opened, ImVec2(996, 635), 0.9f, ImGuiWindowFlags_NoCollapse);
			{
				Pos = ImGui::GetWindowPos();
				if (ImGui::Button(XorStr("Ragebot")))
				{
					Options.Menu.Ragebot = true;
					Options.Menu.Legitbot = false;
					Options.Menu.Visuals = false;
					Options.Menu.PlayerMods = false;
					Options.Menu.Removals = false;
					Options.Menu.Trigger = false;
					Options.Menu.AAC = false;
					Options.Menu.Skins = false;
					Options.Menu.VisualColors = false;
				}
				ImGui::SameLine();
				if (ImGui::Button(XorStr("Legitbot")))
				{
					Options.Menu.Legitbot = true;
					Options.Menu.Ragebot = false;
					Options.Menu.Visuals = false;
					Options.Menu.PlayerMods = false;
					Options.Menu.Removals = false;
					Options.Menu.Trigger = false;
					Options.Menu.AAC = false;
					Options.Menu.Skins = false;
					Options.Menu.VisualColors = false;
				}
				ImGui::SameLine();
				if (ImGui::Button(XorStr("Visuals")))
				{
					Options.Menu.Visuals = true;
					Options.Menu.Legitbot = false;
					Options.Menu.Ragebot = false;
					Options.Menu.PlayerMods = false;
					Options.Menu.Removals = false;
					Options.Menu.Trigger = false;
					Options.Menu.AAC = false;
					Options.Menu.Skins = false;
					Options.Menu.VisualColors = false;
				}
				ImGui::SameLine();
				if (ImGui::Button(XorStr("PlayerMods")))
				{
					Options.Menu.PlayerMods = true;
					Options.Menu.Visuals = false;
					Options.Menu.Legitbot = false;
					Options.Menu.Ragebot = false;
					Options.Menu.Removals = false;
					Options.Menu.Trigger = false;
					Options.Menu.AAC = false;
					Options.Menu.Skins = false;
					Options.Menu.VisualColors = false;
				}
				ImGui::SameLine();
				if (ImGui::Button(XorStr("Removals")))
				{
					Options.Menu.Removals = true;
					Options.Menu.Visuals = false;
					Options.Menu.Legitbot = false;
					Options.Menu.Ragebot = false;
					Options.Menu.PlayerMods = false;
					Options.Menu.Trigger = false;
					Options.Menu.AAC = false;
					Options.Menu.Skins = false;
					Options.Menu.VisualColors = false;
				}
				ImGui::SameLine();
				if (ImGui::Button(XorStr("Triggerbot")))
				{
					Options.Menu.Trigger = true;
					Options.Menu.Visuals = false;
					Options.Menu.Legitbot = false;
					Options.Menu.Ragebot = false;
					Options.Menu.PlayerMods = false;
					Options.Menu.VisualColors = false;
					Options.Menu.AAC = false;
					Options.Menu.Skins = false;
					Options.Menu.Removals = false;
				}
				ImGui::SameLine();
				if (ImGui::Button(XorStr("Colors")))
				{
					Options.Menu.VisualColors = true;
					Options.Menu.Visuals = false;
					Options.Menu.Legitbot = false;
					Options.Menu.Ragebot = false;
					Options.Menu.PlayerMods = false;
					Options.Menu.Trigger = false;
					Options.Menu.AAC = false;
					Options.Menu.Skins = false;
					Options.Menu.Removals = false;
				}
				ImGui::SameLine();
				if (ImGui::Button(XorStr("AC")))
				{
					Options.Menu.AAC = true;
					Options.Menu.Visuals = false;
					Options.Menu.Legitbot = false;
					Options.Menu.Ragebot = false;
					Options.Menu.PlayerMods = false;
					Options.Menu.Trigger = false;
					Options.Menu.VisualColors = false;
					Options.Menu.Skins = false;
					Options.Menu.Removals = false;
				}
				ImGui::SameLine();
				if (ImGui::Button(XorStr("Skins")))
				{
					Options.Menu.Skins = true;
					Options.Menu.Visuals = false;
					Options.Menu.Legitbot = false;
					Options.Menu.Ragebot = false;
					Options.Menu.Trigger = false;
					Options.Menu.VisualColors = false;
					Options.Menu.AAC = false;
					Options.Menu.Removals = false;
				}
				ImGui::SameLine();
				ImGui::Text(XorStr("|"));
				ImGui::SameLine();
				if (ImGui::Button(XorStr("LOAD"))) ConSys->LoadConfig();
				ImGui::SameLine();
				if (ImGui::Button(XorStr("SAVE"))) ConSys->SaveConfig();
				ImGui::SameLine();
				if (ImGui::Button(XorStr("Weapon-Configs"))) Options.Menu.WeaponConfigs ^= 1;
				ImGui::SameLine();
				ImGui::PushItemWidth(-1);
				ImGui::Combo(XorStr("Config"), &Options.Config.Current, XorStr("Default\0Legit\0Rage\0League\0"));
				ImGui::PopItemWidth();
				ImGui::Separator();

				if (Options.Menu.Ragebot)
				{
					ImGui::PushItemWidth(200);
					//ImGui::Checkbox(XorStr("Enabled"), &Options.Rage.Aimbot.Enabled);
					ImGui::Combo(XorStr("HitBox"), &Options.Rage.Aimbot.Hitbox, Bones, ARRAYSIZE(Bones));
					ImGui::Combo(XorStr("AutoWall"), &Options.Rage.AutoWall.AutowallType, XorStr("Low-End\0High-End\0"));
					ImGui::Combo(XorStr("HitScans"), &Options.Rage.Aimbot.HitScans, XorStr("Aim At Bones\0HitScan-MultiPoint\0HitScan Hitboxs\0Hitscan-Extreme\0Custom-Hitscans\0"));
					ImGui::Combo(XorStr("Targeting"), &Options.Rage.Aimbot.Targeting, XorStr("FOV\0Health\0Distance\0Threat\0Visible Bones\0Damage\0"));
					ImGui::Combo(XorStr("StopType"), &Options.Rage.Aimbot.StopType, XorStr("None\0Stop\0StopCrouch\0Full-Stop\0Full-StopCrouch\0"));
					ImGui::Checkbox(XorStr("Auto-Shoot"), &Options.Rage.Aimbot.AutoShoot);
					ImGui::Checkbox(XorStr("Auto-Scope"), &Options.Rage.Aimbot.AutoScope);
					ImGui::Checkbox(XorStr("Enemy Only"), &Options.Rage.Aimbot.EnemyOnly);
					ImGui::Checkbox(XorStr("SilentAim"), &Options.Rage.Aimbot.SilentAim);
					ImGui::Checkbox(XorStr("pSilent(Turn off Wepconfigs)"), &Options.Legit.Aimbot.PerfectSilentAim);
					ImGui::Checkbox(XorStr("MM No Spread"), &Options.Rage.Aimbot.PsuedoSpread);
					ImGui::SliderFloat(XorStr("Min-Damage"), &Options.Rage.AutoWall.MinDamage, 1.f, 100.f, "%.1f");
					ImGui::Text(XorStr("Aim-Smart"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Aim-Smart"), &Options.Rage.Aimbot.AimSmart);
					ImGui::InputInt(XorStr("Smart Shots"), &Options.Rage.Aimbot.iSmartShots);
					ImGui::Text(XorStr("Hitchance"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Hitchance"), &Options.Rage.Aimbot.bHitchance);
					ImGui::Checkbox(XorStr("Hitchance Snipers"), &Options.Rage.Aimbot.bHitchanceSnipers);
					ImGui::SliderFloat(XorStr("HitChance"), &Options.Rage.Aimbot.Hitchance, 1.f, 100.f, "%.1f");
					ImGui::Text(XorStr("AA"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Anti-Aims"), &Options.Rage.AntiAim.Enabled);
					ImGui::Combo(XorStr("Pitch"), &Options.Rage.AntiAim.Pitch, XorStr("None\0Emotion\0"));
					ImGui::Combo(XorStr("Yaw"), &Options.Rage.AntiAim.Yaw, XorStr("None\0Jitter\0Jitter-Synced\0Element\0Backwards\0Fake-Static\0Fake2\0Fake3\0Fake4\0Lisp-Backwards\0Lisp-Flipped\0Lisp-Jitter\0Lisp-FakeJitter\0"));
					if (ImGui::Button(XorStr("PlayerList"))) Options.Menu.PlayerList ^= 1;
					if (ImGui::Button(XorStr("Custom Hitscans"))) Options.Menu.HitScans ^= 1;
					ImGui::PopItemWidth();


				}


				if (Options.Menu.PlayerList)
				{
					static const char* team[4] = { "None","Spec","T","CT" };
					static const char* IsSpec[2] = { "No","Yes" };
					//ImGui::SetNextWindowSize(ImVec2(625, 400), ImGuiSetCond_Appearing);
					if (ImGui::Begin(XorStr("Player List"), &Options.Menu.PlayerList))
					{
						ImGui::Checkbox(XorStr("AntiAntiAim"), &Options.Rage.Aimbot.AntiAntiAim);
						ImGui::Checkbox(XorStr("More Info"), &Options.Menu.pList.MoreInfo);
						ImGui::SameLine();
						ImGui::Checkbox(XorStr("Hide Enemy's"), &Options.Rage.Aimbot.AAA.Enemyonly);
						///ImGui::Combo(XorStr("AAA Type"), &Options.Rage.Aimbot.AAA.ResolverType, XorStr("None\0Dynamic\0"));
						if (Options.Menu.pList.MoreInfo && !Options.Rage.Aimbot.AAA.Enemyonly)
							ImGui::Columns(11, "PlayerList");
						else if (Options.Menu.pList.MoreInfo && Options.Rage.Aimbot.AAA.Enemyonly)
							ImGui::Columns(10, "PlayerList");
						else if (!Options.Menu.pList.MoreInfo && Options.Rage.Aimbot.AAA.Enemyonly)
							ImGui::Columns(6, "PlayerList");
						else if (!Options.Menu.pList.MoreInfo && !Options.Rage.Aimbot.AAA.Enemyonly)
							ImGui::Columns(7, "PlayerList");
						ImGui::Separator();
						ImGui::Text(XorStr("Name"));                 ImGui::NextColumn();
						if (!Options.Rage.Aimbot.AAA.Enemyonly)
						{
							ImGui::Text(XorStr("Team"));                 ImGui::NextColumn();
						}
						if (Options.Menu.pList.MoreInfo)
						{
							ImGui::Text(XorStr("Index"));                ImGui::NextColumn();
							ImGui::Text(XorStr("Spectating Player"));    ImGui::NextColumn();
							ImGui::Text(XorStr("Pitch"));                ImGui::NextColumn();
							ImGui::Text(XorStr("Yaw"));                  ImGui::NextColumn();
						}
						ImGui::Text(XorStr("Custom Yaw Resolve"));   ImGui::NextColumn();
						ImGui::Text(XorStr("Custom Pitch Resolve")); ImGui::NextColumn();
						ImGui::Text(XorStr("Bone Correction")); ImGui::NextColumn();
						ImGui::Text(XorStr("Anti-Aimbot Correction")); ImGui::NextColumn();
						ImGui::Text(XorStr("Disable Head")); ImGui::NextColumn();
						ImGui::Separator();
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
									if (Options.Rage.Aimbot.AAA.Enemyonly)
									{
										if (plClient->GetTeam() == Global::LocalPlayer->GetTeam())
											continue;
										if (plClient->GetTeam() == 1 || plClient->GetTeam() == 0)
											continue;
									}
									ImGui::Text(plInfo.name);
									ImGui::NextColumn();
									bool bIsSpec = 0;
									DWORD hSpecTarget;
									auto iTeamNum = plClient->GetTeam();
									if ((!Options.Rage.Aimbot.AAA.Enemyonly))
									{
										if (iTeamNum == 1)
										{
											hSpecTarget = *reinterpret_cast<DWORD*>(reinterpret_cast<DWORD>(plClient) + offsets.m_hObserverTarget);
											if (hSpecTarget)
												bIsSpec = ClientEntList->GetClientEntityFromHandle(hSpecTarget) == Global::LocalPlayer;
										}
									}
									auto oAngle = Options.Rage.Aimbot.AAA.oAngle[i];
									if (iTeamNum > 3)
										iTeamNum = 0;


									if (!Options.Rage.Aimbot.AAA.Enemyonly)
									{
										ImGui::Text(team[iTeamNum]);
										ImGui::NextColumn();
									}
									if (Options.Menu.pList.MoreInfo)
									{
										ImGui::Text("%i", i);                     ImGui::NextColumn();
										ImGui::Text(IsSpec[bIsSpec]);             ImGui::NextColumn();
										ImGui::Text("%.3f", oAngle.x);            ImGui::NextColumn();
										ImGui::Text("%.3f", oAngle.y);            ImGui::NextColumn();
									}// these only display if mor info
									char Yaw[255] = ""; char Pitch[255] = ""; char Bone[255] = ""; char Lisp[255] = ""; char Head[255] = "";
									XorCompileTime::w_sprintf(Yaw, "%s %s", plInfo.name, "Yaw");
									ImGui::InputFloat(Yaw, &Options.Rage.Aimbot.AAA.CAngle[i].y);
									ImGui::NextColumn();//yaw
									XorCompileTime::w_sprintf(Pitch, "%s %s", plInfo.name, "Pitch");
									ImGui::InputFloat(Pitch, &Options.Rage.Aimbot.AAA.CAngle[i].x);
									ImGui::NextColumn();//pitch
									XorCompileTime::w_sprintf(Bone, "%s %s", plInfo.name, "Bone");
									ImGui::Combo(Bone, &Options.Rage.Aimbot.AAA.bone[i], XorStr("None\0Pelvis\0Lower Body\0Crotch\0Stomach\0Chest\0Neck\0Head\0"));
									ImGui::NextColumn();//bone
									XorCompileTime::w_sprintf(Lisp, "%s %s", plInfo.name, "AAC");
									ImGui::Combo(Lisp, &Options.Rage.Aimbot.AAA.Lisp[i], XorStr("None\0Level 1\0Level 2\0Level 3\0Level 4\0Level 5\0"));
									ImGui::NextColumn();//Lisp
									XorCompileTime::w_sprintf(Head, "%s %s", plInfo.name, "Head");
									ImGui::Checkbox(Head, &Options.Rage.Aimbot.AAA.bDisableHead[i]);
									ImGui::NextColumn();//HEad


								}
							}
						}
						ImGui::Columns(1);
						ImGui::Separator();
						ImGui::Text(XorStr("Anti-Aimbot Level 1 - Fix Pitch"));
						ImGui::Text(XorStr("Anti-Aimbot Level 2 - Fix Jitter / fastspin and Pitch"));
						ImGui::Text(XorStr("Anti-Aimbot Level 3 - Fix Jitter / fastspin and Jitter Pitch"));
						ImGui::Text(XorStr("Anti-Aimbot Level 4 - Fix Lisp and Pitch"));
						ImGui::Text(XorStr("Anti-Aimbot Level 5 - Hail Marry"));

					}
					ImGui::End();
				}

				if (Options.Menu.HitScans)
				{
					ImGui::Begin(XorStr("CHitscans"), &Options.Menu.HitScans, ImVec2(400, 400));
					ImGui::Text(XorStr("HitScan Options"));
					ImGui::Separator();
					ImGui::SliderInt(XorStr("MultiPoint"), &Options.Rage.Aimbot.Hitscan.Point, 0, 9);
					ImGui::BeginChild(XorStr("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 20));
					{
						ImGui::Selectable(XorStr(" Head"), &Options.Rage.Aimbot.Hitscan.Head);
						ImGui::Selectable(XorStr(" Neck"), &Options.Rage.Aimbot.Hitscan.Neck);
						ImGui::Selectable(XorStr(" Lower Neck"), &Options.Rage.Aimbot.Hitscan.LowerNeck);
						ImGui::Selectable(XorStr(" Pelvis"), &Options.Rage.Aimbot.Hitscan.Pelvis);
						ImGui::Selectable(XorStr(" Body"), &Options.Rage.Aimbot.Hitscan.Body);
						ImGui::Selectable(XorStr(" Thorax"), &Options.Rage.Aimbot.Hitscan.Thorax);
						ImGui::Selectable(XorStr(" Chest"), &Options.Rage.Aimbot.Hitscan.Chest);
						ImGui::Selectable(XorStr(" Upper Chest"), &Options.Rage.Aimbot.Hitscan.UpperChest);
						ImGui::Selectable(XorStr(" Right Thigh"), &Options.Rage.Aimbot.Hitscan.RightThigh);
						ImGui::Selectable(XorStr(" Left Thigh"), &Options.Rage.Aimbot.Hitscan.LeftThigh);
						ImGui::Selectable(XorStr(" Right Calf"), &Options.Rage.Aimbot.Hitscan.RightCalf);
						ImGui::Selectable(XorStr(" Left Calf"), &Options.Rage.Aimbot.Hitscan.LeftCalf);
						ImGui::Selectable(XorStr(" Right Foot"), &Options.Rage.Aimbot.Hitscan.RightFoot);
						ImGui::Selectable(XorStr(" Left Foot"), &Options.Rage.Aimbot.Hitscan.LeftFoot);
						ImGui::Selectable(XorStr(" Right Hand"), &Options.Rage.Aimbot.Hitscan.RightHand);
						ImGui::Selectable(XorStr(" Left Hand"), &Options.Rage.Aimbot.Hitscan.LeftHand);
						ImGui::Selectable(XorStr(" Right Upper Arm"), &Options.Rage.Aimbot.Hitscan.RightUpperArm);
						ImGui::Selectable(XorStr(" Right Forearm"), &Options.Rage.Aimbot.Hitscan.RightForeArm);
						ImGui::Selectable(XorStr(" Left Upper Arm"), &Options.Rage.Aimbot.Hitscan.LeftUpperArm);
						ImGui::Selectable(XorStr(" Left Forearm"), &Options.Rage.Aimbot.Hitscan.LeftForeArm);
						ImGui::Selectable(XorStr(" Max"), &Options.Rage.Aimbot.Hitscan.Max);
					}
					ImGui::EndChild();
					ImGui::End();
				}

				if (Options.Menu.Legitbot)
				{
					auto lCheck = Options.AntiCheat.League;
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("Enabled"), &Options.Legit.Aimbot.Enabled);
					ImGui::Checkbox(XorStr("Recoil Control System"), &Options.Legit.Aimbot.RCS);

					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("SilentAim"), &Options.Legit.Aimbot.SilentAim);
						ImGui::SliderFloat(XorStr("FOV"), &Options.Legit.Aimbot.Fov, 0.f, 180.f, "%.1f");
					}
					if (lCheck)
					{
						ImGui::SliderInt(XorStr("FOV"), &Options.Legit.Aimbot.LFOV, 1, 180);
						ImGui::SliderInt(XorStr("Smooth"), &Options.Legit.Aimbot.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("Multiply Smooth"), &Options.Legit.Aimbot.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("FOV Boost"), &Options.Legit.Aimbot.FOVBOOST, 1, 10);
						ImGui::Combo(XorStr("Aim Key"), &Options.Legit.Aimbot.LKey, Keys, ARRAYSIZE(Keys));
						ImGui::Checkbox(XorStr("Visible Only"), &Options.Legit.Aimbot.VisibleOnly);
						ImGui::Combo(XorStr("Bone"), &Options.Legit.Aimbot.Bone, Bones, ARRAYSIZE(Bones));
						ImGui::Checkbox(XorStr("Enemy Only"), &Options.Legit.Aimbot.EnemyOnly);
						ImGui::Text(XorStr("Dynamic Hitbox Options ( Disables RCS )"));
						ImGui::Separator();
						ImGui::Checkbox(XorStr("Enable"), &Options.Legit.Aimbot.DynamicHBox);
						if (Options.Legit.Aimbot.DynamicHBox)
						{
							ImGui::BeginChild(XorStr("Filter"), ImVec2(ImGui::GetWindowContentRegionWidth() * 0.5f, 19 * 19));
							{
								ImGui::Selectable(XorStr(" Head"), &Options.Legit.Aimbot.Hitscan.Head);
								ImGui::Selectable(XorStr(" Neck"), &Options.Legit.Aimbot.Hitscan.Neck);
								ImGui::Selectable(XorStr(" Lower Neck"), &Options.Legit.Aimbot.Hitscan.LowerNeck);
								ImGui::Selectable(XorStr(" Pelvis"), &Options.Legit.Aimbot.Hitscan.Pelvis);
								ImGui::Selectable(XorStr(" Body"), &Options.Legit.Aimbot.Hitscan.Body);
								ImGui::Selectable(XorStr(" Thorax"), &Options.Legit.Aimbot.Hitscan.Thorax);
								ImGui::Selectable(XorStr(" Chest"), &Options.Legit.Aimbot.Hitscan.Chest);
								ImGui::Selectable(XorStr(" Upper Chest"), &Options.Legit.Aimbot.Hitscan.UpperChest);
								ImGui::Selectable(XorStr(" Right Thigh"), &Options.Legit.Aimbot.Hitscan.RightThigh);
								ImGui::Selectable(XorStr(" Left Thigh"), &Options.Legit.Aimbot.Hitscan.LeftThigh);
								ImGui::Selectable(XorStr(" Right Calf"), &Options.Legit.Aimbot.Hitscan.RightCalf);
								ImGui::Selectable(XorStr(" Left Calf"), &Options.Legit.Aimbot.Hitscan.LeftCalf);
								ImGui::Selectable(XorStr(" Right Foot"), &Options.Legit.Aimbot.Hitscan.RightFoot);
								ImGui::Selectable(XorStr(" Left Foot"), &Options.Legit.Aimbot.Hitscan.LeftFoot);
								ImGui::Selectable(XorStr(" Right Hand"), &Options.Legit.Aimbot.Hitscan.RightHand);
								ImGui::Selectable(XorStr(" Left Hand"), &Options.Legit.Aimbot.Hitscan.LeftHand);
								ImGui::Selectable(XorStr(" Right Upper Arm"), &Options.Legit.Aimbot.Hitscan.RightUpperArm);
								ImGui::Selectable(XorStr(" Right Forearm"), &Options.Legit.Aimbot.Hitscan.RightForeArm);
								ImGui::Selectable(XorStr(" Left Upper Arm"), &Options.Legit.Aimbot.Hitscan.LeftUpperArm);
								ImGui::Selectable(XorStr(" Left Forearm"), &Options.Legit.Aimbot.Hitscan.LeftForeArm);
							}
							ImGui::EndChild();
						}
						ImGui::Text(XorStr("Angle Randomization"));
						ImGui::Separator();
						ImGui::Checkbox(XorStr("Randomize Angles"), &Options.Legit.Aimbot.RandomizeAngles);
						ImGui::SliderFloat(XorStr("Randomize Amt"), &Options.Legit.Aimbot.AngleValue, 0.f, 20.f, "%.1f");
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("Smooth X"), &Options.Legit.Aimbot.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Smooth Y"), &Options.Legit.Aimbot.Smooth[1], 1.f, 100.f, "%.1f");
						ImGui::Combo(XorStr("Bone"), &Options.Legit.Aimbot.Bone, Bones, ARRAYSIZE(Bones));
						ImGui::Checkbox(XorStr("Enemy Only"), &Options.Legit.Aimbot.EnemyOnly);
					}
				    ImGui::PopItemWidth();
				}

				if (Options.Menu.Visuals)
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("Enabled"), &Options.Visuals.ESP.Enabled);
					ImGui::Checkbox(XorStr("Enemy-Only"), &Options.Visuals.ESP.EnemyOnly);
					ImGui::Text(XorStr("Main Options"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Box"), &Options.Visuals.ESP.Box);
					ImGui::Combo(XorStr("Health"), &Options.Visuals.ESP.Health, XorStr("None\0Basic\0Bar\0"));
					ImGui::Checkbox(XorStr("Name"), &Options.Visuals.ESP.Name);
					ImGui::Checkbox(XorStr("Weapon"), &Options.Visuals.ESP.Weapon);
					ImGui::Checkbox(XorStr("Distance"), &Options.Visuals.ESP.Distance);
					ImGui::Checkbox(XorStr("Bone"), &Options.Visuals.ESP.Bone);
					ImGui::Checkbox(XorStr("Flashed"), &Options.Visuals.ESP.Flashed);
					ImGui::Checkbox(XorStr("Ammo"), &Options.Visuals.ESP.Ammo);
					ImGui::Checkbox(XorStr("Callout"), &Options.Visuals.ESP.Callout);
					ImGui::Checkbox(XorStr("World"), &Options.Visuals.ESP.World);
					ImGui::Text(XorStr("C4 Options"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("C4 Timer"), &Options.Visuals.ESP.DrawBomb);
					ImGui::Checkbox(XorStr("C4 Defuse Timer"), &Options.Visuals.ESP.DrawDefuser);
					ImGui::Text(XorStr("Misc Options"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Aim Point"), &Options.Visuals.ESP.AimPoint);
					ImGui::Checkbox(XorStr("Barrel"), &Options.Visuals.ESP.Barrel);
					ImGui::Checkbox(XorStr("Hitmarker"), &Options.Visuals.ESP.Hitmarker);
					ImGui::Checkbox(XorStr("Damage Indicator"), &Options.Visuals.ESP.DamageIndicator);
					ImGui::Checkbox(XorStr("Recoil Crosshair"), &Options.Visuals.ESP.RecoilCrosshair);
					ImGui::Checkbox(XorStr("Auto Accept"), &Options.Visuals.ESP.AutoAccept);
					ImGui::Checkbox(XorStr("Rank"), &Options.Visuals.ESP.RankESP);
					ImGui::Checkbox(XorStr("No Name"), &Options.Visuals.ESP.NoName);
					ImGui::Checkbox(XorStr("Watermark"), &Options.Visuals.ESP.Watermark);
					ImGui::Checkbox(XorStr("Sniper Crosshair"), &Options.Visuals.ESP.SniperCrosshair);
					ImGui::SliderInt(XorStr("FOV"), &Options.Visuals.ESP.FOV, 0, 40);
					ImGui::Combo(XorStr("Glow"), &Options.Visuals.ESP.DrawGlowS, XorStr("None\0Spectator\0User-Controlled\0"));
					ImGui::Text(XorStr("Chams"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Chams"), &Options.Visuals.Chams.Enabled);
					ImGui::Combo(XorStr("Type"), &Options.Visuals.Chams.Mode, ChamsType, ARRAYSIZE(ChamsType));
					ImGui::Checkbox(XorStr("XQZ"), &Options.Visuals.Chams.XQZ);
					ImGui::Text(XorStr("Glow Lights"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Lights"), &Options.Visuals.ESP.DLight);
					ImGui::SliderInt(XorStr("Multiply Light"), &Options.Visuals.ESP.DLightRadius, 1, 10);
					ImGui::PopItemWidth();
				}

				if (Options.Menu.PlayerMods)
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("Bunnyhop"), &Options.PlayerMods.bhop.Enabled);
					ImGui::Checkbox(XorStr("AutoStrafe"), &Options.PlayerMods.AutoStrafe.Enabled);
					ImGui::Checkbox(XorStr("Rage AutoStrafe"), &Options.PlayerMods.AutoStrafe.REnabled);
					ImGui::Text(XorStr("Command Forcing"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("AirStuck"), &Options.PlayerMods.AirStuck.Enabled);
					ImGui::Combo(XorStr("Key"), &Options.PlayerMods.AirStuck.Key, Keys, ARRAYSIZE(Keys));
					ImGui::Text(XorStr("FakeLag"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Fakelag"), &Options.PlayerMods.FakeLag.Enabled);
					ImGui::InputInt(XorStr("Send"), &Options.PlayerMods.FakeLag.Send);
					ImGui::InputInt(XorStr("Choke"), &Options.PlayerMods.FakeLag.Choke);
					ImGui::Text(XorStr("Player"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Auto Pistol"), &Options.PlayerMods.AutoPistol.Enabled);
					ImGui::Text(XorStr("Clan Tags"));
					ImGui::Separator();
					ImGui::Combo(XorStr("Clan Tags"), &Options.PlayerMods.ClanTags.Enabled, XorStr("None\0Infamy\0Cloud9\0Valve-Employee\0Valve-Employee-Slow\0Custom\0"));
					//if (Options.PlayerMods.ClanTags.Enabled == 5)
				//	{
				//		//ImGui::InputText(XorStr("Custom Tag"), Options.PlayerMods.ClanTags.buf, 64);
					//}
					ImGui::Text(XorStr("Custom No Flash"));
					ImGui::Separator();
					ImGui::Combo(XorStr("Flash Amt"), &Options.PlayerMods.Flash, PercentFlash, ARRAYSIZE(PercentFlash));
					ImGui::Text(XorStr("Kill Message"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Enabled"), &Options.PlayerMods.KillMsg.Enabled);
					if (Options.PlayerMods.KillMsg.Enabled)
					{
						ImGui::InputText(XorStr("Kill Msg"), Options.PlayerMods.KillMsg.buf, 64);
					}
					ImGui::Combo(XorStr("PANIC Key"), &Options.PlayerMods.PanicKey, Keys, ARRAYSIZE(Keys));

					ImGui::PopItemWidth();
				}

				if (Options.Menu.Removals)
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("No Hands"), &Options.Visuals.Removals.Hands);
					ImGui::Checkbox(XorStr("WireFrame Hands"), &Options.Visuals.Removals.WireframeHands);
					ImGui::Checkbox(XorStr("No Weapon"), &Options.Visuals.Removals.Weapon);
					ImGui::Checkbox(XorStr("WireFrame Weapons"), &Options.Visuals.Removals.WireframeWep);
					ImGui::Checkbox(XorStr("No Vis Recoil"), &Options.Visuals.Removals.VisualRecoil);
					ImGui::Checkbox(XorStr("No Recoil"), &Options.Visuals.Removals.Recoil);
					ImGui::Checkbox(XorStr("No Flash"), &Options.Visuals.Removals.Flash);
					ImGui::PopItemWidth();
				}

				if (Options.Menu.Trigger)
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("Trigger"), &Options.Legit.Trigger.Enabled);
					ImGui::Combo(XorStr("Key"), &Options.Legit.Trigger.Key, Keys, ARRAYSIZE(Keys));
					ImGui::Checkbox(XorStr("EnemyOnly"), &Options.Legit.Trigger.TriggerFriends);
					ImGui::Combo(XorStr("Filter"), &Options.Legit.Trigger.Filter, Filter, ARRAYSIZE(Filter));
					ImGui::InputInt(XorStr("Delay"), &Options.Legit.Trigger.Delay);
					ImGui::Text(XorStr("Hitchance"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Hitchance"), &Options.Legit.Trigger.HitChance);
					ImGui::SliderFloat(XorStr("HitChance"), &Options.Legit.Trigger.HitChanceAmount, 1.f, 100.f, "%.1f");
					ImGui::PopItemWidth();
				}

				//if (Options.Menu.StyleEditor)
				//{
					//ImGui::Begin("Style Editor", &Options.Menu.StyleEditor); ImGui::ShowStyleEditor(); ImGui::End();
				//	}

				if (Options.Menu.VisualColors)
				{
					ImGui::PushItemWidth(200);
					ImGui::Text(XorStr("Cham Color"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Show Chams Enemy Color"), &Options.Visuals.VisualsColors.ShowChams1);
					if (Options.Visuals.VisualsColors.ShowChams1)
					{
						Options.Visuals.VisualsColors.ShowChams7 = false;
						Options.Visuals.VisualsColors.ShowChams2 = false;
						Options.Visuals.VisualsColors.ShowChams3 = false;
						Options.Visuals.VisualsColors.ShowChams4 = false;
						ColorPicker4(Options.Visuals.Chams.EnemyColor, false);
					}
					ImGui::Checkbox(XorStr("Show Chams Enemy NonVis"), &Options.Visuals.VisualsColors.ShowChams2);
					if (Options.Visuals.VisualsColors.ShowChams2)
					{
						Options.Visuals.VisualsColors.ShowChams7 = false;
						Options.Visuals.VisualsColors.ShowChams3 = false;
						Options.Visuals.VisualsColors.ShowChams1 = false;
						Options.Visuals.VisualsColors.ShowChams4 = false;
						ColorPicker4(Options.Visuals.Chams.EnemyColorWall, false);
					}
					ImGui::Text(XorStr("ESP Color"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Show Visible"), &Options.Visuals.VisualsColors.ShowChams3);
					if (Options.Visuals.VisualsColors.ShowChams3)
					{
						Options.Visuals.VisualsColors.ShowChams2 = false;
						Options.Visuals.VisualsColors.ShowChams4 = false;
						Options.Visuals.VisualsColors.ShowChams1 = false;
						Options.Visuals.VisualsColors.ShowChams7 = false;
						ColorPicker4(Options.Visuals.ESP.VisibleColor, false);
					}
					ImGui::Checkbox(XorStr("Show Non Visible"), &Options.Visuals.VisualsColors.ShowChams4);
					if (Options.Visuals.VisualsColors.ShowChams4)
					{
						Options.Visuals.VisualsColors.ShowChams3 = false;
						Options.Visuals.VisualsColors.ShowChams2 = false;
						Options.Visuals.VisualsColors.ShowChams1 = false;
						Options.Visuals.VisualsColors.ShowChams7 = false;
						ColorPicker4(Options.Visuals.ESP.NonVisibleColor, false);
					}
					ImGui::Text(XorStr("Glow Color"));
					ImGui::Separator();
					ImGui::Checkbox(XorStr("Show Glow Color"), &Options.Visuals.VisualsColors.ShowChams7);
					if (Options.Visuals.VisualsColors.ShowChams7)
					{
						Options.Visuals.VisualsColors.ShowChams3 = false;
						Options.Visuals.VisualsColors.ShowChams2 = false;
						Options.Visuals.VisualsColors.ShowChams1 = false;
						Options.Visuals.VisualsColors.ShowChams4 = false;
						ColorPicker4(Options.Visuals.Glow.TeamColor, false);
					}
					ImGui::PopItemWidth();
				}

				if (Options.Menu.AAC)
				{
					ImGui::Checkbox(XorStr("Match-Making(UNTRUSTED)"), &Options.AntiCheat.MM);
					ImGui::Checkbox(XorStr("Source Mod Anti-Cheat(SMAC)"), &Options.AntiCheat.SMAC);
					ImGui::Checkbox(XorStr("Valve Anti-Cheat(VAC)"), &Options.AntiCheat.VAC);
					ImGui::Checkbox(XorStr("League Anti-Cheats (LAC)"), &Options.AntiCheat.League);
				}

				if (Options.Menu.Skins)
				{
					// Still WIP - 9/17/16
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("Enabled"), &Options.Skins.Enabled);
					ImGui::Checkbox(XorStr("Enable Name Changer"), &Options.Skins.NEnabled);
					ImGui::Checkbox(XorStr("Enable Left Hand Knife"), &Options.Skins.LeftHandKnife);
					ImGui::Separator();
					if (Engine->IsInGame() && Engine->IsConnected() && Global::LocalPlayer->GetHealth() > 0)
					{
						auto pWeapon = Global::LocalPlayer->GetWeapon();
						switch (pWeapon->GetWeaponID())
						{
						case WEAPON_DEAGLE:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.deagle);
							break;
						case WEAPON_CZ75A:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.cz75);
							break;
						case WEAPON_HKP2000:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.p2000);
							break;
						case WEAPON_ELITE:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.elites);
							break;
						case WEAPON_P250:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.p250);
							break;
						case WEAPON_FIVESEVEN:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.fiveseven);
							break;
						case WEAPON_TEC9:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.tec9);
							break;
						case WEAPON_GLOCK:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.glock);
							break;
						case WEAPON_AUG:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.aug);
							break;
						case WEAPON_GALILAR:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.galil);
							break;
						case WEAPON_USP_SILENCER:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.usps);
							break;
						case WEAPON_AK47:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.ak47);
							break;
						case WEAPON_FAMAS:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.famas);
							break;
						case WEAPON_M4A1:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.m4a4);
							break;
						case WEAPON_M4A1_SILENCER:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.m4a1s);
							break;
						case WEAPON_BIZON:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.bizon);
							break;
						case WEAPON_MAC10:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.mac10);
							break;
						case WEAPON_MP7:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.mp7);
							break;
						case WEAPON_MP9:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.mp9);
							break;
						case WEAPON_P90:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.p90);
							break;
						case WEAPON_M249:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.m249);
							break;
						case WEAPON_UMP45:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.ump45);
							break;
						case WEAPON_NEGEV:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.negev);
							break;
						case WEAPON_MAG7:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.mag7);
							break;
						case WEAPON_NOVA:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.nova);
							break;
						case WEAPON_SAWEDOFF:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.sawedoff);
							break;
						case WEAPON_XM1014:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.xm1014);
							break;
						case WEAPON_SCAR20:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.scar20);
							break;
						case WEAPON_AWP:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.awp);
							break;
						case WEAPON_SSG08:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.ssg08);
							break;
						case WEAPON_G3SG1:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.g3sg1);
							break;
						case WEAPON_REVOLVER:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.magnum);
							break;
						case WEAPON_SG556:
							ImGui::InputInt(XorStr("PaintKit"), &Options.Skins.sg556);
							break;
						}
						ImGui::InputInt(XorStr("StatTrak Amount"), &Options.Skins.StatTrak);
						ImGui::Separator();
						ImGui::Combo(XorStr("Select a knife"), &Options.Skins.KnifeSelect, Knifes, ARRAYSIZE(Knifes));
						switch (Options.Skins.KnifeSelect)
						{
						case 1:
							ImGui::InputInt(XorStr("Bayonet Paint"), &Options.Skins.KnifeIDb);
							break;
						case 2:
							ImGui::InputInt(XorStr("Flip Knife Paint"), &Options.Skins.KnifeIDf);
							break;
						case 3:
							ImGui::InputInt(XorStr("Gut Knife Paint"), &Options.Skins.KnifeIDg);
							break;
						case 4:
							ImGui::InputInt(XorStr("Karambit Paint"), &Options.Skins.KnifeIDk);
							break;
						case 5:
							ImGui::InputInt(XorStr("M9 Bayonet Paint"), &Options.Skins.KnifeIDm);
							break;
						case 6:
							ImGui::InputInt(XorStr("Huntsman Knife Paint"), &Options.Skins.KnifeIDh);
							break;
						case 7:
							ImGui::InputInt(XorStr("Butterfly Knife Paint"), &Options.Skins.KnifeIDb);
							break;
						case 8:
							ImGui::InputInt(XorStr("Falchion Knife Paint"), &Options.Skins.KnifeIDf);
							break;
						case 9:
							ImGui::InputInt(XorStr("Shadow Daggers Paint"), &Options.Skins.KnifeIDdag);
							break;
						case 10:
							ImGui::InputInt(XorStr("Bowie Knife Paint"), &Options.Skins.KnifeIDbow);
							break;
						}
						ImGui::InputText(XorStr("KnifeName"), Options.Skins.buf, 64);
						ImGui::Separator();
						ImGui::Checkbox(XorStr("Skin Color 0"), &Options.Skins.Color.Custom0);
						if (Options.Skins.Color.Custom0)
						{
							ColorPicker4(Options.Skins.Color.color0, false);
						}
						ImGui::Checkbox(XorStr("Skin Color 1"), &Options.Skins.Color.Custom1);
						if (Options.Skins.Color.Custom1)
						{
							ColorPicker4(Options.Skins.Color.color1, false);
						}
						ImGui::Checkbox(XorStr("Skin Color 2"), &Options.Skins.Color.Custom2);
						if (Options.Skins.Color.Custom2)
						{
							ColorPicker4(Options.Skins.Color.color2, false);
						}
						ImGui::Checkbox(XorStr("Skin Color 3"), &Options.Skins.Color.Custom3);
						if (Options.Skins.Color.Custom3)
						{
							ColorPicker4(Options.Skins.Color.color3, false);
						}
						ImGui::Text(XorStr("HOME KEY = Apply Skins"));
					}
					else
					{
						if (Engine->IsInGame() && Engine->IsConnected() && !Global::LocalPlayer->GetHealth() > 0)
						{
							ImGui::Text(XorStr("You must be alive to change skins."));
						}
						else
						{
							ImGui::Text(XorStr("You must be ingame to change skins."));
						}
					}
				}
				ImGui::PopItemWidth();
				ImGui::End();
			}

			if (Options.Menu.WeaponConfigs)
			{
				auto lCheck = Options.AntiCheat.League;
				ImGui::Begin(XorStr("Weapon Config"), &Options.Menu.WeaponConfigs, ImVec2(400, 400), 1.f);
				ImGui::Text(XorStr("Rifles"));
				ImGui::Separator();
				if (ImGui::CollapsingHeader(XorStr("Rifles")))
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("Rifle TriggerBot"), &Options.Legit.Aimbot.Configs.Rifles.Trigger);
					ImGui::Checkbox(XorStr("Rifle LegitBot"), &Options.Legit.Aimbot.Configs.Rifles.Enabled);
					ImGui::Checkbox(XorStr("Rifle RCS"), &Options.Legit.Aimbot.Configs.Rifles.RCS);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("Rifle SilentAim"), &Options.Legit.Aimbot.Configs.Rifles.SilentAim);
						ImGui::Checkbox(XorStr("Rifle pSilentAim"), &Options.Legit.Aimbot.Configs.Rifles.PerfectSilentAim);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("Rifle FOV"), &Options.Legit.Aimbot.Configs.Rifles.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("Rifle Smooth X"), &Options.Legit.Aimbot.Configs.Rifles.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Rifle Smooth Y"), &Options.Legit.Aimbot.Configs.Rifles.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("Rifle Bone"), &Options.Legit.Aimbot.Configs.Rifles.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{
						ImGui::SliderInt(XorStr("Rifle League FOV"), &Options.Legit.Aimbot.Configs.Rifles.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("Rifle Aim Speed"), &Options.Legit.Aimbot.Configs.Rifles.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("Rifle Multiply Speed"), &Options.Legit.Aimbot.Configs.Rifles.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("Rifle FOV Boost"), &Options.Legit.Aimbot.Configs.Rifles.FOVBOOST, 1, 10);
					}
					ImGui::PopItemWidth();
				}
				ImGui::Text(XorStr("Pistols"));
				ImGui::Separator();
				if (ImGui::CollapsingHeader(XorStr("Pistols")))
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("Pistol TriggerBot"), &Options.Legit.Aimbot.Configs.Pistols.Trigger);
					ImGui::Checkbox(XorStr("Pistol LegitBot"), &Options.Legit.Aimbot.Configs.Pistols.Enabled);
					ImGui::Checkbox(XorStr("Pistol RCS"), &Options.Legit.Aimbot.Configs.Pistols.RCS);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("Pistol SilentAim"), &Options.Legit.Aimbot.Configs.Pistols.SilentAim);
						ImGui::Checkbox(XorStr("Pistol pSilentAim"), &Options.Legit.Aimbot.Configs.Pistols.PerfectSilentAim);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("Pistol FOV"), &Options.Legit.Aimbot.Configs.Pistols.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("Pistol Smooth X"), &Options.Legit.Aimbot.Configs.Pistols.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Pistol Smooth Y"), &Options.Legit.Aimbot.Configs.Pistols.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("Pistol Bone"), &Options.Legit.Aimbot.Configs.Pistols.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{
						ImGui::SliderInt(XorStr("Pistol League FOV"), &Options.Legit.Aimbot.Configs.Pistols.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("Pistol Aim Speed"), &Options.Legit.Aimbot.Configs.Pistols.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("Pistol Multiply Speed"), &Options.Legit.Aimbot.Configs.Pistols.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("Pistol FOV Boost"), &Options.Legit.Aimbot.Configs.Pistols.FOVBOOST, 1, 10);
					}
					ImGui::PopItemWidth();
				}
				ImGui::Text(XorStr("Sniper"));
				ImGui::Separator();
				if (ImGui::CollapsingHeader(XorStr("Sniper")))
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("Sniper TriggerBot"), &Options.Legit.Aimbot.Configs.Snipers.Trigger);
					ImGui::Checkbox(XorStr("Sniper LegitBot"), &Options.Legit.Aimbot.Configs.Snipers.Enabled);
					ImGui::Checkbox(XorStr("Sniper RCS"), &Options.Legit.Aimbot.Configs.Snipers.RCS);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("Sniper SilentAim"), &Options.Legit.Aimbot.Configs.Snipers.SilentAim);
						ImGui::Checkbox(XorStr("Sniper pSilentAim"), &Options.Legit.Aimbot.Configs.Snipers.PerfectSilentAim);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("Sniper FOV"), &Options.Legit.Aimbot.Configs.Snipers.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("Sniper Smooth X"), &Options.Legit.Aimbot.Configs.Snipers.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Sniper Smooth Y"), &Options.Legit.Aimbot.Configs.Snipers.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("Sniper Bone"), &Options.Legit.Aimbot.Configs.Snipers.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{
						ImGui::SliderInt(XorStr("Sniper League FOV"), &Options.Legit.Aimbot.Configs.Snipers.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("Sniper Aim Speed"), &Options.Legit.Aimbot.Configs.Snipers.AimSpeed, 1, 900);
						ImGui::SliderInt(XorStr("Sniper Multiply Speed"), &Options.Legit.Aimbot.Configs.Snipers.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("Sniper FOV Boost"), &Options.Legit.Aimbot.Configs.Snipers.FOVBOOST, 1, 10);
					}
					ImGui::PopItemWidth();
				}
				ImGui::Text(XorStr("Shotgun"));
				ImGui::Separator();
				if (ImGui::CollapsingHeader(XorStr("Shotgun")))
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("Shotgun TriggerBot"), &Options.Legit.Aimbot.Configs.Shotguns.Trigger);
					ImGui::Checkbox(XorStr("Shotgun LegitBot"), &Options.Legit.Aimbot.Configs.Shotguns.Enabled);
					ImGui::Checkbox(XorStr("Shotgun RCS"), &Options.Legit.Aimbot.Configs.Shotguns.RCS);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("Shotgun SilentAim"), &Options.Legit.Aimbot.Configs.Shotguns.SilentAim);
						ImGui::Checkbox(XorStr("Shotgun pSilentAim"), &Options.Legit.Aimbot.Configs.Shotguns.PerfectSilentAim);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("Shotgun FOV"), &Options.Legit.Aimbot.Configs.Shotguns.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("Shotgun Smooth X"), &Options.Legit.Aimbot.Configs.Shotguns.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("Shotgun Smooth Y"), &Options.Legit.Aimbot.Configs.Shotguns.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("Shotgun Bone"), &Options.Legit.Aimbot.Configs.Shotguns.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{
						ImGui::SliderInt(XorStr("Shotgun League FOV"), &Options.Legit.Aimbot.Configs.Shotguns.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("ShotgunAim Speed"), &Options.Legit.Aimbot.Configs.Shotguns.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("Shotgun Multiply Speed"), &Options.Legit.Aimbot.Configs.Shotguns.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("Shotgun FOV Boost"), &Options.Legit.Aimbot.Configs.Shotguns.FOVBOOST, 1, 10);
					}
					ImGui::PopItemWidth();
				}
				ImGui::Text(XorStr("Sub-Machine-Guns"));
				ImGui::Separator();
				if (ImGui::CollapsingHeader(XorStr("Sub-Machine-Guns")))
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("SMG TriggerBot"), &Options.Legit.Aimbot.Configs.SMGs.Trigger);
					ImGui::Checkbox(XorStr("SMG LegitBot"), &Options.Legit.Aimbot.Configs.SMGs.Enabled);
					ImGui::Checkbox(XorStr("SMG RCS"), &Options.Legit.Aimbot.Configs.SMGs.RCS);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("SMG SilentAim"), &Options.Legit.Aimbot.Configs.SMGs.SilentAim);
						ImGui::Checkbox(XorStr("SMG pSilentAim"), &Options.Legit.Aimbot.Configs.SMGs.PerfectSilentAim);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("SMG FOV"), &Options.Legit.Aimbot.Configs.SMGs.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("SMG Smooth X"), &Options.Legit.Aimbot.Configs.SMGs.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("SMG Smooth Y"), &Options.Legit.Aimbot.Configs.SMGs.Smooth[1], 1.f, 100.f, "%.1f");
					}
					ImGui::Combo(XorStr("SMG Bone"), &Options.Legit.Aimbot.Configs.SMGs.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{

						ImGui::SliderInt(XorStr("SMG League FOV"), &Options.Legit.Aimbot.Configs.SMGs.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("SMG Aim Speed"), &Options.Legit.Aimbot.Configs.SMGs.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("SMG Multiply Speed"), &Options.Legit.Aimbot.Configs.SMGs.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("SMG FOV Boost"), &Options.Legit.Aimbot.Configs.SMGs.FOVBOOST, 1, 10);
					}
					ImGui::PopItemWidth();
				}
				ImGui::Text(XorStr("Machine-Guns"));
				ImGui::Separator();
				if (ImGui::CollapsingHeader(XorStr("Machine-Guns")))
				{
					ImGui::PushItemWidth(200);
					ImGui::Checkbox(XorStr("MG TriggerBot"), &Options.Legit.Aimbot.Configs.Machineguns.Trigger);
					ImGui::Checkbox(XorStr("MG LegitBot"), &Options.Legit.Aimbot.Configs.Machineguns.Enabled);
					ImGui::Checkbox(XorStr("MG RCS"), &Options.Legit.Aimbot.Configs.Machineguns.RCS);
					if (!lCheck)
					{
						ImGui::Checkbox(XorStr("MG SilentAim"), &Options.Legit.Aimbot.Configs.Machineguns.SilentAim);
						ImGui::Checkbox(XorStr("MG pSilentAim"), &Options.Legit.Aimbot.Configs.Machineguns.PerfectSilentAim);
					}
					if (!lCheck)
					{
						ImGui::SliderFloat(XorStr("MG FOV"), &Options.Legit.Aimbot.Configs.Machineguns.Fov, 0.f, 180.f, "%.1f");
						ImGui::SliderFloat(XorStr("MG Smooth X"), &Options.Legit.Aimbot.Configs.Machineguns.Smooth[0], 1.f, 100.f, "%.1f");
						ImGui::SliderFloat(XorStr("MG Smooth Y"), &Options.Legit.Aimbot.Configs.Machineguns.Smooth[1], 1.f, 100.f, "%.1f");
						
					}
					ImGui::Combo(XorStr("MG Bone"), &Options.Legit.Aimbot.Configs.Machineguns.Bone, Bones, ARRAYSIZE(Bones));
					if (lCheck)
					{

						ImGui::SliderInt(XorStr("MG League FOV"), &Options.Legit.Aimbot.Configs.Machineguns.LFOV, 1, 300);
						ImGui::SliderInt(XorStr("MG Aim Speed"), &Options.Legit.Aimbot.Configs.Machineguns.AimSpeed, 1, 300);
						ImGui::SliderInt(XorStr("MG Multiply Speed"), &Options.Legit.Aimbot.Configs.Machineguns.MultiplySpeed, 1, 10);
						ImGui::SliderInt(XorStr("MG FOV Boost"), &Options.Legit.Aimbot.Configs.Machineguns.FOVBOOST, 1, 10);
					}
					ImGui::PopItemWidth();
				}
				ImGui::Checkbox(XorStr("Weapon Configs"), &Options.Legit.Aimbot.WeaponConfigs);
				ImGui::End();
			}

		}
		Global::g_pRenderer->BeginRendering();
		if (Options.Menu.Opened)
		{
			Infamy->pPos.x = Pos.x + 350;
			Infamy->pPos.y = Pos.y - 75;	// Fps Fix
			if (Infamy && Infamy->IsInit())Infamy->Draw();
		}

		ImGui::Render();

		Global::g_pRenderer->EndRendering();

	}
	return oEndScene(pDevice);
}
HRESULT __stdcall Game::hkdReset(IDirect3DDevice9* pDevice, D3DPRESENT_PARAMETERS* pPresParam)
{
	if (!Global::Init) return oResetScene(pDevice, pPresParam);
	Global::g_pRenderer->OnLostDevice();
	Infamy->Release();
	ImGui_ImplDX9_InvalidateDeviceObjects();
	auto newr = oResetScene(pDevice, pPresParam);
	Infamy = new cSprite(0, 0);
	Infamy->Init(pDevice, XorStr("C://Infamy//Files//logo.png"), 259, 73);
	Global::g_pRenderer->OnResetDevice();
	ImGui_ImplDX9_CreateDeviceObjects();
	return newr;
}
void GUI_Init(IDirect3DDevice9* pDevice)
{
	ImGui_ImplDX9_Init(Global::Window, pDevice);
	Global::g_pRenderer = std::make_unique<DrawManager>(pDevice);
	auto& style = ImGui::GetStyle();
	style.Colors[ImGuiCol_Text] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextDisabled] = ImVec4(0.60f, 0.60f, 0.60f, 1.00f);
	style.Colors[ImGuiCol_WindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.59f);
	style.Colors[ImGuiCol_ChildWindowBg] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_CheckMark] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_Border] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_BorderShadow] = ImVec4(0.00f, 0.00f, 0.00f, 0.00f);
	style.Colors[ImGuiCol_FrameBg] = ImVec4(0.80f, 0.80f, 0.80f, 0.30f);
	style.Colors[ImGuiCol_FrameBgHovered] = ImVec4(0.90f, 0.80f, 0.80f, 0.40f);
	style.Colors[ImGuiCol_FrameBgActive] = ImVec4(0.90f, 0.65f, 0.65f, 0.45f);
	style.Colors[ImGuiCol_TitleBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgCollapsed] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TitleBgActive] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_MenuBarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarBg] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrab] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabHovered] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ScrollbarGrabActive] = ImVec4(0.00f, 1.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ComboBg] = ImVec4(0.20f, 0.20f, 0.20f, 0.99f);
	style.Colors[ImGuiCol_SliderGrab] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_SliderGrabActive] = ImVec4(0.80f, 0.50f, 0.50f, 1.00f);
	style.Colors[ImGuiCol_Button] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ButtonHovered] = ImVec4(0.00f, 0.06f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_ButtonActive] = ImVec4(0.00f, 0.53f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_Header] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderHovered] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_HeaderActive] = ImVec4(0.00f, 0.15f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_Column] = ImVec4(0.39f, 0.39f, 0.39f, 1.00f);
	style.Colors[ImGuiCol_ColumnHovered] = ImVec4(0.26f, 0.59f, 0.98f, 0.78f);
	style.Colors[ImGuiCol_ColumnActive] = ImVec4(0.26f, 0.59f, 0.98f, 1.00f);
	style.Colors[ImGuiCol_ResizeGrip] = ImVec4(1.00f, 1.00f, 1.00f, 0.30f);
	style.Colors[ImGuiCol_ResizeGripHovered] = ImVec4(1.00f, 1.00f, 1.00f, 0.60f);
	style.Colors[ImGuiCol_ResizeGripActive] = ImVec4(1.00f, 1.00f, 1.00f, 0.90f);
	style.Colors[ImGuiCol_CloseButton] = ImVec4(0.00f, 0.98f, 0.00f, 0.59f);
	style.Colors[ImGuiCol_CloseButtonHovered] = ImVec4(0.00f, 0.00f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_CloseButtonActive] = ImVec4(0.00f, 0.09f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLines] = ImVec4(1.00f, 1.00f, 1.00f, 1.00f);
	style.Colors[ImGuiCol_PlotLinesHovered] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogram] = ImVec4(0.90f, 0.70f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_PlotHistogramHovered] = ImVec4(1.00f, 0.60f, 0.00f, 1.00f);
	style.Colors[ImGuiCol_TextSelectedBg] = ImVec4(0.00f, 0.00f, 1.00f, 0.35f);
	style.Colors[ImGuiCol_TooltipBg] = ImVec4(0.05f, 0.05f, 0.10f, 0.90f);
	style.Colors[ImGuiCol_ModalWindowDarkening] = ImVec4(0.20f, 0.20f, 0.20f, 0.35f);
	style.WindowTitleAlign = ImGuiAlign_Center;

	//ConSys->LoadConfig();
	Infamy = new cSprite(0, 0);
	Infamy->Init(pDevice, XorStr("C://Infamy//Files//logo.png"), 259, 73);
	Global::Init = true;
}