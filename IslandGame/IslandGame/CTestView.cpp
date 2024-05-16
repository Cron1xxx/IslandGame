#pragma once
#include "CTestView.h"
#include <iostream>

using namespace std;

CTestView::CTestView(CGame* game, SIZE size) : CAbstractView(game, size) {
	
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
	printf("TestView key %d pressed\n", keyCode);
	if (keyCode == 69) {
		mExit = true;
	}
}
