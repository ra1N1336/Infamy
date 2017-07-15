#include "Menu.h"
#include "mouse.h"
cMenu* myMenu = new cMenu;

bool Settings::NewMenu::active;

bool test = false;
bool RageMenu;
bool LegitMenu;
bool VisualMenu;
bool MiscMenu;
bool SkinsMenu;

static bool wasMousePressedLastTick = false;
void cMenu::Paint()
{

	static bool once = false;
	if (input->IsButtonDown(KEY_INSERT))
	{
		if (!once)
		{
			Settings::NewMenu::active = !Settings::NewMenu::active;
			if (Settings::NewMenu::active)
				Engine->ClientCmd_Unrestricted("cl_mouseenable 0", false);
			else
				Engine->ClientCmd_Unrestricted("cl_mouseenable 1", false);
			once = true;
		}
	}
	else
	{
		once = false;
	}

	if (!Settings::NewMenu::active)
		return;


	//Input->GetClicked();

	int width, height;
	Engine->GetScreenSize(width, height);
	int menuX = 200, menuY = 200;

	// Begin Overall menu drawing
	DrawFrame(menuX, menuY, 650, 450);
	Draw::DrawString(Impact, menuX + 300, menuY - 30, Color(0, 255, 0, 255), FONT_CENTER, "infamy.founder");
	DrawTabs(menuX, menuY);

	// Begin our groups
	/*if (Options.Menu.Ragebot)
	{
		DrawGroupBox("Ragebot", menuX + 200, menuY + 30, 250, 400);
	}

	if (Options.Menu.Legitbot)
	{
		DrawGroupBox("Legitbot", menuX + 200, menuY + 30, 250, 400);
	}

	// Begin our actual checkboxes.
	// Rage

	if (Options.Menu.Ragebot)
	{
		DrawCheckbox("Enabled", menuX + 225, menuY + 60, Options.Rage.Aimbot.Enabled);
	}*/


	//DrawTab("Legit", menuX + 20, menuY + 65, LegitMenu);
	//DrawTab("Visuals", menuX + 20, menuY + 100, VisualMenu);
	//DrawTab("Misc", menuX + 20, menuY + 135, MiscMenu);
	//DrawTab("Skins", menuX + 20, menuY + 170, SkinsMenu);
	//DrawButton("Load", menuX + 20, menuY + 280, 150, 30);
	//DrawButton("Save", menuX + 20, menuY + 320, 150, 30);
//	DrawButton("Reset", menuX + 20, menuY + 360, 150, 30);
//	DrawButton("Unload", menuX + 20, menuY + 400, 150, 30);

//	if (Input->Clicked(menuX + 20, menuY + 400, 150, 30))
	//{
		//Options.Cheat.Uninject = true;
//	}
}

void cMenu::DrawFrame(int x, int y, int w, int h)
{
	static int bWasntHolding = false;
	static int bGrabbing = false;
	static int iOffsetX = 0, iOffsetY = 0;

	POINT ptMouse = Input->GetMousePos();

	if (Input->Holding(x, y, w, 12) && !bGrabbing && bWasntHolding)
	{
		bGrabbing = true;
		iOffsetX = x - ptMouse.x;
		iOffsetY = y - ptMouse.y;
	}
	else if (bGrabbing && !GetAsyncKeyState(VK_LBUTTON))
	{
		bGrabbing = false;
		iOffsetX = 0;
		iOffsetY = 0;
	}

	if (bGrabbing)
	{
		x = ptMouse.x + iOffsetX;
		y = ptMouse.y + iOffsetY;
	}

	//i cant code
	static float rainbow;
	DrawRect(x, y, w, h, Color(20, 20, 20, 254));//entire black fill
	DrawOutlinedRect(x - 1, y - 1, w + 1, h + 1, Color(15, 15, 15, 255));//inner black line
	DrawOutlinedRect(x - 2, y - 2, w + 3, h + 3, Color(60, 60, 60, 255));//inner light gray line
	DrawOutlinedRect(x - 3, y - 3, w + 5, h + 5, Color(40, 40, 40, 255));//1px 3.1 line connection
	DrawOutlinedRect(x - 4, y - 4, w + 7, h + 7, Color(40, 40, 40, 255));//1px 3.2 line connection
	DrawOutlinedRect(x - 5, y - 5, w + 9, h + 9, Color(40, 40, 40, 255));//1px 3.3 line connection
	DrawOutlinedRect(x - 6, y - 6, w + 11, h + 11, Color(60, 60, 60, 255));//outer light gray line
	DrawOutlinedRect(x - 7, y - 7, w + 13, h + 13, Color(15, 15, 15, 255));//outer black line
	DrawRectRainbow(x, y, w - 1, 3, 0.002, rainbow);
}

