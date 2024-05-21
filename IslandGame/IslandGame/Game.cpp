#pragma once
#include "Game.h"
#include "Scene_1.h"

CGame::CGame() {
	mScenes.insert(std::make_pair("S1", new CScene("S1", field_1, "", "", "", "")));
	mpCurrentScene = mScenes.at("S1");
}

CGame::CScene::CScene(
	CString name, 
	WORD field[][FIELD_WIGHT], 
	CString rightSceneName, 
	CString leftSceneName, 
	CString upSceneName, 
	CString downSceneName) 
{
	msName = name;
	msRightSceneName = rightSceneName;
	msLeftSceneName = leftSceneName;
	msUpSceneName = upSceneName;
	msDownSceneName = downSceneName;
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIGHT; x++) {
			mField[y][x] = field[y][x];
		}
	}
}

void CGame::moveCharacter(EDirection direction) {
	COORD nextPos = mPosCharacter;

	if (direction == EDirection::UP) {
		nextPos.Y--; 
	} else if (direction == EDirection::DOWN) {
		nextPos.Y++;
	} else if (direction == EDirection::LEFT) {
		nextPos.X--;
	} else if (direction == EDirection::RIGHT) {
		nextPos.X++;
	}
}
