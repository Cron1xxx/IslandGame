#pragma once
#include "ActivityView.h"
#include <atlstr.h>


CActivityView::CActivityView(CGame** game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput){
	msBottomString = formBottomString();
	drawBottomString();
}

EViewType CActivityView::show() {
	mExitToSceneView = false;
	clean();
	drawText(getText(), EAlignment::CENTER, EAlignment::CENTER, F_WHITE | B_BLACK);

	while (!mExitToSceneView) {
		mSurface->print();
		Sleep(100);
	}
	(*mpGame)->mpCurrentActivity->mVisited = true;
	(*mpGame)->mpCurrentActivity = nullptr;
	return EViewType::SCENE_VIEW;
}

void CActivityView::keypressed(WORD keyCode) {
	if (keyCode == KEY_E) {
		(*mpGame)->offerExchange();
	}
	if (keyCode == KEY_ENTER) {
		mExitToSceneView = true;
	}
}

CString CActivityView::formBottomString() {
	return "E - offer exchange, ENTER - leave activity";
}

vector<CString> CActivityView::getText() {
	auto activity = (*mpGame)->mpCurrentActivity;
	
	if (activity->mVisited) {
		if (activity->mExchanged) {
			return activity->mTextAfterExchange;
		} else {
			return activity->mTextOthersVisitsBeforeExchange;
		}
	} else {
		return activity->mTextFirstVisit;
	}
	return vector<CString>();
}