/*void cMenu::DrawGroupBox(const char* text, int x, int y, int w, int h)
{
	DrawOutlinedRect(x - 1, y - 1, w + 1, h + 1, Color::Black());
	DrawOutlinedRect(x, y, w, h, Color(50, 50, 50, 255));
	DrawString(Verdana, x + 12, y - 1, Color::White(), FONT_LEFT, text);
}*/

void cMenu::DrawTabs(int x, int y)
{
	//if (Input->Clicked(x, y, GetStringWidth(Impact, text), 30))
	//{
		//value = !value;
	//}

	if (Input->Clicked(x + 20, y + 20, GetStringWidth(Impact, "Rage"), 30))
	{
		Options.Menu.Ragebot = true;
		Options.Menu.PlayerMods = false;
		Options.Menu.Legitbot = false;
		Options.Menu.Visuals = false;
		Options.Menu.Removals = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
	}

	if (Input->Clicked(x + 20, y + 50, GetStringWidth(Impact, "Legit"), 30))
	{
		Options.Menu.Legitbot = true;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Visuals = false;
		Options.Menu.Removals = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
	}

	if (Input->Clicked(x + 20, y + 80, GetStringWidth(Impact, "PlayerMods"), 30))
	{
		Options.Menu.PlayerMods = true;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.Visuals = false;
		Options.Menu.Removals = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
	}

	if (Input->Clicked(x + 20, y + 110, GetStringWidth(Impact, "Visuals"), 30))
	{
		Options.Menu.Visuals = true;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.Removals = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
	}

	if (Input->Clicked(x + 20, y + 140, GetStringWidth(Impact, "Removals"), 30))
	{
		Options.Menu.Removals = true;
		Options.Menu.Visuals = false;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.AAC = false;
		Options.Menu.Skins = false;
	}

	if (Input->Clicked(x + 20, y + 170, GetStringWidth(Impact, "Anti-Cheats"), 30))
	{
		Options.Menu.AAC = true;
		Options.Menu.Removals = false;
		Options.Menu.Visuals = false;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
		Options.Menu.Skins = false;
	}

	if (Input->Clicked(x + 20, y + 200, GetStringWidth(Impact, "Skins"), 30))
	{
		Options.Menu.Skins = true;
		Options.Menu.AAC = false;
		Options.Menu.Removals = false;
		Options.Menu.Visuals = false;
		Options.Menu.PlayerMods = false;
		Options.Menu.Ragebot = false;
		Options.Menu.Legitbot = false;
	}

	//if (Input->Hovering(x, y, GetStringWidth(Impact, text), 30))
	//{
		//DrawString(Impact, x, y, Color(255, 0, 0, 255), FONT_LEFT, text);
//	}

	if (Options.Menu.Ragebot)
	{
		DrawString(Impact, x + 20, y + 30, Color::White(), FONT_LEFT, "Rage");
	}
	else
	{
		DrawString(Impact, x + 20, y + 30, Color(80, 80, 80, 255), FONT_LEFT, "Rage");
	}

	if (Options.Menu.Legitbot)
	{
		DrawString(Impact, x + 20, y + 60, Color::White(), FONT_LEFT, "Legit");
	}
	else
	{
		DrawString(Impact, x + 20, y + 60, Color(80, 80, 80, 255), FONT_LEFT, "Legit");
	}

	if (Options.Menu.PlayerMods)
	{
		DrawString(Impact, x + 20, y + 90, Color::White(), FONT_LEFT, "PlayerMods");
	}
	else
	{
		DrawString(Impact, x + 20, y + 90, Color(80, 80, 80, 255), FONT_LEFT, "PlayerMods");
	}

	if (Options.Menu.Visuals)
	{
		DrawString(Impact, x + 20, y + 120, Color::White(), FONT_LEFT, "Visuals");
	}
	else
	{
		DrawString(Impact, x + 20, y + 120, Color(80, 80, 80, 255), FONT_LEFT, "Visuals");
	}

	if (Options.Menu.Removals)
	{
		DrawString(Impact, x + 20, y + 150, Color::White(), FONT_LEFT, "Removals");
	}
	else
	{
		DrawString(Impact, x + 20, y + 150, Color(80, 80, 80, 255), FONT_LEFT, "Removals");
	}

	if (Options.Menu.AAC)
	{
		DrawString(Impact, x + 20, y + 180, Color::White(), FONT_LEFT, "Anti-Cheats");
	}
	else
	{
		DrawString(Impact, x + 20, y + 180, Color(80, 80, 80, 255), FONT_LEFT, "Anti-Cheats");
	}

	if (Options.Menu.Skins)
	{
		DrawString(Impact, x + 20, y + 210, Color::White(), FONT_LEFT, "Skins");
	}
	else
	{
		DrawString(Impact, x + 20, y + 210, Color(80, 80, 80, 255), FONT_LEFT, "Skins");
	}

	//if (value)
	//{
		//DrawString(Impact, x, y, Color::White(), FONT_LEFT, text);
	//}
	//else
	//{
		//DrawString(Impact, x, y, Color(80, 80, 80, 255), FONT_LEFT, text);
//	}
}

