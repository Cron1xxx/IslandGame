#include "Surface.h"
#include <iostream>
using namespace std;

CSurface::CSurface(SIZE size, HANDLE hConsoleOutput) : mSize(size){
	mhConsoleOutput = hConsoleOutput;
	mBufferSize = {(SHORT)mSize.cx, (SHORT)mSize.cy};
	mBufferCoord = {0, 0};
	mRegion = {0, 0, (SHORT)mSize.cx - 1, (SHORT)mSize.cy - 1};
	for (int y = 0; y < mSize.cy; y++) {
		for (int x = 0; x < mSize.cx; x++) {
			mBuffer[y][x].Char.AsciiChar = ' ';
			mBuffer[y][x].Attributes = 0x07;
		}
	}
}

CSurface::~CSurface() {
}

void CSurface::fill(CHAR ch) {
	for (int i = 0; i < mSize.cy; i++ ) {
		for (int j = 0; j < mSize.cx; j++) {
			mBuffer[i][j].Char.AsciiChar = ch;
		}
	}
}

void CSurface::print() {
	WriteConsoleOutputA(mhConsoleOutput, (CHAR_INFO*) mBuffer, mBufferSize, mBufferCoord, &mRegion);
}

void CSurface::drawRect(_RECTL rect) {
	int height = rect.bottom - rect.top;
	int width = rect.right - rect.left;
	for ( int y = 0; y <= height; y++ ) {
		if (y == 0 || y == height) {
			for (int x = 1; x < width; x++) {
				mBuffer[y + rect.top][x + rect.left].Char.AsciiChar = '-';
			}
		} else {
			mBuffer[y + rect.top][rect.left].Char.AsciiChar = '|';
			mBuffer[y + rect.top][width + rect.left].Char.AsciiChar = '|';
		}

	}
	mBuffer[rect.top][rect.left].Char.AsciiChar = '+';
	mBuffer[rect.top][rect.right].Char.AsciiChar = '+';
	mBuffer[rect.bottom][rect.left].Char.AsciiChar = '+';
	mBuffer[rect.bottom][rect.right].Char.AsciiChar = '+';
}
