#pragma once

#include "Game.h"
#include "Scene_1.h"
#include "Scene_2.h"
#include "Scene_3.h"
#include "Scene_4.h"

CGame::CGame() {
	// things:
	mThings.insert(std::make_pair("Rod", new CThing("Rod", "The rod from Igor for passing to the monk")));

	// scenes:
	mScenes.insert(std::make_pair("S1", new CScene("S1", *field_1, "S2", "", "", "S3")));
	mScenes.insert(std::make_pair("S2", new CScene("S2", *field_2, "", "S1", "", "S4")));
	mScenes.insert(std::make_pair("S3", new CScene("S3", *field_3, "S4", "", "S1", "")));
	mScenes.insert(std::make_pair("S4", new CScene("S4", *field_4, "", "S3", "S2", "")));
	// activities:
	initActivities();

	mpCurrentScene = mScenes.at("S3");
	mPosCharacter.X = 50;
	mPosCharacter.Y = 25;
}

CGame::~CGame() {
	// release memory
	for (map<CString, CScene*>::iterator it = mScenes.begin(); it != mScenes.end(); it++) {
		delete it->second;
	}
	mScenes.clear();

	for (map<SHORT, CActivity*>::iterator it = mActivities.begin(); it != mActivities.end(); it++) {
		delete it->second;
	}
	mActivities.clear();
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
		// ACTIVITY
		if (mpCurrentScene->mField[nextPos.Y][nextPos.X].sObject == S_ACTIVITY) {
			mpCurrentActivity = mActivities.at(mpCurrentScene->mField[nextPos.Y][nextPos.X].sAttr);
		}
		nextPos = mPosCharacter;
	}

	if (nextPos.X != mPosCharacter.X || nextPos.Y != mPosCharacter.Y) {
		mCharacter.health -= mpCurrentScene->mField[nextPos.Y][nextPos.X].sPenalty;
		if (mCharacter.health <= 0) {
			mGameOver = true;
		}
	}

	mPosCharacter = nextPos;
}

bool CGame::offerExchange() {
	bool exchange = false;

	if (mpCurrentActivity == nullptr) {
		return exchange;
	}
	if (mpCurrentActivity->mExchanged) {
		return exchange;
	}

	if (!mpCurrentActivity->mFree) {
		if (mpCurrentActivity->mNeed.ExchangeType == EExchangeType::MONEY) {
			if (mCharacter.coins >= mpCurrentActivity->mNeed.Exchange.MoneyAmount) {
				mCharacter.coins -= mpCurrentActivity->mNeed.Exchange.MoneyAmount;
				exchange = true;
			}
		}
		if (mpCurrentActivity->mNeed.ExchangeType == EExchangeType::THING) {
			vector <CThing*>::iterator i;
			for (CThing* thing : mCharacter.bag) {
				if (*(mpCurrentActivity->mNeed.Exchange.Thing) == *thing) {
					mCharacter.bag.erase(i);
					exchange = true;
					break;
				}
				i++;
			}
		}
		if (mpCurrentActivity->mNeed.ExchangeType == EExchangeType::HEALTH) {
			if (mCharacter.health >= mpCurrentActivity->mNeed.Exchange.Health) {
				mCharacter.health -= mpCurrentActivity->mNeed.Exchange.Health;
				exchange = true;
			}
		}
	} else {
		exchange = true;
	}

	if (exchange) {
		
		if (mpCurrentActivity->mOffer.ExchangeType == EExchangeType::MONEY) {
			mCharacter.coins += mpCurrentActivity->mOffer.Exchange.MoneyAmount;
		}

		if (mpCurrentActivity->mOffer.ExchangeType == EExchangeType::THING) {
			mCharacter.bag.push_back(mpCurrentActivity->mOffer.Exchange.Thing);
		}

		if (mpCurrentActivity->mOffer.ExchangeType == EExchangeType::RELOCATION) {
			mPosCharacter.X = mpCurrentActivity->mOffer.Exchange.RelocationCoord.X;
			mPosCharacter.Y = mpCurrentActivity->mOffer.Exchange.RelocationCoord.Y;
		}

		if (mpCurrentActivity->mOffer.ExchangeType == EExchangeType::ESCAPE) {
			mGameOver = true;
			mIsWin = true;
		}
	}

	return exchange;
}


