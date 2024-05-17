#pragma once

#include "Frame.h"
#include <thread>
#include <windows.h>
#include "CTestView.h"
#include "MenuView.h"
#include <strsafe.h>
#include "Constants.h"


CFrame::CFrame() {
	SIZE size;
	size.cx = WINDOW_WIGHT;
	size.cy = WINDOW_HEIGHT;
	TCHAR szNewTitle[MAX_PATH];
	StringCchPrintf(szNewTitle, MAX_PATH, TEXT("Island Game"));
	SetConsoleTitle(szNewTitle);
	HANDLE hConsoleOutput = (HANDLE)GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleScreenBufferSize(hConsoleOutput, {(SHORT)size.cx, (SHORT)size.cy});
	SMALL_RECT rect = {0, 0, size.cx, size.cy};
	SetConsoleWindowInfo(hConsoleOutput, TRUE, &rect);
	mpKeyboardHandler = new CKeyboardHandler();
	mpMenuView = new CMenuView(mpGame, size, hConsoleOutput);
	mpTestView = new CTestView(mpGame, size, hConsoleOutput);
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

