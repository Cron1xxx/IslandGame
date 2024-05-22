#pragma once
#include "Game.h"
#include "Scene_1.h"

CGame::CGame() {
	mScenes.insert(std::make_pair("S1", new CScene("S1", *field_1, "", "", "", "")));
	mpCurrentScene = mScenes.at("S1");
}

CGame::CScene::CScene(
	CString name, 
	WORD* field, 
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

	WORD point;

	// copy passed by pointer 2D array to class member array mField
	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIGHT; x++) {
			point = *((field + y * FIELD_WIGHT) + x);
			mField[y][x] = {(SHORT)((point>>8) & 0xFF), (SHORT)(point & 0xFF)};
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
