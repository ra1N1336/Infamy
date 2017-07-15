#pragma once
#include "sdk.h"
#include "controls.h"

bool IsClicked = false;
bool ClickedThisTick1 = false;
bool HoldingOtherMenu = false;

bool CTab::Draw(int Windowx, int Windowy, int add)
{
	if (!active)
		return false;
	for each(CControl *control in controls)
	{
		control->Draw(Windowx, Windowy + 10, 0);
	}
	return false;
}
bool  CTab::Check(int Windowx, int Windowy, int add)
{
	for each(CControl *control in controls)
	{
		control->Check(Windowx, Windowy + 10, 0);
	}
	return false;
}
void  CTab::AddControl(CControl* control)
{
	controls.push_back(control);
}

CWindow::CWindow(int x, int y, char* name)
{
	this->x = x; this->y = y; this->name = name;
}
bool CWindow::Draw(int Windowx, int Windowy, int add)
{
	bool go = false;
	if (active) {
		DrawRect(Windowx + add, Windowy, Windowx + add + 130, Windowy + 18, SeccondColor);
		go = true;
	}
	else
		DrawRect(Windowx + add, Windowy, Windowx + add + 130, Windowy + 18, ThirdColor);
	RECT nameSize = GetTextSize(39, name);
	Interfaces.pSurface->DrawT(Windowx + add + 65 - (nameSize.right / 2), Windowy + 7.5f - (nameSize.bottom / 2), FirstColor, 39, false, name);
	if (go)
	{
		int tabslength = 0;
		DrawRect(x, y, x + 450, y + 320, ThirdColor);
		DrawOutlinedRect(x - 1, y - 1, x + 450 + 1, y + 321, FirstColor);
		nameSize = GetTextSize(39, name);
		Interfaces.pSurface->DrawT(x + (450 / 2) - (nameSize.right / 2), y + 7.5f - (nameSize.bottom / 2), SeccondColor, 39, false, name);

		for each(CControl *tab in tabs)
		{
			if (tab->active)
				DrawRect(x + tabslength, y + 15, x + tabslength + (450 / (int)tabs.size()), y + 25, FirstColor);
			else
				DrawRect(x + tabslength, y + 15, x + tabslength + (450 / (int)tabs.size()), y + 25, SeccondColor);
			tab->Draw(x, y + 25, tabslength);
			tabslength += 450 / (int)tabs.size();
		}
	}
	return false;
}
bool CWindow::Check(int Windowx, int Windowy, int add)
{
	POINT Mouse;
	GetCursorPos(&Mouse);
	ScreenToClient(GetForegroundWindow(), &Mouse);
	int MouseX = Mouse.x, MouseY = Mouse.y;
	static int oldmousex, oldmousey;
	if (!holdingmenu && HoldingOtherMenu)
		return false;
	if (IsClicked)
	{
		if (MouseX >= x  && MouseX <= x + 450 || this->holdingmenu)
			if (MouseY >= y && MouseY <= y + 15 || holdingmenu)
			{
				HoldingOtherMenu = true;
				holdingmenu = true;
				x += MouseX - oldmousex;
				y += MouseY - oldmousey;
			}
	}
	else
	{
		holdingmenu = false;
		HoldingOtherMenu = false;
	}
	oldmousex = MouseX;
	oldmousey = MouseY;
	if (holdingmenu)
		return false;
	int tabslength = 0;
	for each(CControl *tab in tabs)
	{
		if (ClickedThisTick1)
			if (MouseX >= tabslength + x  && MouseX <= tabslength + x + 450 / (int)tabs.size())
				if (MouseY >= y + 15 && MouseY <= y + 25)
				{
					for each(CControl *tab1 in tabs)
						tab1->active = false;
					tab->active = true;
				}

		if (tab->active)
			tab->Check(x, y + 25, tabslength);
		tabslength += 450 / (int)tabs.size();
	}
	return false;
}
void CWindow::AddTab(CControl *tab)
{
	tabs.push_back(tab);
}

