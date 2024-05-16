#include "AbstractView.h"
#include <cstdio>

CAbstractView::CAbstractView(CGame* game, SIZE size) {
	mpGame = game;
	mpSize = size;
	mSurface = new CSurface(size);
	mSurface->fill(' ');
}

CAbstractView::~CAbstractView() {
	delete mSurface;
}

