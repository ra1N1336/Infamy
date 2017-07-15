#include "Console.h"
#include <shellapi.h>

CConsole* CommandConsole = new CConsole();

bool CConsole::IsActive()
{
	if (!bActive)
		return false;
	else
		return true;
}

char* stringToLower(char *string)
{
	int i;
	int len = strlen(string);
	for (i = 0; i<len; i++) {
		if (string[i] >= 'A' && string[i] <= 'Z') {
			string[i] += 32;
		}
	}
	return string;
}


bool bIsDigitInString(std::string pszString)
{
	for (int ax = 0; ax < 9; ax++)
	{
		char buf[MAX_PATH];

		_snprintf(buf, (size_t)255, "%d", ax);

		if (strstr(pszString.c_str(), buf))
		{
			return true;
		}
	}
	return false;
}


void CConsole::addCvar(char *szName, int iValue, bool bStyle)
{
	CRetVar buf = CRetVar(szName, iValue, bStyle);
	vars.push_back(buf);
}

int CConsole::getValue(const char* szName)
{
	for (int ax = 0; ax < vars.size(); ax++)
	{
		if (vars[ax].szName == szName)
			return vars[ax].iValue;
	}
	return 0;
}

void CConsole::HandleCommands(std::string szCommand)
{
	if (szCommand.empty())
		return;

	if (strcmp(szCommand.c_str(), "exit") == 0)
	{
		selected = 0;
		bActive = !bActive;
		return;
	}

	int r = getValue("font_color_r");
	int g = getValue("font_color_g");
	int b = getValue("font_color_b");

	char szCommandBuffer[512] = "";
	strcpy(szCommandBuffer, szCommand.c_str());

	szCommand = stringToLower(szCommandBuffer);

	if (strcmp(szCommand.c_str(), "commands") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].bStyle == true)
				continue;

			print(r, g, b, "%s %i", vars[ax].szName.c_str(), vars[ax].iValue);
		}
		return;
	}

	std::string szCmd, szValue;
	int iValue;
	size_t nPos;

	bool isDigitInString = bIsDigitInString(szCommand);
	bool isTextCmd = strstr(szCommand.c_str(), "echo") || strstr(szCommand.c_str(), "exec") || strstr(szCommand.c_str(), "aim_bone_head") || strstr(szCommand.c_str(), "aim_bone_chest") || strstr(szCommand.c_str(), "aim_bone_upperchest") ||
		strstr(szCommand.c_str(), "triggerbotkey_shift") || strstr(szCommand.c_str(), "triggerbotkey_ctrl") || strstr(szCommand.c_str(), "triggerbotkey_alt") || strstr(szCommand.c_str(), "triggerbotkey_mouse5") || strstr(szCommand.c_str(), "triggerbotkey_mouse4");

	if (isDigitInString || isTextCmd)
	{
		nPos = szCommand.find_first_of(" ");

		if (nPos != std::string::npos)
		{
			szCmd = szCommand.substr(0, nPos);

			szCommand.erase(0, nPos + 1);

			if (szCommand.length() > 0)
			{
				szValue = szCommand;
			}
		}

	}
	else
	{
#ifdef DEBUG
		print(r, g, b, "%s - %i", szCommand.c_str(), getValue(szCommand.c_str()));
#endif
	}

	if (strcmp(szCmd.c_str(), "echo") == 0)
	{
		print(r, g, b, szValue.c_str());
		return;
	}

	if (strcmp(szCmd.c_str(), "aim_bone_head") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].szName == "aimbot_bone")
			{
				vars[ax].iValue = 6;
			}
		}
		print(0, 255, 127, "NOTICE: Aimbot bone has been modified");
		return;
	}

	if (strcmp(szCmd.c_str(), "aim_bone_upperchest") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].szName == "aimbot_bone")
			{
				vars[ax].iValue = 4;
			}
		}
		print(0, 255, 127, "NOTICE: Aimbot bone has been modified");
		return;
	}

	if (strcmp(szCmd.c_str(), "aim_bone_chest") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].szName == "aimbot_bone")
			{
				vars[ax].iValue = 3;
			}
		}
		print(0, 255, 127, "NOTICE: Aimbot bone has been modified");
		return;
	}

	if (strcmp(szCmd.c_str(), "triggerbotkey_shift") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].szName == "triggerbot_key")
			{
				vars[ax].iValue = 0x10;
			}
		}
		print(0, 255, 127, "NOTICE: The triggerbot key has been modified");
		return;
	}

	if (strcmp(szCmd.c_str(), "triggerbotkey_alt") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].szName == "triggerbot_key")
			{
				vars[ax].iValue = 0x12;
			}
		}
		print(0, 255, 127, "NOTICE: The triggerbot key has been modified");
		return;
	}

	if (strcmp(szCmd.c_str(), "triggerbotkey_ctrl") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].szName == "triggerbot_key")
			{
				vars[ax].iValue = 0x11; // Because pika is retarded ????? its actually 12 fam.
			}
		}
		print(0, 255, 127, "NOTICE: The triggerbot key has been modified");
		return;
	}

	if (strcmp(szCmd.c_str(), "help") == 0)
	{
		ShellExecute(NULL, "open", "https://docs.google.com/document/d/13OD1_CNezZvwcfUEgoCIyRtCeThP9wg16qsmaeiS4DU/", NULL, NULL, SW_SHOWNORMAL);
		return;
	}

	if (strcmp(szCmd.c_str(), "triggerbotkey_mouse5") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].szName == "triggerbot_key")
			{
				vars[ax].iValue = 0x06;
			}
		}
		print(0, 255, 127, "NOTICE: The triggerbot key has been modified");
		return;
	}

	if (strcmp(szCmd.c_str(), "triggerbotkey_mouse4") == 0)
	{
		for (int ax = 0; ax < vars.size(); ax++)
		{
			if (vars[ax].szName == "triggerbot_key")
			{
				vars[ax].iValue = 0x05;
			}
		}
		print(0, 255, 127, "NOTICE: The triggerbot key has been modified");
		return;
	}

	// Begin triggerbot input command entry handle


	iValue = atoi(szValue.c_str());

	for (int ax = 0; ax < vars.size(); ax++)
	{
		if (strcmp(vars[ax].szName.c_str(), szCmd.c_str()) == 0)
		{
			vars[ax].iValue = iValue;

			if (vars[ax].bStyle == true)
				continue;
			if (!bCfgload)
			{
				print(0, 255, 127, "NOTICE: cvar %s has been modified.", szCmd.c_str(), iValue);
			}
			if (bCfgload)
			{
				bCfgload = false;
			}
		}
	}
}

