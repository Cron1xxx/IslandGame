#include "GameOverView.h"

CGameOverView::CGameOverView(CGame** game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput){
	msBottomString = formBottomString();
	drawBottomString();
}

NEXT_VIEW_INFO CGameOverView::show() {
	mExitToMainMenuView = false;
	mSurface->drawText({ 30,10 }, "Game Over!", F_RED | F_BLACK);
	if ((*mpGame)->mIsWin) {
		mSurface->drawText({ 30,11 }, "You win!", F_RED | F_BLACK);
	} else {
		mSurface->drawText({ 30,11 }, "You lose!", F_RED | F_BLACK);
	}
	while (!mExitToMainMenuView) {
		mSurface->print();
		Sleep(100);
	}
	delete (*mpGame);
	return {EViewType::MENU_VIEW};
}

void CGameOverView::keypressed(WORD keyCode) {
    mExitToMainMenuView = true;
}

CString CGameOverView::formBottomString() {
    
    return "Press any key...";
}
