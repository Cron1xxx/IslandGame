#pragma once

#include "Frame.h"
#include <thread>
#include <windows.h>
#include "MenuView.h"
#include "SceneView.h"
#include "IntroView.h"
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
	
	//create views
	mViews.insert(std::make_pair(EViewType::MENU_VIEW, new CMenuView(&mpGame, size, hConsoleOutput)));
	mViews.insert(std::make_pair(EViewType::SCENE_VIEW, new CSceneView(&mpGame, size, hConsoleOutput)));
	mViews.insert(std::make_pair(EViewType::INTRO_VIEW, new CIntroView(&mpGame, size, hConsoleOutput)));
}

void CFrame::run() {
	mKeyboardHandlingThread = new thread(&CKeyboardHandler::run, mpKeyboardHandler);
	NEXT_VIEW_INFO nextView;
	nextView.mViewType = EViewType::MENU_VIEW;
	setActiveView(nextView);
	
	while (true) {
		nextView = mpActiveView->show();
		if (nextView.mViewType == EViewType::EXIT) {
			exit(0);
		}
		setActiveView(nextView);
	}
	
}


void CFrame::setActiveView(NEXT_VIEW_INFO nextViewInfo) {
	auto view = mViews.at(nextViewInfo.mViewType);
	mpKeyboardHandler->setListener(view);
	mpActiveView = view;
}

CFrame::~CFrame() {
	if (mKeyboardHandlingThread) {
		mKeyboardHandlingThread->join();
	}
}

