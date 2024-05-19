#include "MenuView.h"
#include <cstdio>

CMenuView::CMenuView(CGame* game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput){
	msCaption = "Main Menu";
	drawCaption();
	mMenu = new CMenu(game);
	drawMenu();
}

NEXT_VIEW_INFO CMenuView::show() {
	mExit = false;
	
	while (!mExit) {
		render();
		Sleep(500);
	}
	NEXT_VIEW_INFO nextViewInfo;
	nextViewInfo.mViewType = EViewType::TEST_VIEW;
	return nextViewInfo;
}

void CMenuView::render(){
	mSurface->print();
}

void CMenuView::keypressed(WORD keyCode) {
	if (keyCode == 69) {
		mExit = true;
	}
}

void CMenuView::drawMenu() {
	SHORT numItem = mMenu->mvMenuItems.size();
	SHORT maxItemCaptionLength = mMenu->mMaxItemCaptionLength;

	const SHORT boxHeight = 3;
	const SHORT boxWight = maxItemCaptionLength > 30 ? maxItemCaptionLength + 4 : 30;

	const SHORT x = mpSize.cx / 2 - boxWight / 2;
	const SHORT y = mpSize.cy / 2 - numItem * (boxHeight + 1) / 2;

	for (SHORT i = 0; i < numItem; i++) {
		mSurface->drawRect({x, y + i * (boxHeight + 1), x + boxWight, y + boxHeight + i * (boxHeight + 1) }, EFrameType::SINGLE, F_WHITE);
	}

	
}

CMenuView::CMenu::CAbstractMenuItem::CAbstractMenuItem(CString caption, BOOL enable, CGame* game) {
	msCaption = caption;
	mbEnable = enable;
	mpGame = game;
}

CMenuView::CMenu::CMenu(CGame* game) {
	mvMenuItems.push_back(new CNewGameMenuItem("New Game", true, game));
	mvMenuItems.push_back(new CExitMenuItem("Exit", true, game));
	mvMenuItems.push_back(new CExitMenuItem("Exit", true, game));
	mvMenuItems.push_back(new CExitMenuItem("Exit", true, game));
	mvMenuItems.push_back(new CExitMenuItem("Exit", true, game));
	mvMenuItems.push_back(new CExitMenuItem("Exit", true, game));

}

void CMenuView::CMenu::scroll(EMenuScroll direction) {
	auto pos = mCurrentPosition;
	
	while (true) {
		if (direction == EMenuScroll::DOWN) {
			if (pos + 1 >= mvMenuItems.size()) {
				pos = 0;
			} else {
				pos++;
			}
		} else {
			if (pos - 1 < 0) {
				pos = mvMenuItems.size() - 1;
			} else {
				pos--;
			}
		}
		if (mvMenuItems[pos]->mbEnable) {
			setCurrentPosition(pos);
			break;
		}
	}
}

NEXT_VIEW_INFO CMenuView::CMenu::action() {
	return mCurrentItem->action();
}

void CMenuView::CMenu::addItem(CAbstractMenuItem* item) {
	if (item->msCaption.GetLength() > mMaxItemCaptionLength) {
		mMaxItemCaptionLength = item->msCaption.GetLength();
	}
	mvMenuItems.push_back(item);
}

void CMenuView::CMenu::setCurrentPosition(SHORT ind) {
	mCurrentItem = mvMenuItems[ind];
	mCurrentPosition = ind;
}


CMenuView::CMenu::CNewGameMenuItem::CNewGameMenuItem(CString caption, BOOL enable, CGame* game) : CAbstractMenuItem(caption, enable, game) {}

NEXT_VIEW_INFO CMenuView::CMenu::CNewGameMenuItem::action() {
	if (mpGame != nullptr) {
		delete mpGame;
	}
	mpGame = new CGame();

	return NEXT_VIEW_INFO();
}

CMenuView::CMenu::CExitMenuItem::CExitMenuItem(CString caption, BOOL enable, CGame* game) : CAbstractMenuItem(caption, enable, game) {}

NEXT_VIEW_INFO CMenuView::CMenu::CExitMenuItem::action() {
	return {EViewType::EXIT};
}
