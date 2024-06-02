#include "BagView.h"

CBagView::CBagView(CGame** game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput) {
	msBottomString = formBottomString();
	drawBottomString();
	msCaption = "Bag";
	drawCaption();
}

EViewType CBagView::show() {
	mExitToSceneView = false;
	drawBagItems();

	while (!mExitToSceneView) {
		mSurface->print();
		Sleep(100);
	}

	return EViewType::SCENE_VIEW;
}

void CBagView::keypressed(WORD keyCode) {
	if (keyCode == KEY_ENTER) {
		mExitToSceneView = true;
	}
}

CString CBagView::formBottomString() {

	return "Press ENTER to continue...";
}

void CBagView::drawBagItems() {
	clean();
	vector<CString> text;
	auto bag = (*mpGame)->mCharacter.bag;
	if (bag.empty()) {
		text.push_back("The bag is empty.");
	} else {
		for (auto thing : bag) {
			CString str;
			str.Format(_T("%s - %s"), thing->mName, thing->mDescription);
			text.push_back(str);
		}
	}
	drawText(text, EAlignment::CENTER, EAlignment::CENTER, F_WHITE|B_BLACK);
}
