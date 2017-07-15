#pragma once
#include "SDK.h"
#include "Globals.h"
#include "Config.h"
#include "Accessors.h"



class cMenu
{
public:
	void Paint();
	void OnClick();
	void OnRelease();
private:
	void DrawFrame(int x, int y, int w, int h);
	void DrawTab(const char* text, int x, int y, bool value);
	void DrawCheckbox(const char* text, int x, int y, bool value);
	void DrawButton(const char* text, int x, int y, int w, int h);
	void DrawSlider(const char* text, int x, int y, int min, int max);
	void DrawCheckbox(const char* text, int x, int y, int value);
	void DrawGroupBox(const char* text, int x, int y, int w, int h);
	void DrawTabs(int x, int y);
	void DrawTab(const char* text, int x, int y);
	void DrawCombobox();
};

extern cMenu* myMenu;