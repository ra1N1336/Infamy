#pragma once
#include "sdk.h"

inline RECT GetTextSize(DWORD font, const char* text)
{
	size_t origsize = strlen(text) + 1;
	const size_t newsize = 100;
	size_t convertedChars = 0;
	wchar_t wcstring[newsize];
	mbstowcs_s(&convertedChars, wcstring, origsize, text, _TRUNCATE);

	RECT rect; int x, y;
    Surface->GetTextSize(font, wcstring, x, y);
	rect.left = x; rect.bottom = y;
	rect.right = x;
	return rect;
}


inline bool IsMousePressed()
{
	return (GetAsyncKeyState(0x01));
}

#define FirstColor Color(4, 244, 243, 255)
#define SeccondColor Color(150,150,150, 255)
#define ThirdColor Color(45,45,45, 255)

class CControl
{
public:
	CControl() {}
	bool active = false;
	virtual bool Draw(int x, int y, int add) = 0;
	virtual bool Check(int x, int y, int add) = 0;
};

class CTab : public CControl
{
	std::vector<CControl*> controls;
public:
	CTab() {}
	virtual bool Draw(int Windowx, int Windowy, int add);
	virtual bool Check(int Windowx, int Windowy, int add);
	void AddControl(CControl* control);
};

class CWindow : public CControl
{
	std::vector<CControl*> tabs;
	char* name = "";
	bool holdingmenu = false;
public:
	int x = 0, y = 0;
	CWindow(int x, int y, char* name);
	virtual bool Draw(int Windowx, int Windowy, int add);
	virtual bool Check(int Windowx, int Windowy, int add);
	void AddTab(CControl *tab);
};

class CMenu : public CControl
{
	std::vector<CControl*> windows;
public:
	CMenu() {}
	int x = 0, y = 0;
	virtual bool Draw(int Windowx, int Windowy, int add);
	virtual bool Check(int Windowx, int Windowy, int add);
	void AddWindow(CControl *window);
};

class CKey : public CControl {
	int keycode = NULL;
	int x, y, size;
	char* text = "";
public:
	CKey(int nx, int ny, int nsize, char* text);
	virtual bool Draw(int Windowx, int Windowy, int add);
	virtual bool Check(int Windowx, int Windowy, int add);
};

class CButton : public CControl
{
	int x, y, size;
	char* text = "";
public:
	CButton(int nx, int ny, int nsize, char* text);
	virtual bool Draw(int Windowx, int Windowy, int add);
	virtual bool Check(int Windowx, int Windowy, int add);
};

class CComboBox : public CControl
{
public:
	int x = 0;
	int y = 0;
	int size = 0;
	char* tag = "";

	CComboBox();

	CComboBox(int xz, int yz, int sizez, char* ttag);

	int count = 0;
	int activeid = 0;
	std::vector<char*> content = {};

	void addContent(char* ttag);
	virtual bool Check(int Windowx, int Windowy, int add);
	virtual bool Draw(int Windowx, int Windowy, int add);
	void reset();
};

class CSlider : public CControl
{
public:
	int x = 0;
	int y = 0;
	int size = 0;
	float max = 0;
	float min = 0;
	float disvalue = 0;
	float value = 0;
	bool washolding = false;
	char* tag = "";


	CSlider();

	CSlider(int xz, int yz, int sizez, float valuez, float minz, float maxz, char* ttag);

	virtual bool Check(int Windowx, int Windowy, int add);
	virtual bool Draw(int Windowx, int Windowy, int add);
};