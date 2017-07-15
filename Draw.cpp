#include "SDK.h"

HFont Meme;
HFont ESP;
HFont MemeRC;
HFont Watermark;
HFont ConsoleFont;
HFont BombStuff;
HFont Menufont;
HFont HitIndicator;
HFont Verdana;
HFont Impact;

void SetupFonts()
{
	Surface->SetFontGlyphSet(Meme = Surface->Create_Font(), XorStr("Comic Sans MS"), 30, FW_DONTCARE, NULL, NULL, FONTFLAG_ANTIALIAS);
	Surface->SetFontGlyphSet(MemeRC = Surface->Create_Font(), XorStr("Comic Sans MS"), 40, FW_DONTCARE, NULL, NULL, FONTFLAG_ANTIALIAS);
	Surface->SetFontGlyphSet(ESP = Surface->Create_Font(), XorStr("Tahoma"), 13, 700, NULL, NULL, FONTFLAG_DROPSHADOW);
	Surface->SetFontGlyphSet(BombStuff = Surface->Create_Font(), XorStr("Tahoma"), 20, 450, NULL, NULL, FONTFLAG_OUTLINE);
	Surface->SetFontGlyphSet(HitIndicator = Surface->Create_Font(), XorStr("coolvetica"), 21, 800, NULL, NULL, FONTFLAG_OUTLINE);
	Surface->SetFontGlyphSet(Watermark = Surface->Create_Font(), XorStr("Arial Bold"), 12, FW_DONTCARE, NULL, NULL, FONTFLAG_OUTLINE);
	Surface->SetFontGlyphSet(Menufont = Surface->Create_Font(), XorStr("Tahoma"), 13, FW_DONTCARE, NULL, NULL, FONTFLAG_OUTLINE);
	Surface->SetFontGlyphSet(Verdana = Surface->Create_Font(), XorStr("Verdana"), 12, FW_DONTCARE, NULL, NULL, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
	Surface->SetFontGlyphSet(Impact = Surface->Create_Font(), XorStr("Impact"), 34, FW_DONTCARE, NULL, NULL, FONTFLAG_ANTIALIAS | FONTFLAG_DROPSHADOW);
}

void resetFonts()
{
	Meme = 0, ESP = 0;
	MemeRC = 0;
	Watermark = 0;
	ConsoleFont = 0;
	BombStuff = 0;
	Menufont = 0;
}

void initializeFonts()
{
	resetFonts();
	Surface->SetFontGlyphSet(Meme = Surface->Create_Font(), XorStr("Comic Sans MS"), 30, FW_DONTCARE, NULL, NULL, FONTFLAG_ANTIALIAS);
	Surface->SetFontGlyphSet(MemeRC = Surface->Create_Font(), XorStr("Comic Sans MS"), 40, FW_DONTCARE, NULL, NULL, FONTFLAG_ANTIALIAS);
	Surface->SetFontGlyphSet(ESP = Surface->Create_Font(), XorStr("Arial Regular"), 15, 450, NULL, NULL, FONTFLAG_OUTLINE);
	Surface->SetFontGlyphSet(BombStuff = Surface->Create_Font(), XorStr("Tahoma"), 20, 450, NULL, NULL, FONTFLAG_OUTLINE);
	Surface->SetFontGlyphSet(Watermark = Surface->Create_Font(), XorStr("Arial Bold"), 12, FW_DONTCARE, NULL, NULL, FONTFLAG_OUTLINE);
	Surface->SetFontGlyphSet(Menufont = Surface->Create_Font(), XorStr("Tahoma"), 13, FW_DONTCARE, NULL, NULL, FONTFLAG_OUTLINE);
}

std::wstring stringToWide(const std::string& text)
{
	std::wstring wide(text.length(), L' ');
	std::copy(text.begin(), text.end(), wide.begin());

	return wide;
}

int getWidht(unsigned long font, const char* input)
{
	INT iWide = 0;
	INT iTall = 0;
	INT iBufSize = MultiByteToWideChar(CP_UTF8, 0x0, input, -1, NULL, 0);

	wchar_t* pszUnicode = new wchar_t[iBufSize];

	MultiByteToWideChar(CP_UTF8, 0x0, input, -1, pszUnicode, iBufSize);

	Surface->GetTextSize(font, pszUnicode, iWide, iTall);

	delete[] pszUnicode;

	return iWide;
}

std::wstring getWide(const std::string& text)
{
	std::wstring wide(text.length(), L' ');
	std::copy(text.begin(), text.end(), wide.begin());

	return wide;
}

void DrawString(HFont font, int x, int y, Color color, DWORD alignment, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor(r, g, b, a);

	int width, height;
	Surface->GetTextSize(font, wbuf, width, height);

	if (alignment & FONT_RIGHT)
		x -= width;
	if (alignment & FONT_CENTER)
		x -= width / 2;

	Surface->DrawSetTextFont(font);
	Surface->DrawSetTextColor(r, g, b, a);
	Surface->DrawSetTextPos(x, y - height / 2);
	Surface->DrawPrintText(wbuf, wcslen(wbuf));
}

void DrawStringN(unsigned long font, bool shouldCenter, int x, int y, Color color, const char* text, ...)
{
	if (!text)
		return;

	char buffer[MAX_PATH];

	vsprintf_s(buffer, text, (char*)&text + _INTSIZEOF(text));

	if (shouldCenter)
		x -= getWidht(font, buffer) / 2;

	Surface->DrawSetTextColor(color.r(), color.g(), color.b(), color.a());
	Surface->DrawSetTextFont(font);
	Surface->DrawSetTextPos(x, y);

	std::wstring wide = getWide(std::string(buffer));
	Surface->DrawPrintText(wide.c_str(), wide.length());
}

Vector2D GetTextSize(std::string text, HFont font)
{
	int x = 0;
	int y = 0;

	Surface->GetTextSize(font, std::wstring(text.begin(), text.end()).c_str(), x, y);

	return Vector2D(x, y);
}

Vector2D GetTextSize(const wchar_t* text, HFont font)
{
	int x = 0;
	int y = 0;

	Surface->GetTextSize(font, text, x, y);

	return Vector2D(x, y);
}

void DrawStringUnicode(HFont font, int x, int y, Color color, bool bCenter, const wchar_t* msg, ...)
{
	int r = 255, g = 255, b = 255, a = 255;
	color.GetColor(r, g, b, a);

	int iWidth, iHeight;

	Surface->GetTextSize(font, msg, iWidth, iHeight);
	Surface->DrawSetTextFont(font);
	Surface->DrawSetTextColor(r, g, b, a);
	Surface->DrawSetTextPos(!bCenter ? x : x - iWidth / 2, y - iHeight / 2);
	Surface->DrawPrintText(msg, wcslen(msg));
}

void DrawRect(int x, int y, int w, int h, Color col)
{
	Surface->DrawSetColor(col);
	Surface->DrawFilledRect(x, y, x + w, y + h);
}

void DrawRectRainbow(int x, int y, int width, int height, float flSpeed, float &flRainbow)
{
	Color colColor(0, 0, 0);

	flRainbow += flSpeed;
	if (flRainbow > 1.f) flRainbow = 0.f;

	for (int i = 0; i < width; i++)
	{
		float hue = (1.f / (float)width) * i;
		hue -= flRainbow;
		if (hue < 0.f) hue += 1.f;

		Color colRainbow = colColor.FromHSB(hue, 1.f, 1.f);
		DrawRect(x + i, y, 1, height, colRainbow);
	}
}

void DrawStringA(HFont font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...)
{
	CHAR szBuffer[MAX_PATH];

	if (!input)
		return;

	vsprintf(szBuffer, input, (char*)&input + _INTSIZEOF(input));

	if (center)
		x -= getWidht(font, szBuffer) / 2;

	Surface->DrawSetTextColor(Color(r, g, b, a));
	Surface->DrawSetTextFont(font);
	Surface->DrawSetTextPos(x, y);
	std::wstring wide = stringToWide(std::string(szBuffer));
	Surface->DrawPrintText(wide.c_str(), wide.length());
}

void FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a)
{
	Surface->DrawSetColor(r, g, b, a);
	Surface->DrawFilledRect(x, y, x + w, y + h);
}

