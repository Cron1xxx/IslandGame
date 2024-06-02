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
	drawText((*mpGame)->mpCurrentActivity->getText(), EAlignment::CENTER, EAlignment::CENTER, F_WHITE | B_BLACK);

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
		if (!(*mpGame)->mpCurrentActivity->mExchanged) {
			auto successful = (*mpGame)->offerExchange();
			vector<CString> text;
			clean();
			if (successful) {
				(*mpGame)->mpCurrentActivity->mExchanged = true;
				text = (*mpGame)->mpCurrentActivity->mTextAfterSuccessfulExchange;
			} else {
				text = (*mpGame)->mpCurrentActivity->mTextAfterUnsuccessfulExchange;
			}
			drawText(text, EAlignment::CENTER, EAlignment::CENTER, F_WHITE | B_BLACK);
		}
	}
	if (keyCode == KEY_ENTER) {
		mExitToSceneView = true;
	}
}

CString CActivityView::formBottomString() {
	return "E - offer exchange, ENTER - leave activity";
}

