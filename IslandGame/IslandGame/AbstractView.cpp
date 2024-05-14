#include "AbstractView.h"
#include <cstdio>

CAbstractView::CAbstractView(CGame* game, SIZE size) {
	mpGame = game;
	mpSize = size;
}

