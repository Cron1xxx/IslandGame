#pragma once

#include "Frame.h"
#include <thread>
#include <windows.h>
#include "CTestView.h"
#include "MenuView.h"



CFrame::CFrame() {
	mpKeyboardHandler = new CKeyboardHandler();
	mpMenuView = new CMenuView(mpGame);
	mpTestView = new CTestView(mpGame);
}

void CFrame::run() {
	mKeyboardHandlingThread = new thread(&CFrame::runThreadKeyboardHandler, this, mpKeyboardHandler);
	setActiveView("menu_view");
	std::string nextView;
	while (true) {
		nextView = mpActiveView->show();
		setActiveView(nextView);
	}
}


void CFrame::runThreadKeyboardHandler(CKeyboardHandler* handler) {
	mpKeyboardHandler->run();
}

void CFrame::setActiveView(std::string viewName) {
	if (viewName.compare("menu_view") == 0) {
		mpKeyboardHandler->setListener(mpMenuView);
		mpActiveView = mpMenuView;
		
	} else if (viewName.compare("test_view") == 0) {
		mpKeyboardHandler->setListener(mpTestView);
		mpActiveView = mpTestView;
	};
}

CFrame::~CFrame() {
	if (mKeyboardHandlingThread) {
		mKeyboardHandlingThread->join();
	}
}

