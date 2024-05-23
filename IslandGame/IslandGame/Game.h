#pragma once
#include <Windows.h>
#include <atlstr.h>
#include "Constants.h"
#include <map>
#include "Structures.h"


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
	};
	COORD mPosCharacter;
	CScene* mpCurrentScene;
	map<CString, CScene*> mScenes;
	CGame();
	void moveCharacter(EDirection direction);

};

