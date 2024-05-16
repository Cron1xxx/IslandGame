#pragma once

#include "Frame.h"
#include <thread>
#include <windows.h>
#include "CTestView.h"
#include "MenuView.h"



CFrame::CFrame() {
	SIZE size;
	size.cx = 120;
	size.cy = 40;
	mpKeyboardHandler = new CKeyboardHandler();
	mpMenuView = new CMenuView(mpGame, size);
	mpTestView = new CTestView(mpGame, size);
}

void CFrame::run() {
	mKeyboardHandlingThread = new thread(&CKeyboardHandler::run, mpKeyboardHandler);
	NEXT_VIEW_INFO nextView;
	nextView.mViewType = EViewType::MENU_VIEW;
	setActiveView(nextView);
	
	while (true) {
		nextView = mpActiveView->show();
		setActiveView(nextView);
	}
}


void CFrame::setActiveView(NEXT_VIEW_INFO nextViewInfo) {
	if (nextViewInfo.mViewType == EViewType::MENU_VIEW) {
		mpKeyboardHandler->setListener(mpMenuView);
		mpActiveView = mpMenuView;
		
	} else if (nextViewInfo.mViewType == EViewType::TEST_VIEW) {
		mpKeyboardHandler->setListener(mpTestView);
		mpActiveView = mpTestView;
	};
}

CFrame::~CFrame() {
	if (mKeyboardHandlingThread) {
		mKeyboardHandlingThread->join();
	}
}

