#pragma once
#include "CTestView.h"
#include <iostream>

using namespace std;

CTestView::CTestView(CGame* game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput) {
	
}

NEXT_VIEW_INFO CTestView::show() {
	mExit = false;
	while (!mExit) {

	}
	NEXT_VIEW_INFO nextViewInfo;
	nextViewInfo.mViewType = EViewType::MENU_VIEW;
	return nextViewInfo;
}

void CTestView::keypressed(WORD keyCode) {
	if (keyCode == 69) {
		mExit = true;
	}
}
