#include "SceneView.h"

CSceneView::CSceneView(CGame** game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput) {
	mpGame = game;
	msCaption = "Scene";
	drawCaption();
	msBottomString = formBottomString();
	drawBottomString();
	mSurface->drawRect({1, 5, mpSize.cx - 2, mpSize.cy - 3}, EFrameType::SINGLE, F_WHITE);
}

NEXT_VIEW_INFO CSceneView::show() {
	mExitToMainMenu = false;
	NEXT_VIEW_INFO nextView;
	while (true) {
		if (mExitToMainMenu == true) {
			nextView = {EViewType::MENU_VIEW};
			mExitToMainMenu = false;
			break;
		}
		renderField();
		renderCharacter();
		mSurface->print();
		Sleep(100);
	}
	return nextView;
}

void CSceneView::keypressed(WORD keyCode) {
	if (keyCode == KEY_M) {
		mExitToMainMenu = true;
	}
	if (keyCode == KEY_ARROW_UP) {
		(*mpGame)->moveCharacter(EDirection::UP);
	}
	if (keyCode == KEY_ARROW_DOWN) {
		(*mpGame)->moveCharacter(EDirection::DOWN);
	}
	if (keyCode == KEY_ARROW_LEFT) {
		(*mpGame)->moveCharacter(EDirection::LEFT);
	}
	if (keyCode == KEY_ARROW_RIGHT) {
		(*mpGame)->moveCharacter(EDirection::RIGHT);
	}
}

CString CSceneView::formBottomString() {
	CString str = "";
	str.AppendChar((char)27);
	str.AppendChar((char)24);
	str.AppendChar((char)26);
	str.AppendChar((char)25);
	str = str + " - Move, M - Main Menu";
	return str;
}

void CSceneView::renderField() {
	SHORT dx = 2, dy = 6; 
	WORD color = B_BLACK;
	CHAR ch;
	auto field = (**mpGame).mpCurrentScene->mField;
	for (SHORT y = 0; y < FIELD_HEIGHT; y++) {
		for (SHORT x = 0; x < FIELD_WIGHT; x++) {
			if (field[y][x].sObject == S_WATER) {
				ch = ' ';
				color = B_BLUE;
			} else if (field[y][x].sObject == S_GROUND) {
				ch = ' ';
				color = B_LIGHTGREEN;
			} else  if (field[y][x].sObject == S_ROAD) {
				ch = ' ';
				color = B_GREY;
			} else  if (field[y][x].sObject == S_SAND) {
				ch = ' ';
				color = B_LIGHTYELLOW;
			} else  if (field[y][x].sObject == S_FOREST) {
				ch = ' ';
				color = B_GREEN;
			} else  if (field[y][x].sObject == S_ACTIVITY) {
				ch = 'A';
				color = F_WHITE|B_RED;
			} else {
				continue;
			}
			mSurface->drawChar({ SHORT(dx + x), (SHORT)(dy + y) }, ch, color);
		}
	}
}

void CSceneView::renderCharacter() {
	COORD cord = (*mpGame)->mPosCharacter;
	cord.X += 2;
	cord.Y +=6;
	mSurface->drawTransparentChar(cord, (char)20, F_BLACK);
}