std::string getClipboard()
{
	if (!OpenClipboard(nullptr))
		return "";

	HANDLE hData = GetClipboardData(CF_TEXT);
	if (!hData)
		return "";

	char * pszText = static_cast<char*>(GlobalLock(hData));
	if (pszText == nullptr)
		return "";

	GlobalUnlock(hData);
	CloseClipboard();

	return std::string(pszText);
}

void CConsole::HandleKeys(int key)
{

	Key_t pKey = gKeyMap[key];

	switch (key)
	{
	case KEY_LSHIFT:
	case KEY_RSHIFT:
	case KEY_LCONTROL:
	case KEY_RCONTROL:
	case KEY_LEFT:
	case KEY_RIGHT:
	case KEY_CAPSLOCKTOGGLE:
		return;

	case KEY_UP:
		return;

	case KEY_DOWN:
		return;


	case KEY_ENTER:
		if (bComplete == true)
		{
			command = vars[selected - 1].szName;
			command.append(" ");
			selected = 0;
			bComplete = false;
			return;
		}

		HandleCommands(command.c_str());
		command.clear();
		buf.clear();
		counter = 0;
		selected = 0;
		return;

	case KEY_SPACE:
		command.append(" ");
		return;

	case KEY_BACKSPACE:
		if (command.length() > 0)
		{
			command.erase(command.length() - 1);
			counter--;
		}
		return;
	}



	if (GetAsyncKeyState(VK_LSHIFT) || GetAsyncKeyState(VK_RSHIFT))
	{
		command.append(pKey.m_alt);
		counter++;
	}
	else if (GetAsyncKeyState(VK_LCONTROL) && GetAsyncKeyState(0x56))
	{
		std::string Data = getClipboard();
		command.append(Data);
		counter++;
	}
	else
	{
		command.append(pKey.m_def);
		counter++;
	}
}

