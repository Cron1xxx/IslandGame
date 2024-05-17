#include "AbstractView.h"
#include <cstdio>

CAbstractView::CAbstractView(CGame* game, SIZE size, HANDLE hConsoleOutput) {
	mpGame = game;
	mpSize = size;
	mSurface = new CSurface(size, hConsoleOutput);
	mSurface->fill(' ');
}

CAbstractView::~CAbstractView() {
	delete mSurface;
}

