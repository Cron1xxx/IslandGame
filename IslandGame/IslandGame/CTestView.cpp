#pragma once
#include "CTestView.h"
#include <iostream>

using namespace std;

CTestView::CTestView(CGame* game) : CAbstractView(game) {
	
}

std::string CTestView::show() {
	mExit = false;
	while (!mExit) {

	}
	return "menu_view";
}

void CTestView::keypressed(WORD keyCode) {
	printf("TestView key %d pressed\n", keyCode);
	if (keyCode == 69) {
		mExit = true;
	}
}
