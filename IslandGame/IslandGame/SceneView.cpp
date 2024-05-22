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
	auto field = (**mpGame).mpCurrentScene->mField;
	for (SHORT y = 0; y < FIELD_HEIGHT; y++) {
		for (SHORT x = 0; x < FIELD_WIGHT; x++) {
			if (field[y][x].sObject == S_WATER) {
				color = B_BLUE;
			} else if (field[y][x].sObject == S_GROUND) {
				color = B_LIGHTGREEN;
			} else  if (field[y][x].sObject == S_ROAD) {
				color = B_GREY;
			} else  if (field[y][x].sObject == S_SAND) {
				color = B_LIGHTYELLOW;
			} else  if (field[y][x].sObject == S_FOREST) {
				color = B_GREEN;
			} else {
				continue;
			}
			mSurface->drawChar({ SHORT(dx + x), (SHORT)(dy + y) }, ' ', color);
		}
	}
}

void CSceneView::renderCharacter() {

}
