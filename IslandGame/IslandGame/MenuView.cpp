#include "MenuView.h"
#include <cstdio>

CMenuView::CMenuView(CGame* game, SIZE size) : CAbstractView(game, size){}

NEXT_VIEW_INFO CMenuView::show() {
	mExit = false;
	while (!mExit) {
		render();
	}
	NEXT_VIEW_INFO nextViewInfo;
	nextViewInfo.mViewType = EViewType::TEST_VIEW;
	return nextViewInfo;
}

void CMenuView::render(){
	system("cls");
}

void CMenuView::keypressed(WORD keyCode) {
	printf("MenuView key %d pressed\n", keyCode);
	if (keyCode == 69) {
		mExit = true;
	}
}