void CConsole::RenderConsole()
{
	if (!bActive)
		return;

	static bool bDidOnce = false;

	//int r = getValue("font_color_r");
	//int g = getValue("font_color_g");
	//int b = getValue("font_color_b");

	int rc = 117;
	int gc = 97;
	int bc = 49;

	if (bDidOnce == false)
	{
		print(rc, gc, bc, "Main Developers:");
		print(rand() % 255, rand() % 255, rand() % 255, "@rwby");
		print(rc, gc, bc, "");
		print(rc, gc, bc, "Community Developing Credits:");
		print(rc, gc, bc, "@Truix");
		bDidOnce = true;
		iPrintCounter = 0;
	}

	int iWidth, iHeight;
	RWBYHAX.m_pEngine->GetScreenSize(iWidth, iHeight);

	// New Frame

	RWBYHAX.m_pDraw->FillRGBA(600, 100, 400, 500, getValue("menu_color_r"), getValue("menu_color_g"), getValue("menu_color_b"), 100); //MainFrame
	RWBYHAX.m_pDraw->DrawBox(600, 100, 400, 500, 3, 0, 0, 0, 255); //MainBox
	RWBYHAX.m_pDraw->DrawBox(600, 570, 400, 30, 3, 0, 0, 0, 255); //InputField

	//DrawString(RWBYHAX.menupls, false, 605, 73, 255, 0, 0, 255, "Azay's Command Console v1.8");
	DrawString(RWBYHAX.m_pFont, false, 605, 575, 255, 0, 0, 255, command.c_str());

	for (int ax = 0; ax < output.size(); ax++)
	{
		int iIndex = (output.size() - ax) + 1;
		int iHeight = 580 - (20 * (iIndex));

		if (iHeight < 120)
			continue;

		DrawString(RWBYHAX.m_pFont, false, 605, iHeight, 255, 0, 0, 255, (char*)output[ax].c_str());
	}

}

void CConsole::print(int r, int g, int b, const char* szInput, ...)
{
	va_list		va_alist;
	char		szBuf[2048];

	va_start(va_alist, szInput);
	_vsnprintf(szBuf, sizeof(szBuf), szInput, va_alist);
	va_end(va_alist);

	COLOR buf;

	buf.r = r;
	buf.g = g;
	buf.b = b;
	buf.a = 255;

	output.push_back(szBuf);
	outputColor.push_back(buf);
}

void CConsole::readConfig(const char* szName)
{
	std::string line;
	std::string crtlDir = "C:\\settings\\";
	std::string path = crtlDir + szName;

	std::ifstream myfile(path);
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			if (strstr(line.c_str(), "//"))
				continue;

			bCfgload = true;
			HandleCommands(line);
		}
		myfile.close();
	}
	else
		print(255, 0, 0, "ERROR: Config could not be located!");
}

