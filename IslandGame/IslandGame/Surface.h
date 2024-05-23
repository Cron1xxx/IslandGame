#pragma once
#include <Windows.h>
#include "Constants.h"
#include "Structures.h"
#include <atlstr.h>

class CSurface {
public:
	CSurface(SIZE size, HANDLE hConsoleOutput);
	~CSurface();
	void print();
	void printRegion(SHORT x, SHORT y, SHORT x2, SHORT y2);
	void fill(CHAR ch, WORD attr);
	void drawRect(_RECTL rect, EFrameType frameType, WORD attr);
	void drawRect(_RECTL rect, EFrameType frameType, WORD attr, CString text, EAlignment horizontalAlignment);
	void drawText(COORD pos, CString text, WORD attr);
	void drawChar(COORD pos, CHAR ch, WORD attr);
	void drawTransparentChar(COORD pos, CHAR ch, SHORT color);
private:
	SIZE mSize;
	CHAR_INFO mBuffer[WINDOW_HEIGHT][WINDOW_WIGHT];
	HANDLE mhConsoleOutput;
	COORD mBufferSize;
	COORD mBufferCoord;
	SMALL_RECT mRegion;
};

