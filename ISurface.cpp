#include "sdk.h"

void ISurface::DrawSetColor(int r, int g, int b, int a)
{
	typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
	return GetVFunc<OriginalFn>(this, 15)(this, r, g, b, a);
}

void ISurface::DrawSetColor(Color col)
{
	typedef void(__thiscall* OriginalFn)(void*, Color);
	return GetVFunc<OriginalFn>(this, 14)(this, col);
}

void ISurface::DrawFilledRect(int x0, int y0, int x1, int y1)
{ 
	typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
	return GetVFunc<OriginalFn>(this, 16)(this, x0, y0, x1, y1);
}

void ISurface::DrawOutlinedRect(int x0, int y0, int x1, int y1)
{ 
	typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
	return GetVFunc<OriginalFn>(this, 18)(this, x0, y0, x1, y1);
}

void ISurface::DrawLine(int x0, int y0, int x1, int y1)
{
	typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
	return GetVFunc<OriginalFn>(this, 19)(this, x0, y0, x1, y1);
}

void ISurface::DrawPolyLine(int *px, int *py, int numPoints) 
{
	typedef void(__thiscall* OriginalFn)(void*, int*, int*, int);
	return GetVFunc<OriginalFn>(this, 20)(this, px, py, numPoints);
}

void ISurface::DrawSetTextFont(HFont font)
{ 
	typedef void(__thiscall* OriginalFn)(void*, HFont);
	return GetVFunc<OriginalFn>(this, 23)(this, font);
}

void ISurface::DrawSetTextColor(int r, int g, int b, int a) 
{
	typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
	return GetVFunc<OriginalFn>(this, 25)(this, r, g, b, a);
}

void ISurface::DrawSetTextColor(Color col)
{
	typedef void(__thiscall* OriginalFn)(void*, Color);
	return GetVFunc<OriginalFn>(this, 24)(this, col);
}

void ISurface::DrawSetTextPos(int x, int y) 
{ 
	typedef void(__thiscall* OriginalFn)(void*, int, int);
	return GetVFunc<OriginalFn>(this, 26)(this, x, y);
}

void ISurface::DrawPrintText(const wchar_t *text, int textLen, FontDrawType_t drawType)
{ 
	typedef void(__thiscall* OriginalFn)(void*, const wchar_t*, int, FontDrawType_t);
	return GetVFunc<OriginalFn>(this, 28)(this, text, textLen, drawType);
}

void ISurface::DrawSetTextureRGBA(int id, const unsigned char *rgba, int wide, int tall)
{
	typedef void(__thiscall* OriginalFn)(void*, int, const unsigned char*, int, int);
	return GetVFunc<OriginalFn>(this, 37)(this, id, rgba, wide, tall);
}

void ISurface::DrawSetTexture(int id) 
{
	typedef void(__thiscall* OriginalFn)(void*, int);
	return GetVFunc<OriginalFn>(this, 38)(this, id);
}

int	ISurface::CreateNewTextureID(bool procedural)
{
	typedef int(__thiscall* OriginalFn)(void*, bool);
	return GetVFunc<OriginalFn>(this, 43)(this, procedural);
}

HFont ISurface::Create_Font()
{
	typedef HFont(__thiscall* OriginalFn)(void*);
	return GetVFunc<OriginalFn>(this, 71)(this);
}

bool ISurface::SetFontGlyphSet(HFont font, const char *windowsFontName, int tall, int weight, int blur, int scanlines, int flags, int nRangeMin, int nRangeMax)
{
	typedef bool(__thiscall* OriginalFn)(void*, HFont, const char*, int, int, int, int, int, int, int);
	return GetVFunc<OriginalFn>(this, 72)(this, font, windowsFontName, tall, weight, blur, scanlines, flags, nRangeMin, nRangeMax);
}

void ISurface::GetTextSize(HFont font, const wchar_t *text, int &wide, int &tall)
{
	typedef void(__thiscall* OriginalFn)(void*, HFont, const wchar_t*, int&, int&);
	return GetVFunc<OriginalFn>(this, 79)(this, font, text, wide, tall);
}

void ISurface::DrawT(int X, int Y, Color Color, int Font, bool Center, char* _Input, ...)
{
	int apple = 0;
	/* set up buffer */
	char Buffer[1024] = { '\0' };

	/* set up varargs*/
	va_list Args;

	va_start(Args, _Input);
	vsprintf_s(Buffer, _Input, Args);
	va_end(Args);

	size_t Size = strlen(Buffer) + 1;

	/* set up widebuffer*/
	wchar_t* WideBuffer = new wchar_t[Size];

	/* char -> wchar */
	mbstowcs_s(0, WideBuffer, Size, Buffer, Size - 1);

	/* check center */
	int Width = 0, Height = 0;

	if (Center)
	{
		GetTextSize(Font, WideBuffer, Width, Height);
	}

	/* call and draw*/
	DrawSetTextColor(Color._color[0], Color._color[1], Color._color[2], Color._color[3]);
	DrawSetTextFont(Font);
	DrawSetTextPos(X - (Width / 2), Y);
	DrawPrintText(WideBuffer, wcslen(WideBuffer));

	return;
}

void ISurface::DrawOutlinedCircle(int x, int y, int radius, int segments) 
{ 
	typedef void(__thiscall* OriginalFn)(void*, int, int, int, int);
	return GetVFunc<OriginalFn>(this, 103)(this, x, y, radius, segments);
}

void ISurface::DrawTexturedPolygon(int n, Vertex_t *pVertice, bool bClipVertices)
{
	typedef void(__thiscall* OriginalFn)(void*, int, Vertex_t*, bool);
	return GetVFunc<OriginalFn>(this, 106)(this, n, pVertice, bClipVertices);
}

int ISurface::GetFontTall(HFont font)
{
	typedef int(__thiscall* OriginalFn)(void*, HFont);
	return GetVFunc<OriginalFn>(this, 74)(this, font);
}

void ISurface::GetCursorPos(int& x, int& y)
{
	typedef void(__thiscall* OriginalFn)(void*, int &, int &);
	return GetVFunc<OriginalFn>(this, 100)(this, x, y);
}