void DrawRectGradientVertical(int x, int y, int width, int height, Color color1, Color color2)
{
	DrawRect(x, y, width, height, color1);
	BYTE first = color2.r();
	BYTE second = color2.g();
	BYTE third = color2.b();
	for (int i = 0; i < height; i++)
	{
		float fi = i, fh = height;
		float a = fi / fh;
		DWORD ia = a * 255;
		DrawRect(x, y + i, width, 1, Color(first, second, third, ia));
	}
}

void DrawRectGradientHorizontal(int x, int y, int width, int height, Color color1, Color color2)
{
	float flDifferenceR = (float)(color2.r() - color1.r()) / (float)width;
	float flDifferenceG = (float)(color2.g() - color1.g()) / (float)width;
	float flDifferenceB = (float)(color2.b() - color1.b()) / (float)width;

	for (float i = 0.f; i < width; i++)
	{
		Color colGradient = Color(color1.r() + (flDifferenceR * i), color1.g() + (flDifferenceG * i), color1.b() + (flDifferenceB * i), color1.a());
		DrawRect(x + i, y, 1, height, colGradient);
	}
}

void DrawPixel(int x, int y, Color col)
{
	Surface->DrawSetColor(col);
	Surface->DrawFilledRect(x, y, x + 1, y + 1);
}

