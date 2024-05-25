#include "IntroView.h"

CIntroView::CIntroView(CGame** game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput) {
	msCaption = "Intro";
	drawCaption();
	msBottomString = formBottomString();
	drawBottomString();
	drawIntroText();

}

NEXT_VIEW_INFO CIntroView::show() {
	mExitToSceneView = false;
	NEXT_VIEW_INFO nextView{ EViewType::MENU_VIEW };
	mSurface->print();
	while (!mExitToSceneView) {
		Sleep(100);
	}
	return {EViewType::SCENE_VIEW};
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
	mSurface->drawText({10,10},"Welcome to the Island Game!", F_WHITE|B_BLACK);
}
