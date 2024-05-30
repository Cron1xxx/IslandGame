#pragma once
#pragma once
#include <Windows.h>
#include <atlstr.h>
#include "GameConstants.h"
#include <map>
#include <vector>
#include "GameStructures.h"
#include "Thing.h"


using namespace std;

class CGame {
public:
	class CScene {
	public:
		CScene(CString name, WORD* field, CString rightSceneName, CString leftSceneName, CString upSceneName, CString downSceneName);
		CString msName;
		LOCATION_INFO mField[FIELD_HEIGHT][FIELD_WIGHT];
		CString msRightSceneName;
		CString msLeftSceneName;
		CString msUpSceneName;
		CString msDownSceneName;
		static LOCATION_INFO convertToLocationInfo(WORD word);
	};

	

	class CCharacter {
	public:
		SHORT health = CHARACTER_HEALTH_DEFAULT;
		SHORT coins = CHARACTER_COINS_DEFAULT;
		vector<CThing*> bag;
	};

	class CActivity {
	public:
		CString mTitle;
		CString mInhabitant;
		//first greeting
		CString mText1;
		//second end others greetings before exchange
		CString mText2;
		//all greetings after exchange
		CString mText3;
		bool mVisited;
		bool mExchanged;
		bool mFree;

		EXCHANGE_RECORD mNeed;
		EXCHANGE_RECORD mOffer;

		EXCHANGE_RECORD offerToExchange (EXCHANGE_RECORD forExchange);
	};
	
	bool mGameOver = false;
	bool mIsWin = false;
	COORD mPosCharacter;
	CScene* mpCurrentScene;
	CCharacter mCharacter;
	map<CString, CScene*> mScenes;
	CGame();
	void moveCharacter(EDirection direction);

};