void DrawOutlinedRect(int x, int y, int w, int h, Color col)
{
	Surface->DrawSetColor(col);
	Surface->DrawOutlinedRect(x, y, x + w, y + h);
}


void DrawOutlinedCircle(int x, int y, int r, Color col)
{
	Surface->DrawSetColor(col);
	Surface->DrawOutlinedCircle(x, y, r, 1);
}

void DrawLine(int x0, int y0, int x1, int y1, Color col)
{
	Surface->DrawSetColor(col);
	Surface->DrawLine(x0, y0, x1, y1);
}

void DrawCorner(int iX, int iY, int iWidth, int iHeight, bool bRight, bool bDown, Color colDraw)
{
	int iRealX = bRight ? iX - iWidth : iX;
	int iRealY = bDown ? iY - iHeight : iY;

	if (bDown && bRight)
		iWidth = iWidth + 1;

	DrawRect(iRealX, iY, iWidth, 1, colDraw);
	DrawRect(iX, iRealY, 1, iHeight, colDraw);

	DrawRect(iRealX, bDown ? iY + 1 : iY - 1, !bDown && bRight ? iWidth + 1 : iWidth, 1, Color(0, 0, 0, 255));
	DrawRect(bRight ? iX + 1 : iX - 1, bDown ? iRealY : iRealY - 1, 1, bDown ? iHeight + 2 : iHeight + 1, Color(0, 0, 0, 255));
}

void drawOutlinedBox(int x, int y, int w, int h, Color color, Color colorOutline)
{
	DrawOutlinedRect(x, y, w, h, color);

	Surface->DrawSetColor(colorOutline.r(), colorOutline.g(), colorOutline.b(), colorOutline.a());
	Surface->DrawOutlinedRect(x + 1, y + 1, x + w - 1, y + h - 1);
	Surface->DrawOutlinedRect(x - 1, y - 1, x + w + 1, y + h + 1);
}

void drawBar(int x, int y, int w, int h, Color color, float value)
{
	x -= w / 2;
	y -= h / 2;

	DrawRect(x, y, w, h + 1, Color(0, 0, 0));

	UINT height = (UINT)(((h + 1) * value) / 100);
	DrawRect(x + 1, y + 1, w - 2, height - 2, color);
}

void DrawPolygon(int count, Vertex_t* Vertexs, Color color)
{
	static int Texture = Surface->CreateNewTextureID(true);
	unsigned char buffer[4] = { 255, 255, 255, 255 };

	Surface->DrawSetTextureRGBA(Texture, buffer, 1, 1);
	Surface->DrawSetColor(color);
	Surface->DrawSetTexture(Texture);

	Surface->DrawTexturedPolygon(count, Vertexs);
}

void DrawRoundedBox(int x, int y, int w, int h, int r, int v, Color col)
{
	std::vector<Vertex_t> p;
	for (int _i = 0; _i < 3; _i++)
	{
		int _x = x + (_i < 2 && r || w - r);
		int _y = y + (_i % 3 > 0 && r || h - r);
		for (int i = 0; i < v; i++)
		{
			int a = RAD2DEG((i / v) * -90 - _i * 90);
			p.push_back(Vertex_t(Vector2D(_x + sin(a) * r, _y + cos(a) * r)));
		}
	}

	DrawPolygon(4 * (v + 1), &p[0], col);
}

bool ScreenTransform(const Vector &point, Vector &screen) // tots not pasted
{
	float w;
	const VMatrix &worldToScreen = Engine->WorldToScreenMatrix();

	screen.x = worldToScreen[0][0] * point[0] + worldToScreen[0][1] * point[1] + worldToScreen[0][2] * point[2] + worldToScreen[0][3];
	screen.y = worldToScreen[1][0] * point[0] + worldToScreen[1][1] * point[1] + worldToScreen[1][2] * point[2] + worldToScreen[1][3];
	w = worldToScreen[3][0] * point[0] + worldToScreen[3][1] * point[1] + worldToScreen[3][2] * point[2] + worldToScreen[3][3];
	screen.z = 0.0f;

	bool behind = false;

	if (w < 0.001f)
	{
		behind = true;
		screen.x *= 100000;
		screen.y *= 100000;
	}
	else
	{
		behind = false;
		float invw = 1.0f / w;
		screen.x *= invw;
		screen.y *= invw;
	}

	return behind;
}