bool CMenu::Draw(int Windowx, int Windowy, int add)
{
	if (!active)
		return false;
	int count = 0;
	for each(CControl *window in windows)
	{
		window->Draw(0, 0, count * 130);
		count++;
	}

	POINT Mouse;
	GetCursorPos(&Mouse);
	ScreenToClient(GetForegroundWindow(), &Mouse);
	int MouseX = Mouse.x, MouseY = Mouse.y;

	Vertex_t Verts[3];
	Verts[0].x = MouseX;
	Verts[0].y = MouseY;
	Verts[1].x = MouseX + 16;
	Verts[1].y = MouseY + 10;
	Verts[2].x = MouseX;
	Verts[2].y = MouseY + 16;

	static int Texturer = Interfaces.pSurface->CreateNewTextureID(true);
	unsigned char buffer[4] = { 140, 140, 140, 255 };

	Interfaces.pSurface->DrawSetTextureRGBA(Texturer, buffer, 1, 1);
	Interfaces.pSurface->DrawSetTexture(Texturer);
	Interfaces.pSurface->DrawSetColor(140, 140, 140, 255);
	Interfaces.pSurface->DrawTexturedPolygon(3, Verts);

	return false;
}
bool CMenu::Check(int Windowx, int Windowy, int add)
{
	static bool once = false;
	if (GetAsyncKeyState(VK_INSERT))
	{
		if (!once)
		{
			active = !active;
			if (active)
				Interfaces.pEngine->ClientCmd_Unrestricted("cl_mouseenable 0", false);
			else
				Interfaces.pEngine->ClientCmd_Unrestricted("cl_mouseenable 1", false);
			once = true;
		}
	}
	else
	{
		once = false;
	}
	if (!active)
		return false;
	int count = 0;
	static bool once1 = false;
	IsClicked = IsMousePressed();

	ClickedThisTick1 = false;
	if (IsClicked)
	{
		if (!once1)
		{
			ClickedThisTick1 = true;
			once1 = true;
		}
	}
	else
		once1 = false;

	for each(CControl *window in windows)
	{
		POINT Mouse;
		GetCursorPos(&Mouse);
		ScreenToClient(GetForegroundWindow(), &Mouse);
		int MouseX = Mouse.x, MouseY = Mouse.y;
		if (ClickedThisTick1)
			if (MouseX >= (count * 130) + x  && MouseX <= (count * 130) + x + 130)
				if (MouseY >= y && MouseY <= y + 18)
					window->active = !window->active;
		if (window->active)
			window->Check(0, 0, 0);
		count++;
	}
	return false;
}
void CMenu::AddWindow(CControl *window)
{
	windows.push_back(window);
}

CKey::CKey(int nx, int ny, int nsize, char* text)
{
	x = nx; y = ny; size = nsize; this->text = text;
}
bool CKey::Draw(int Windowx, int Windowy, int add)
{
	int nX = x + Windowx + add, nY = y + Windowy;
	if (active)
		DrawRect(nX, nY, nX + size, nY + size, FirstColor);
	DrawOutlinedRect(nX, nY, nX + size, nY + size, CColor(255, 255, 255, 255));
	RECT nameSize = GetTextSize(39, text);
	Interfaces.pSurface->DrawT(nX + size + 6, nY + (size / 2) - (nameSize.bottom / 2), CColor(255, 255, 255, 255), 39, false, text);
	return false;
}
bool CKey::Check(int Windowx, int Windowy, int add)
{
	int nX = x + Windowx + add, nY = y + Windowy;
	static bool once = false;
	POINT Mouse;
	GetCursorPos(&Mouse);
	ScreenToClient(GetForegroundWindow(), &Mouse);
	int MouseX = Mouse.x, MouseY = Mouse.y;
	if (ClickedThisTick1)
		if (MouseX >= nX  && MouseX <= nX + size)
			if (MouseY >= nY && MouseY <= nY + size)
				active = !active;
	return false;
}

CButton::CButton(int nx, int ny, int nsize, char* text)
{
	x = nx; y = ny; size = nsize; this->text = text;
}

bool CButton::Draw(int Windowx, int Windowy, int add)
{
	int nX = x + Windowx + add, nY = y + Windowy;
	if (active)
		DrawRect(nX, nY, nX + size, nY + size, FirstColor);
	DrawOutlinedRect(nX, nY, nX + size, nY + size, CColor(255, 255, 255, 255));
	RECT nameSize = GetTextSize(39, text);
	Interfaces.pSurface->DrawT(nX + size + 6, nY + (size / 2) - (nameSize.bottom / 2), CColor(255, 255, 255, 255), 39, false, text);
	return false;
}

bool CButton::Check(int Windowx, int Windowy, int add)
{
	int nX = x + Windowx + add, nY = y + Windowy;
	static bool once = false;
	POINT Mouse;
	GetCursorPos(&Mouse);
	ScreenToClient(GetForegroundWindow(), &Mouse);
	int MouseX = Mouse.x, MouseY = Mouse.y;
	if (ClickedThisTick1)
		if (MouseX >= nX  && MouseX <= nX + size)
			if (MouseY >= nY && MouseY <= nY + size)
				active = !active;
	return false;
}

CComboBox::CComboBox()
{
}

CComboBox::CComboBox(int xz, int yz, int sizez, char* ttag)
{
	x = xz;
	y = yz;
	size = sizez;
	tag = ttag;
}

void CComboBox::addContent(char* ttag)
{
	content.push_back(ttag);
}

