#include "GameOverView.h"

CGameOverView::CGameOverView(CGame** game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput){
	msBottomString = formBottomString();
	drawBottomString();
}

EViewType CGameOverView::show() {
	mExitToMainMenuView = false;
	clean();
	vector<CString> text;
	text.push_back("Game Over!");
	text.push_back("");
	if ((*mpGame)->mIsWin) {
		text.push_back("You win!");
	} else {
		text.push_back("You lose!");
		text.push_back("Next time be more clever.");
	}
	drawText(text, EAlignment::CENTER, EAlignment::CENTER, F_WHITE | B_BLACK);

	while (!mExitToMainMenuView) {
		mSurface->print();
		Sleep(100);
	}

	delete *mpGame;
	*mpGame = nullptr;
	
	return EViewType::MENU_VIEW;
}

void CGameOverView::keypressed(WORD keyCode) {
	if (keyCode == KEY_ENTER) {
		mExitToMainMenuView = true;
	}
}

CString CGameOverView::formBottomString() {
    
    return "Press ENTER to continue...";
}
