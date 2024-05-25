#pragma once
#pragma once
#include <Windows.h>
#include <atlstr.h>
#include "GameConstants.h"
#include <map>
#include "GameStructures.h"


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
	COORD mPosCharacter;
	CScene* mpCurrentScene;
	map<CString, CScene*> mScenes;
	CGame();
	void moveCharacter(EDirection direction);

};

