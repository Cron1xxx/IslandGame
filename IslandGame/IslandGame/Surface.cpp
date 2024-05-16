#include "Surface.h"
#include <iostream>
using namespace std;

CSurface::CSurface(SIZE size) : mSize(size){
	mSurface = new char*[mSize.cy];
	for (int i = 0; i < mSize.cy; i++) {
		mSurface[i] = new char[mSize.cx];
	}
}

CSurface::~CSurface() {
	for (int i = 0; i < mSize.cy; i++) {
		delete[] mSurface[i];
	}
	delete[] mSurface;
}

void CSurface::fill(char ch) {
	for (int i = 0; i < mSize.cy; i++ ) {
		for (int j = 0; j < mSize.cx; j++) {
			mSurface[i][j] = ch;
		}
	}
}

void CSurface::print() {
	system("cls");
	for (int i = 0; i < mSize.cy; i++) {
		for (int j = 0; j < mSize.cx; j++) {
			cout << mSurface[i][j];
		}
		cout << endl;
	}
}

void CSurface::drawRect(_RECTL rect) {
	int hight = rect.bottom - rect.top;
	int width = rect.right - rect.left;
	for ( int i = 0; i <= hight; i++ ) {
		if (i == 0 || i == hight - 1) {
			for (int j = 1; j < width; j++) {
				mSurface[i + rect.top][j + rect.left] = '-';
			}
		} else {
			mSurface[i + rect.top][rect.left] = '|';
			mSurface[i + rect.top][width + rect.left] = '|';
		}

	}
	mSurface[rect.top][rect.left] = '+';
	mSurface[rect.top][rect.right] = '+';
	mSurface[rect.bottom][rect.left] = '+';
	mSurface[rect.bottom][rect.right] = '+';
}
