#include "IntroView.h"

CIntroView::CIntroView(CGame** game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput) {
	msCaption = "Intro";
	drawCaption();
	msBottomString = formBottomString();
	drawBottomString();
	drawIntroText();

}

EViewType CIntroView::show() {
	mExitToSceneView = false;
	mSurface->print();
	while (!mExitToSceneView) {
		Sleep(100);
	}
	return EViewType::SCENE_VIEW;
}

void CIntroView::keypressed(WORD keyCode) {
	if (keyCode == KEY_ENTER) {
		mExitToSceneView = true;
	}
}

CString CIntroView::formBottomString() {
	return "ENTER - start game";
}

void CIntroView::drawIntroText() {
	vector<CString> text;
	text.push_back("Welcome to the Island Game!");
	text.push_back("");
	text.push_back("Your goal is to escape from this island.");

	drawText(text, EAlignment::CENTER, EAlignment::CENTER, F_WHITE|B_BLACK);
}
