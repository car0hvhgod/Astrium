/*
Syn's AyyWare Framework 2015
*/

#pragma once

#include "Interfaces.h"

#include "Vector2D.h"

void Quad();


namespace Render
{
	void Initialise();

	// Normal Drawing functions
	void Clear(int x, int y, int w, int h, Color color);
	void FillRGBA(int x, int y, int w, int h, int r, int g, int b, int a);
	void Outline(int x, int y, int w, int h, Color color);
	void Rect2(int x, int y, int w, int h, int r, int g, int b, int a);
	void Line(int x, int y, int x2, int y2, Color color);

	void DrawRect(int x, int y, int w, int h, Color col);
	void DrawRectRainbow(int x, int y, int w, int h, float flSpeed, float &flRainbow);
	void PolyLine(int *x, int *y, int count, Color color);
	void Polygon(int count, Vertex_t* Vertexs, Color color);
	void PolygonOutline(int count, Vertex_t* Vertexs, Color color, Color colorLine);
	void PolyLine(int count, Vertex_t* Vertexs, Color colorLine);

	// Gradient Functions
	void GradientV(int x, int y, int w, int h, Color c1, Color c2);
	void GradientH(int x, int y, int w, int h, Color c1, Color c2);

	// Text functions
	namespace Fonts
	{
		extern DWORD Default;
		extern DWORD Menu;
		extern DWORD MenuBold;
		extern DWORD Untitled1;
		extern DWORD ESP;
		extern DWORD MenuText;
		extern DWORD MenuSymbols;
		extern DWORD Orion;
		extern DWORD Watermark;
		extern DWORD MenuMeme;
		extern DWORD Indicator;
		extern DWORD Tabs;
		extern DWORD Slider;
		extern DWORD HealthESP;
	};

	void Text(int x, int y, Color color, DWORD font, const char* text);
	void DrawCircle(float x, float y, float r, float s, Color color);
	void Textf(int x, int y, Color color, DWORD font, const char* fmt, ...);
	void Text(int x, int y, Color color, DWORD font, const wchar_t* text);
	RECT GetTextSize(DWORD font, const char* text);

	// Other rendering functions
	bool WorldToScreen(Vector &in, Vector &out);
	RECT GetViewport();
};

