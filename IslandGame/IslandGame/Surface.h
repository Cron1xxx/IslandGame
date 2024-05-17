#pragma once
#include <Windows.h>
#include "Constants.h"

class CSurface {
public:
	CSurface(SIZE size, HANDLE hConsoleOutput);
	~CSurface();
	void print();
	void fill(CHAR ch);
	void drawRect(_RECTL);
private:
	SIZE mSize;
	CHAR_INFO mBuffer[WINDOW_HEIGHT][WINDOW_WIGHT];
	HANDLE mhConsoleOutput;
	COORD mBufferSize;
	COORD mBufferCoord;
	SMALL_RECT mRegion;
};

