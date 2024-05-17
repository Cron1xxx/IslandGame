#include "MenuView.h"
#include <cstdio>

CMenuView::CMenuView(CGame* game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput){}

NEXT_VIEW_INFO CMenuView::show() {
	mExit = false;

	mSurface->drawRect({6, 1, 20, 4});
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
	if (keyCode == 69) {
		mExit = true;
	}
}

