#pragma once

	extern HFont Meme;
	extern HFont ESP;
	extern HFont MemeRC;
	extern HFont Watermark;
	extern HFont MenuTitle;
	extern HFont MenuTab;
	extern HFont MenuPrimary;
	extern HFont ConsoleFont;
	extern HFont BombStuff;
	extern HFont Menufont;
	extern HFont HitIndicator;
	extern HFont Verdana;
	extern HFont Impact;



	extern void SetupFonts();
	extern void initializeFonts();
	extern void DrawString(HFont font, int x, int y, Color color, DWORD alignment, const char* msg, ...);
	extern void DrawStringUnicode(HFont font, int x, int y, Color color, bool bCenter, const wchar_t* msg, ...);
	extern void DrawRect(int x, int y, int w, int h, Color col);
	extern void FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a);
	extern void DrawStringA(HFont font, bool center, int x, int y, int r, int g, int b, int a, const char *input, ...);
	extern int getWidht(unsigned long font, const char* input);
	extern void DrawRectRainbow(int x, int y, int w, int h, float flSpeed, float &flRainbow);
	extern void DrawStringN(unsigned long font, bool shouldCenter, int x, int y, Color color, const char* text, ...);
	extern void DrawRectGradientVertical(int x, int y, int width, int height, Color color1, Color color2);
	extern void DrawRectGradientHorizontal(int x, int y, int width, int height, Color color1, Color color2);
	extern void drawOutlinedBox(int x, int y, int w, int h, Color color, Color colorOutline);
	extern void drawBar(int x, int y, int w, int h, Color color, float value);
	extern void DrawPixel(int x, int y, Color col);
	extern void DrawOutlinedRect(int x, int y, int w, int h, Color col);
	extern void DrawOutlinedCircle(int x, int y, int r, Color col);
	extern void DrawLine(int x0, int y0, int x1, int y1, Color col);
	extern void DrawCorner(int iX, int iY, int iWidth, int iHeight, bool bRight, bool bDown, Color colDraw);
	extern void DrawRoundedBox(int x, int y, int w, int h, int r, int v, Color col);
	extern void DrawPolygon(int count, Vertex_t* Vertexs, Color color);
	extern bool ScreenTransform(const Vector &point, Vector &screen);
	extern bool WorldToScreen(Vector &origin, Vector &screen);
	extern int GetStringWidth(HFont font, const char* msg, ...);
	extern void Draw3DBox(Vector* boxVectors, Color color);
	extern Vector2D GetTextSize(const wchar_t* text, HFont font);
	extern Vector2D GetTextSize(std::string text, HFont font);
	extern void DrawCircle(float x, float y, float r, float s, Color color);

