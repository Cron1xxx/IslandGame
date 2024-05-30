#include "SceneView.h"
#include <string>

using namespace std;

CSceneView::CSceneView(CGame** game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput) {
	msCaption = "Scene";
	drawCaption();
	msBottomString = formBottomString();
	drawBottomString();
	renderCharacterInfoFrame();
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
		renderCharacterInfo();
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
				ch = char(177);
				color = F_YELLOW|B_LIGHTYELLOW;
			} else  if (field[y][x].sObject == S_FOREST) {
				ch = char(23);
				color = F_BLACK|B_GREEN;
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
	mSurface->drawTransparentChar(cord, (char)2, F_BLACK);
}

void CSceneView::renderCharacterInfo() {
	// clean area
	mSurface->drawText({9, 2},"                    ", F_WHITE | B_BLACK);
	mSurface->drawText({9, 3},"                    ", F_WHITE | B_BLACK);
	
	// calculate health
	SHORT const numberOfHearts = 5;
	SHORT const oneHeartHealth = CHARACTER_HEALTH_DEFAULT / numberOfHearts;
	SHORT const numberOfHealthyHearts = (*mpGame)->mCharacter.health / oneHeartHealth;

	// draw hearts
	WORD color;
	for (SHORT i = 1; i <= numberOfHearts; i++) {
		if (i <= numberOfHealthyHearts) {
			color = F_LIGHTRED | B_BLACK;
		} else {
			color = F_GREY | B_BLACK;
		}
		mSurface->drawChar({SHORT(10 + i), 2}, char(3), color);
	}

	// print coins
	CString strCoins;
	strCoins.Format("%d", (*mpGame)->mCharacter.coins);
	mSurface->drawText({10, 3}, strCoins, F_LIGHTYELLOW | B_BLACK);
}

void CSceneView::renderCharacterInfoFrame() {
	mSurface->drawRectWithCaption({1, 1, 30, 4}, EFrameType::SINGLE, F_WHITE|B_BLACK, " Character Info ");
	mSurface->drawText({2, 2}, "Health:", F_WHITE | B_BLACK);
	mSurface->drawText({2, 3}, "Coins :", F_WHITE | B_BLACK);
}