void CGame::initActivities() {
	mScenes.insert(std::make_pair("S4", new CScene("S4", *field_4, "", "S3", "S2", "")));
	CString title;
	CString inhabitant;
	bool free;
	EXCHANGE_RECORD need;
	EXCHANGE_RECORD offer;
	vector<CString> textFirstVisit;
	vector<CString> textOthersVisitsBeforeExchange;
	vector<CString> textAfterExchange;

	//A1
	title = "Harbor";
	inhabitant = "Jack";
	free = false;
	need = EXCHANGE_RECORD();
	need.ExchangeType = EExchangeType::MONEY;
	need.Exchange.MoneyAmount = 10;
	offer = EXCHANGE_RECORD();
	offer.ExchangeType = EExchangeType::ESCAPE;
	textFirstVisit.clear();
	textFirstVisit.push_back("Hi stranger!!!");
	textFirstVisit.push_back("");
	textFirstVisit.push_back("I'm Jack, harbor master.");
	textFirstVisit.push_back("You can rent a boat and leave the island but it will cost 10 coins.");
	textFirstVisit.push_back("Do you have any???.");
	textOthersVisitsBeforeExchange.clear();
	textOthersVisitsBeforeExchange.push_back("Hi! Glad to see you again stranger.");
	textOthersVisitsBeforeExchange.push_back("Did you find money?");
	textAfterExchange.clear();
	mActivities.insert(std::make_pair(1, 
		new CActivity(title, inhabitant, free, need, offer, textFirstVisit, textOthersVisitsBeforeExchange, textAfterExchange)));

	//A2
	title = "Fishermen's house";
	inhabitant = "Igor";
	free = true;
	need = EXCHANGE_RECORD();
	need.ExchangeType = EExchangeType::NOTHING;
	need.Exchange.MoneyAmount = 10;
	offer = EXCHANGE_RECORD();
	offer.ExchangeType = EExchangeType::THING;
	offer.Exchange.Thing = mThings.at("Rod");
	textFirstVisit.clear();
	textFirstVisit.push_back("Hi man!!!");
	textFirstVisit.push_back("");
	textFirstVisit.push_back("I'm Igor, I'm fisher.");
	textFirstVisit.push_back("Can you take this rod and pass it to the monk from island?");
	textFirstVisit.push_back("He will be so glad.");
	textOthersVisitsBeforeExchange.clear();
	textOthersVisitsBeforeExchange.push_back("Hi, how are you?");
	textOthersVisitsBeforeExchange.push_back("How about a rod?");
	textAfterExchange.clear();
	textAfterExchange.push_back("How are you?");
	mActivities.insert(std::make_pair(2,
		new CActivity(title, inhabitant, free, need, offer, textFirstVisit, textOthersVisitsBeforeExchange, textAfterExchange)));
}


CGame::CActivity::CActivity(CString title, 
		CString inhabitant, 
		bool free, 
		EXCHANGE_RECORD need, 
		EXCHANGE_RECORD offer, 
		vector<CString> textFirstVisit, 
		vector<CString> textOthersVisitsBeforeExchange, 
		vector<CString> textAfterExchange) : 
	mInhabitant(inhabitant), 
	mFree(free), 
	mNeed(need), 
	mOffer(offer), 
	mTextFirstVisit(textFirstVisit), 
	mTextOthersVisitsBeforeExchange(textOthersVisitsBeforeExchange),
	mTextAfterExchange(textAfterExchange)
{
	// default 
	mTextAfterSuccessfulExchange.push_back("Thank you!!!");
	mTextAfterUnsuccessfulExchange.push_back("You have nothing interesting for me.");
}

vector<CString> CGame::CActivity::getText() {
	if (mVisited) {
		if (mExchanged) {
			return mTextAfterExchange;
		} else {
			return mTextOthersVisitsBeforeExchange;
		}
	} else {
		return mTextFirstVisit;
	}
}