void cMenu::DrawButton(const char* text, int x, int y, int w, int h)
{
	if (Input->Hovering(x, y, w, h))
	{
		DrawRectGradientVertical(x, y, w, h, Color(30, 30, 30, 255), Color(20, 20, 20, 255));
		DrawOutlinedRect(x - 1, y - 1, w + 3, h + 3, Color(40, 40, 40, 255));
		DrawOutlinedRect(x - 2, y - 2, w + 5, h + 5, Color(10, 10, 10, 255));
		DrawString(Verdana, x + w / 2, y + h / 2, Color::White(), FONT_CENTER, text);
		DrawRect(x - 2, y - 2, w + 5, h + 5, Color(255, 255, 255, 3));
	}
	else
	{
		DrawRectGradientVertical(x, y, w, h, Color(30, 30, 30, 255), Color(20, 20, 20, 255));
		DrawOutlinedRect(x - 1, y - 1, w + 3, h + 3, Color(40, 40, 40, 255));
		DrawOutlinedRect(x - 2, y - 2, w + 5, h + 5, Color(10, 10, 10, 255));
		DrawString(Verdana, x + w / 2, y + h / 2, Color::White(), FONT_CENTER, text);
	}
}

void cMenu::DrawSlider(const char* text, int x, int y, int min, int max)
{

}
bool ragemenu;
void cMenu::DrawCheckbox(const char* text, int x, int y, bool value)
{

	if (Input->Hovering(x, y, 8, 8))
	{
		DrawRectGradientVertical(x, y, 8, 8, Color(70, 70, 70, 255), Color(50, 50, 50, 255));
		DrawOutlinedRect(x - 1, y - 1, 9, 9, Color::Black());
		DrawRect(x - 1, y - 1, 9, 9, Color(255, 255, 255, 3));
	}
	else
	{
		DrawRectGradientVertical(x, y, 8, 8, Color(70, 70, 70, 255), Color(50, 50, 50, 255));
		DrawOutlinedRect(x - 1, y - 1, 9, 9, Color::Black());
	}

	if (value)
	{
		DrawRectGradientVertical(x, y, 8, 8, Color(150, 200, 30, 255), Color(110, 150, 10, 255));
		DrawOutlinedRect(x - 1, y - 1, 9, 9, Color::Black());
	}

	DrawString(Verdana, x + 20, y + 3, Color::White(), FONT_LEFT, text);
}
