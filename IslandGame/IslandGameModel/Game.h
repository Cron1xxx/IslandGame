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
		
		bool mVisited = false;
		bool mExchanged = false;
		bool mFree;

		EXCHANGE_RECORD mNeed;
		EXCHANGE_RECORD mOffer;

		CActivity(CString title, 
				CString inhabitant, 
				bool free, 
				EXCHANGE_RECORD need, 
				EXCHANGE_RECORD offer, 
				vector<CString> textFirstVisit, 
				vector<CString> textOthersVisitsBeforeExchange, 
				vector<CString> textAfterExchange);
		//first greeting
		vector<CString> mTextFirstVisit;
		//second end others greetings before exchange
		vector<CString> mTextOthersVisitsBeforeExchange;
		//all greetings after exchange
		vector<CString> mTextAfterExchange;
	};
	
	bool mGameOver = false;
	bool mIsWin = false;
	COORD mPosCharacter;
	CScene* mpCurrentScene = nullptr;
	CActivity* mpCurrentActivity = nullptr;
	CCharacter mCharacter;
	map<CString, CScene*> mScenes;
	map<SHORT, CActivity*> mActivities;
	CGame();
	~CGame();
	void moveCharacter(EDirection direction);
	void offerExchange();

private:
	void initActivities();
};