bool WorldToScreen(Vector& vOrigin, Vector& vScreen)
{
	int screenWidth, screenHeight;
	Engine->GetScreenSize(screenWidth, screenHeight);
	const VMatrix& worldToScreen = Engine->WorldToScreenMatrix();

	float w = worldToScreen[3][0] * vOrigin[0] + worldToScreen[3][1] * vOrigin[1] + worldToScreen[3][2] * vOrigin[2] + worldToScreen[3][3];
	vScreen.z = 0;
	if (w > 0.01)
	{
		float inverseWidth = 1 / w;
		vScreen.x = (screenWidth / 2) + (0.5 * ((worldToScreen[0][0] * vOrigin[0] + worldToScreen[0][1] * vOrigin[1] + worldToScreen[0][2] * vOrigin[2] + worldToScreen[0][3]) * inverseWidth) * screenWidth + 0.5);
		vScreen.y = (screenHeight / 2) - (0.5 * ((worldToScreen[1][0] * vOrigin[0] + worldToScreen[1][1] * vOrigin[1] + worldToScreen[1][2] * vOrigin[2] + worldToScreen[1][3]) * inverseWidth) * screenHeight + 0.5);
		return true;
	}
	return false;
}

int GetStringWidth(HFont font, const char* msg, ...)
{
	va_list va_alist;
	char buf[1024];
	va_start(va_alist, msg);
	_vsnprintf(buf, sizeof(buf), msg, va_alist);
	va_end(va_alist);
	wchar_t wbuf[1024];
	MultiByteToWideChar(CP_UTF8, 0, buf, 256, wbuf, 256);

	int iWidth, iHeight;

	Surface->GetTextSize(font, wbuf, iWidth, iHeight);

	return iWidth;
}

void Draw3DBox(Vector* boxVectors, Color color)
{
	Vector boxVectors0, boxVectors1, boxVectors2, boxVectors3,
		boxVectors4, boxVectors5, boxVectors6, boxVectors7;


	if (WorldToScreen(boxVectors[0], boxVectors0) &&
		WorldToScreen(boxVectors[1], boxVectors1) &&
		WorldToScreen(boxVectors[2], boxVectors2) &&
		WorldToScreen(boxVectors[3], boxVectors3) &&
		WorldToScreen(boxVectors[4], boxVectors4) &&
		WorldToScreen(boxVectors[5], boxVectors5) &&
		WorldToScreen(boxVectors[6], boxVectors6) &&
		WorldToScreen(boxVectors[7], boxVectors7))
	{

		/*
		.+--5---+
		.8 4    6'|
		+--7---+'  11
		9   |  10  |
		|  ,+--|3--+
		|.0    | 2'
		+--1---+'
		*/

		Vector2D lines[12][2];
		//bottom of box
		lines[0][0] = { boxVectors0.x, boxVectors0.y };
		lines[0][1] = { boxVectors1.x, boxVectors1.y };
		lines[1][0] = { boxVectors1.x, boxVectors1.y };
		lines[1][1] = { boxVectors2.x, boxVectors2.y };
		lines[2][0] = { boxVectors2.x, boxVectors2.y };
		lines[2][1] = { boxVectors3.x, boxVectors3.y };
		lines[3][0] = { boxVectors3.x, boxVectors3.y };
		lines[3][1] = { boxVectors0.x, boxVectors0.y };

		lines[4][0] = { boxVectors0.x, boxVectors0.y };
		lines[4][1] = { boxVectors6.x, boxVectors6.y };

		// top of box
		lines[5][0] = { boxVectors6.x, boxVectors6.y };
		lines[5][1] = { boxVectors5.x, boxVectors5.y };
		lines[6][0] = { boxVectors5.x, boxVectors5.y };
		lines[6][1] = { boxVectors4.x, boxVectors4.y };
		lines[7][0] = { boxVectors4.x, boxVectors4.y };
		lines[7][1] = { boxVectors7.x, boxVectors7.y };
		lines[8][0] = { boxVectors7.x, boxVectors7.y };
		lines[8][1] = { boxVectors6.x, boxVectors6.y };


		lines[9][0] = { boxVectors5.x, boxVectors5.y };
		lines[9][1] = { boxVectors1.x, boxVectors1.y };

		lines[10][0] = { boxVectors4.x, boxVectors4.y };
		lines[10][1] = { boxVectors2.x, boxVectors2.y };

		lines[11][0] = { boxVectors7.x, boxVectors7.y };
		lines[11][1] = { boxVectors3.x, boxVectors3.y };

		for (int i = 0; i < 12; i++)
		{
			DrawLine(lines[i][0].x, lines[i][0].y, lines[i][1].x, lines[i][1].y, color);
		}
	}
}

void DrawCircle(float x, float y, float r, float s, Color color)
{
	float Step = M_PI * 2.0 / s;
	for (float a = 0; a < (M_PI*2.0); a += Step)
	{
		float x1 = r * cos(a) + x;
		float y1 = r * sin(a) + y;
		float x2 = r * cos(a + Step) + x;
		float y2 = r * sin(a + Step) + y;

		DrawLine(x1, y1, x2, y2, color);
	}
}