void CConsole::initCommands()
{

	// Gonna start seperating Cvars as we are getting a bit large now.
	addCvar("aimbot_enabled", 2, false);
	addCvar("aimbot_key", 0, false);
	addCvar("aimbot_fov", 2, false);
	addCvar("aimbot_bone", 3, false);
	addCvar("aimbot_silentfov", 0, false);
	addCvar("aimbot_aimspeed", 120, false);
	addCvar("aimbot_multiplyspeed", 3, false);
	addCvar("aimbot_fovboost", 4, false);

	// Visuals 

	addCvar("esp_enabled", 0, false);
	addCvar("esp_health", 0, false);
	addCvar("esp_awarebar", 0, false);
	addCvar("esp_cornerbox", 0, false);
	addCvar("esp_box", 0, false);
	addCvar("esp_name", 0, false);
	addCvar("esp_infoenabled", 0, false);
	addCvar("esp_infohealth", 0, false);
	addCvar("esp_infoarmor", 0, false);
	addCvar("esp_infoweapon", 0, false);
	addCvar("esp_infoammo", 0, false);
	addCvar("esp_infodefuse", 0, false);
	addCvar("esp_infoname", 0, false);
	addCvar("esp_bones", 0, false);
	addCvar("esp_barrel", 0, false);
	addCvar("esp_chat", 0, false);
	//addCvar("esp_defusetimer", 0, false); //Coming back at a later time.
	addCvar("radar_enabled", 0, false);
	addCvar("chams_enabled", 0, false);
	addCvar("chams_red", 255, false);
	addCvar("chams_blue", 0, false);
	addCvar("chams_green", 0, false);
	addCvar("chams_vischeck", 1, false);
	addCvar("bunnyhop_enabled", 0, false);
	addCvar("noflash_enabled", 0, false);

	// Trigger
	addCvar("triggerbot_enabled", 0, false);
	addCvar("triggerbot_key", 6, false);
	addCvar("triggerbot_delay", 0, false);

	// Skins
	addCvar("skin_cz", 0, false);
	addCvar("skin_fiveseven", 0, false);
	addCvar("skin_deagle", 0, false);
	addCvar("skin_p250", 0, false);
	addCvar("skin_glock", 0, false);
	addCvar("skin_usps", 0, false);
	addCvar("skin_p2000", 0, false);
	addCvar("skin_tec9", 0, false);
	addCvar("skin_ak47", 0, false);
	addCvar("skin_aug", 0, false);
	addCvar("skin_famas", 0, false);
	addCvar("skin_galil", 0, false);
	addCvar("skin_m4a4", 0, false);
	addCvar("skin_m4a1s", 0, false);
	addCvar("skin_bizon", 0, false);
	addCvar("skin_mac10", 0, false);
	addCvar("skin_mp7", 0, false);
	addCvar("skin_mp9", 0, false);
	addCvar("skin_p90", 0, false);
	addCvar("skin_ump45", 0, false);
	addCvar("skin_m249", 0, false);
	addCvar("skin_negev", 0, false);
	addCvar("skin_mag7", 0, false);
	addCvar("skin_nova", 0, false);
	addCvar("skin_sawed", 0, false);
	addCvar("skin_xm1014", 0, false);
	addCvar("skin_awp", 0, false);
	addCvar("skin_g3sg1", 0, false);
	addCvar("skin_scar20", 0, false);
	addCvar("skin_sg556", 0, false);
	addCvar("skin_ssg08", 0, false);
	addCvar("skin_magnum", 0, false);
	addCvar("karambit", 0, false);
	addCvar("flip", 0, false);
	addCvar("gut", 0, false);
	addCvar("bayonet", 0, false);
	addCvar("m9bayonet", 0, false);
	addCvar("dagger", 0, false);
	addCvar("falchion", 0, false);
	addCvar("huntsman", 0, false);
	addCvar("butterfly", 0, false);
	addCvar("karambit_skin", 0, false);
	addCvar("m9bayonet_skin", 0, false);
	addCvar("butterfly_skin", 0, false);
	addCvar("flip_skin", 0, false);
	addCvar("gut_skin", 0, false);
	addCvar("bayonet_skin", 0, false);
	addCvar("dagger_skin", 0, false);
	addCvar("falchion_skin", 0, false);
	addCvar("huntsman_skin", 0, false);
	addCvar("knifeseed", 0, false);
	addCvar("randomknifeseed", 0, false);
	addCvar("weapon_stattrak", 0, false);
	addCvar("nametag", 0, false);


	// HvH Features
	addCvar("antiuntrusted_enabled", 1, false);
	addCvar("hvh_norecoil_enabled", 0, false); // Hidden from the public still in the cheat but not shown publicly.
	addCvar("hvh_stopcrouch_enabled", 0, false); // Hidden from the public still in the cheat but not shown publicly.
	addCvar("hvh_antiaim_style", 0, false); // Hidden from the public still in the cheat but not shown publicly.
	addCvar("hvh_antiaim_packets", 8, false); // Hidden from the public still in the cheat but not shown publicly.
	addCvar("misc_fov90", 0, false);
	addCvar("misc_coin", 0, false);
	addCvar("misc_music_kit", 0, false);
	addCvar("misc_casual_rank", 0, false);
	// features that i dont know what the fuck im doing with.
	addCvar("menu_color_r", 0, false);
	addCvar("menu_color_g", 0, false);
	addCvar("menu_color_b", 0, false);
}