bool CComboBox::Check(int Windowx, int Windowy, int add)
{
	if (!ClickedThisTick1)
		return false;
	Vector origin = Vector(x + Windowx + 1, y + Windowy + 19, 0);
	int zsize = size - 1;
	int draw = 15;
	POINT Mouse;
	GetCursorPos(&Mouse);
	ScreenToClient(GetForegroundWindow(), &Mouse);
	int MouseX = Mouse.x, MouseY = Mouse.y;
	if (active)
	{
		for (int i = 0; i < (int)content.size(); i++)
		{
			if (i != activeid && content[i] != "")
			{
				if (MouseX >= origin.x && MouseX <= origin.x + size - 1)
				{
					if (MouseY >= origin.y + draw && MouseY <= origin.y + 15 + draw)
					{
						activeid = i;
						break;
					}
				}
				draw += 15;
			}
		}
		active = false;
	}
	else
		if (MouseX > x + Windowx && MouseX < x + Windowx + size)
		{
			if (MouseY > y + Windowy + 18 && MouseY < y + Windowy + 18 + 15)
			{
				active = true;
			}
		}
	return false;
}

bool CComboBox::Draw(int Windowx, int Windowy, int add)
{
	Interfaces.pSurface->DrawT(x + Windowx, y + Windowy, CColor(255, 255, 255, 255), 39, false, tag);
	Vector origin = Vector(x + 1 + Windowx, y + 19 + Windowy, 0);
	int zsize = 15;
	int draw = 0;

	DrawRect(x + Windowx, y + Windowy + 18, x + Windowx + size, y + Windowy + 18 + 17, SeccondColor);
	DrawRect(x + Windowx + 1, y + Windowy + 19, x + Windowx + size - 1, y + Windowy + 19 + 15, ThirdColor);
	if (content[activeid] != "")
	{
		RECT nameSize = GetTextSize(39, content[activeid]);
		Interfaces.pSurface->DrawT(origin.x + size / 2 - nameSize.right / 2, origin.y + 7.5f - nameSize.bottom / 2, CColor(255, 255, 255, 255), 39, false, content[activeid]);
		draw += 15;
	}
	if (active)
	{
		for (int i = 0; i < (int)content.size(); i++)
		{
			if (i != activeid && content[i] != "")
			{
				DrawRect(x + Windowx, origin.y + draw, x + Windowx + size, y + Windowy + 18 + 17 + draw, SeccondColor);
				DrawRect(x + Windowx + 1, y + Windowy + 19 + draw, x + Windowx + size - 1, y + Windowy + 19 + 15 + draw, ThirdColor);
				RECT nameSize = GetTextSize(39, content[i]);
				Interfaces.pSurface->DrawT(origin.x + size / 2 - nameSize.right / 2, origin.y + 7.5f - nameSize.bottom / 2 + draw, CColor(255, 255, 255, 255), 39, false, content[i]);
				draw += 15;
			}
		}
	}
	return false;
}

void CComboBox::reset()
{
	content[100] = {};
}


CSlider::CSlider()
{
}

CSlider::CSlider(int xz, int yz, int sizez, float valuez, float minz, float maxz, char* ttag)
{
	x = xz;
	y = yz;
	size = sizez;
	value = valuez;
	max = maxz;
	min = minz;
	disvalue = value * (float(size) / float(max - min));
	tag = ttag;
}

bool CSlider::Draw(int Windowx, int Windowy, int add)
{
	Interfaces.pSurface->DrawT(x + Windowx, y + Windowy, CColor(255, 255, 255, 255), 39, false, tag);
	if (size == 0)
		return false;
	DrawRect(x + Windowx, y + Windowy + 4 + 18, x + Windowx + size, y + Windowy + 7 + 18, ThirdColor);
	DrawRect(x + Windowx + 1, y + Windowy + 5 + 18, x + Windowx + size - 1, y + Windowy + 6 + 18, FirstColor);
	DrawRect(x + Windowx + disvalue - 2, y + Windowy + 18, x + Windowx + disvalue + 2, y + Windowy + 12 + 18, ThirdColor);
	DrawRect(x + Windowx + disvalue - 1, y + Windowy + 1 + 18, x + Windowx + disvalue + 1, y + Windowy + 11 + 18, FirstColor);
	return false;
}

bool CSlider::Check(int Windowx, int Windowy, int add)
{
	POINT Mouse;
	GetCursorPos(&Mouse);
	ScreenToClient(GetForegroundWindow(), &Mouse);
	int MouseX = Mouse.x, MouseY = Mouse.y;
	bool change = false;
	if (IsClicked)
	{
		if (ClickedThisTick1)
			if (Mouse.x >= Windowx + x && Mouse.x <= Windowx + x + size)
				if (Mouse.y >= Windowy + y + 18 && Mouse.y <= y + Windowy + 18 + 8)
					washolding = true;
	}
	else
		washolding = false;
	if (washolding)
	{
		washolding = true;
		value = ((Mouse.x - (x + Windowx)) / (float(size) / float(max - min)));
		if (value > max)
			value = max;
		if (value < min)
			value = min;
		disvalue = Mouse.x - Windowx;
		if (disvalue < x)
			disvalue = x;
		if (disvalue > size + x)
			disvalue = size + x;
		disvalue -= x;
	}
	return false;
}