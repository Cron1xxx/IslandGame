#include "MenuView.h"
#include <cstdio>

CMenuView::CMenuView(CGame* game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput){
	msCaption = "Main Menu";
	drawCaption();
	msBottomString = "?-";
	drawBottomString();
	mMenu = new CMenu(game);
	drawMenu();

}

NEXT_VIEW_INFO CMenuView::show() {
	mExit = false;
	
	while (!mExit) {
		render();
		Sleep(100);
	}
	return mMenu->action();
}

void CMenuView::render(){
	mSurface->print();
}

void CMenuView::keypressed(WORD keyCode) {
	if (keyCode == KEY_ARROW_UP) {
		mMenu->scroll(EMenuScroll::UP);
	}
	if (keyCode == KEY_ARROW_DOWN) {
		mMenu->scroll(EMenuScroll::DOWN);
	}
	if (keyCode == KEY_ENTER) {
		mExit = true;
	}
	drawMenu();
}

void CMenuView::drawMenu() {
	SHORT numItem = mMenu->mvMenuItems.size();
	SHORT maxItemCaptionLength = mMenu->mMaxItemCaptionLength;

	const SHORT boxHeight = 2;
	const SHORT boxWight = maxItemCaptionLength > 30 ? maxItemCaptionLength + 4 : 30;

	const SHORT x = mpSize.cx / 2 - boxWight / 2;
	const SHORT y = mpSize.cy / 2 - numItem * (boxHeight + 1) / 2;

	WORD attr;
	auto currentPos = mMenu->mCurrentPosition;

	for (SHORT i = 0; i < numItem; i++) {
		if (i == currentPos) {
			attr = F_BLACK | B_WHITE;
		} else {
			if (mMenu->mvMenuItems[i]->mbEnable) {
				attr = F_WHITE | B_BLACK;
			} else {
				attr = F_GREY | B_BLACK;
			}
		}
		mSurface->drawRect({x, y + i * (boxHeight + 1), x + boxWight, y + boxHeight + i * (boxHeight + 1) }, 
			EFrameType::SINGLE, attr, mMenu->mvMenuItems[i]->msCaption, EAlignment::CENTER);
	}
}

CMenuView::CMenu::CAbstractMenuItem::CAbstractMenuItem(CString caption, BOOL enable, CGame* game) {
	msCaption = caption;
	mbEnable = enable;
	mpGame = game;
}

CMenuView::CMenu::CMenu(CGame* game) {
	mvMenuItems.push_back(new CNewGameMenuItem("New Game", true, game));
	mvMenuItems.push_back(new CLoadGameMenuItem("Load Game", true, game));
	mvMenuItems.push_back(new CSaveGameMenuItem("Save Game", true, game));
	mvMenuItems.push_back(new CContinueGameMenuItem("Continue Game", true, game));
	mvMenuItems.push_back(new CExitMenuItem("Exit", true, game));
	setCurrentPosition(0);

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
	return {EViewType::SCENE_VIEW};
}

CMenuView::CMenu::CExitMenuItem::CExitMenuItem(CString caption, BOOL enable, CGame* game) : CAbstractMenuItem(caption, enable, game) {}

NEXT_VIEW_INFO CMenuView::CMenu::CExitMenuItem::action() {
	return {EViewType::EXIT};
}

CMenuView::CMenu::CLoadGameMenuItem::CLoadGameMenuItem(CString caption, BOOL enable, CGame* game) : CAbstractMenuItem(caption, enable, game) {}

//TODO:
NEXT_VIEW_INFO CMenuView::CMenu::CLoadGameMenuItem::action() {
	if (mpGame != nullptr) {
		delete mpGame;
	}
	//TODO
	mpGame = new CGame();
	return {EViewType::MENU_VIEW};
}

CMenuView::CMenu::CSaveGameMenuItem::CSaveGameMenuItem(CString caption, BOOL enable, CGame* game) : CAbstractMenuItem(caption, enable, game) {}

NEXT_VIEW_INFO CMenuView::CMenu::CSaveGameMenuItem::action() {
	if (mpGame != nullptr) {
		//TODO
	}
	return { EViewType::MENU_VIEW };
}

CMenuView::CMenu::CContinueGameMenuItem::CContinueGameMenuItem(CString caption, BOOL enable, CGame* game) : CAbstractMenuItem(caption, enable, game) {}

NEXT_VIEW_INFO CMenuView::CMenu::CContinueGameMenuItem::action() {
	if (mpGame != nullptr) {
		delete mpGame;
	}
	mpGame = new CGame();    
	return { EViewType::SCENE_VIEW };
}
