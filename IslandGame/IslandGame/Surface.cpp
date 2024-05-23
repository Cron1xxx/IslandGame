#include "Surface.h"
#include <iostream>
using namespace std;

CSurface::CSurface(SIZE size, HANDLE hConsoleOutput) : mSize(size){
	mhConsoleOutput = hConsoleOutput;
	mBufferSize = {(SHORT)mSize.cx, (SHORT)mSize.cy};
	mBufferCoord = {0, 0};
	mRegion = {0, 0, (SHORT)(mSize.cx - 1), (SHORT)(mSize.cy - 1)};
	for (int y = 0; y < mSize.cy; y++) {
		for (int x = 0; x < mSize.cx; x++) {
			mBuffer[y][x].Char.AsciiChar = ' ';
			mBuffer[y][x].Attributes = 0x07;
		}
	}
}

CSurface::~CSurface() {
}

void CSurface::fill(CHAR ch, WORD attr) {
	for (SHORT y = 0; y < mSize.cy; y++ ) {
		for (SHORT x = 0; x < mSize.cx; x++) {
			drawChar({x, y}, ch, attr);
		}
	}
}

void CSurface::print() {
	WriteConsoleOutputA(mhConsoleOutput, (CHAR_INFO*) mBuffer, mBufferSize, mBufferCoord, &mRegion);
}

void CSurface::printRegion(SHORT x, SHORT y, SHORT x2, SHORT y2) {
	SMALL_RECT region = { x, y, x + x2 - 1, y + y2 - 1 };
	WriteConsoleOutputA(mhConsoleOutput, (CHAR_INFO*)mBuffer, mBufferSize, { x, y }, &region);
}

void CSurface::drawRect(_RECTL rect, EFrameType frameType, WORD attr) {
	static const char doubleFrame[6] = {(char)201/*'╔'*/, (char)187/*'╗'*/, (char)200/*'╚'*/, (char)188/*'╝'*/, (char)205/*'═'*/, (char)186/*'║'*/};
	static const char singleFrame[6] = {(char)218/*'┌'*/, (char)191, (char)192, (char)217, (char)196, (char)179};
	static const char* pFrameChars;

	if (frameType == EFrameType::SINGLE) {
		pFrameChars = singleFrame;
	} else {
		pFrameChars = doubleFrame;
	}

	SHORT height = rect.bottom - rect.top;
	SHORT width = rect.right - rect.left;
	for ( SHORT y = 0; y <= height; y++ ) {
		if (y == 0 || y == height) {
			for (SHORT x = 1; x < width; x++) {
				drawChar({(SHORT)(x + rect.left), (SHORT)(y + rect.top)}, *(pFrameChars + 4), attr);  /*'═'*/
			}
		} else {
			drawChar({ (SHORT)(rect.left), (SHORT)(y + rect.top) }, *(pFrameChars + 5), attr); /*'║'*/
			drawChar({ (SHORT)(width + rect.left), (SHORT)(y + rect.top) }, *(pFrameChars + 5), attr); /*'║'*/
		}

	}
	drawChar({ (SHORT)(rect.left), (SHORT)(rect.top) }, *(pFrameChars), attr); /*'╔'*/
	drawChar({ (SHORT)(rect.right), (SHORT)(rect.top) }, *(pFrameChars + 1), attr); /*'╗'*/
	drawChar({ (SHORT)(rect.left), (SHORT)(rect.bottom) }, *(pFrameChars + 2), attr); /*'╚'*/ 
	drawChar({ (SHORT)(rect.right), (SHORT)(rect.bottom) }, *(pFrameChars + 3), attr); /*'╝'*/
}

void CSurface::drawRect(_RECTL rect, EFrameType frameType, WORD attr, CString text, EAlignment horizontalAlignment) {
	drawRect(rect, frameType, attr);
	auto rectWight = rect.right - rect.left;
	auto rectHeight = rect.bottom - rect.top; 
	auto textLength = text.GetLength();
	if (textLength > rectWight - 2) {
		text = text.Left(rectWight - 2);
		textLength = text.GetLength();
	}
	for (SHORT y = 1; y < rectHeight; y++) {
		for (SHORT x = 1; x < rectWight; x++) {
			drawChar({(SHORT)(rect.left + x), (SHORT)(rect.top + y)}, ' ', attr);
		}
	}
	if (horizontalAlignment == EAlignment::LEFT) {
		drawText({(SHORT)(rect.left + 1), (SHORT)(rect.top + 1)}, text, attr);
	} else if (horizontalAlignment == EAlignment::CENTER) {
		drawText({(SHORT)(rect.left + rectWight / 2 - textLength / 2), (SHORT)(rect.top + 1)}, text, attr);
	}

}

void CSurface::drawText(COORD pos, CString text, WORD attr) {
	for (SHORT i = 0; i < text.GetLength(); i++) {
		drawChar({(SHORT)(pos.X + i), pos.Y}, text[i], attr);
	}
}

void CSurface::drawChar(COORD pos, CHAR ch, WORD attr) {
	if (pos.X >= 0 && pos.X < mSize.cx && pos.Y >= 0 && pos.Y < mSize.cy) {
		mBuffer[pos.Y][pos.X].Char.AsciiChar = ch;
		mBuffer[pos.Y][pos.X].Attributes = attr;
	}
}

void CSurface::drawTransparentChar(COORD pos, CHAR ch, SHORT color) {
	if (pos.X >= 0 && pos.X < mSize.cx && pos.Y >= 0 && pos.Y < mSize.cy) {
		SHORT backgroundColor = mBuffer[pos.Y][pos.X].Attributes & 0xF0;
		drawChar(pos, ch, color | backgroundColor);
	}
}
