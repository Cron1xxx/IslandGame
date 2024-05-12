#include "MenuView.h"
#include <cstdio>

CMenuView::CMenuView(CGame* game) : CAbstractView(game){}

std::string CMenuView::show() {
	mExit = false;
	while (!mExit) {
	}
	return "test_view";
}

void CMenuView::keypressed(WORD keyCode) {
	printf("MenuView key %d pressed\n", keyCode);
	if (keyCode == 69) {
		mExit = true;
	}
}
