#pragma once

#include "Game.h"
#include "Scene_1.h"
#include "Scene_2.h"
#include "Scene_3.h"
#include "Scene_4.h"

CGame::CGame() {
	mScenes.insert(std::make_pair("S1", new CScene("S1", *field_1, "S2", "", "", "S3")));
	mScenes.insert(std::make_pair("S2", new CScene("S2", *field_2, "", "S1", "", "S4")));
	mScenes.insert(std::make_pair("S3", new CScene("S3", *field_3, "S4", "", "S1", "")));
	mScenes.insert(std::make_pair("S4", new CScene("S4", *field_4, "", "S3", "S2", "")));
	mpCurrentScene = mScenes.at("S3");
	mPosCharacter.X = 50;
	mPosCharacter.Y = 25;
}

CGame::CScene::CScene(
	CString name,
	WORD* field,
	CString rightSceneName,
	CString leftSceneName,
	CString upSceneName,
	CString downSceneName) {
	msName = name;
	msRightSceneName = rightSceneName;
	msLeftSceneName = leftSceneName;
	msUpSceneName = upSceneName;
	msDownSceneName = downSceneName;

	WORD point;

	for (int y = 0; y < FIELD_HEIGHT; y++) {
		for (int x = 0; x < FIELD_WIGHT; x++) {
			point = *((field + y * FIELD_WIGHT) + x);
			mField[y][x] = convertToLocationInfo(point);
		}
	}
}

LOCATION_INFO CGame::CScene::convertToLocationInfo(WORD word) {
	SHORT object = (word >> 8) & 0xFF;
	SHORT attr = word & 0xFF;
	SHORT penalty = 0;
	bool obstacle = false;

	if (object == S_WATER || object == S_ACTIVITY) {
		obstacle = true;
	}

	if (object == S_GROUND) {
		penalty = 2;
	}

	if (object == S_ROAD) {
		penalty = 1;
	}

	if (object == S_SAND) {
		penalty = 3;
	}

	if (object == S_FOREST) {
		penalty = 4;
	}

	return { object, attr, obstacle, penalty };
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

	// TO UP
	if (nextPos.Y < 0) {
		mpCurrentScene = mScenes.at(mpCurrentScene->msUpSceneName);
		nextPos.Y = FIELD_HEIGHT - 1;
		// TO DOWN
	} else if (nextPos.Y >= FIELD_HEIGHT) {
		mpCurrentScene = mScenes.at(mpCurrentScene->msDownSceneName);
		nextPos.Y = 0;
		// TO RIGHT
	} else if (nextPos.X >= FIELD_WIGHT) {
		mpCurrentScene = mScenes.at(mpCurrentScene->msRightSceneName);
		nextPos.X = 0;
		// TO LEFT
	} else if (nextPos.X < 0) {
		mpCurrentScene = mScenes.at(mpCurrentScene->msLeftSceneName);
		nextPos.X = FIELD_WIGHT - 1;
		// OBSTACLE
	} else if (mpCurrentScene->mField[nextPos.Y][nextPos.X].bObstacle) {
		nextPos = mPosCharacter;
	}

	if (nextPos.X != mPosCharacter.X || nextPos.Y != mPosCharacter.Y) {
		mCharacter.health -= mpCurrentScene->mField[nextPos.Y][nextPos.X].sPenalty;
	}

	mPosCharacter = nextPos;
}

EXCHANGE_RECORD CGame::CActivity::offerToExchange(EXCHANGE_RECORD forExchange) {
	if (!mExchanged && (mFree || forExchange == mNeed)) {
		mExchanged = true;
		return mOffer;
	} else {
		return {EExchangeType::NOTHING};
	}
}
