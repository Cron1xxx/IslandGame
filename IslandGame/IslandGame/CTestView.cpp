#pragma once
#include "CTestView.h"
#include <iostream>

using namespace std;

CTestView::CTestView(CFrame* frame) {
	mpFrame = frame;
}

void CTestView::show() {
	cout<<"I'm test view!!!"<<endl;
}

void CTestView::keypressed(WORD keyCode) {
}
