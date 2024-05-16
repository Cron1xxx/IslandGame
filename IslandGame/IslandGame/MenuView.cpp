#include "MenuView.h"
#include <cstdio>

CMenuView::CMenuView(CGame* game, SIZE size) : CAbstractView(game, size){}

NEXT_VIEW_INFO CMenuView::show() {
	mExit = false;
	_RECTL rect;
	rect.bottom = 20;
	rect.right = 40;
	rect.top = 5;
	rect.left=6;
	mSurface->drawRect(rect);
	while (!mExit) {
		render();
		Sleep(500);
	}
	NEXT_VIEW_INFO nextViewInfo;
	nextViewInfo.mViewType = EViewType::TEST_VIEW;
	return nextViewInfo;
}

void CMenuView::render(){
	mSurface->print();
}

void CMenuView::keypressed(WORD keyCode) {
	printf("MenuView key %d pressed\n", keyCode);
	if (keyCode == 69) {
		mExit = true;
	}
}

