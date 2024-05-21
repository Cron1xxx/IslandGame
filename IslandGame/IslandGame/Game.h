#pragma once
#include <Windows.h>
#include <atlstr.h>
#include "Constants.h"
#include <map>
#include "Structures.h"

#define	FIELD_HEIGHT 31
#define FIELD_WIGHT 96

#define S_WATER 0x00
#define S_GROUND 0x01
#define S_ROAD 0x02
#define S_SAND 0x03
#define S_ACTIVITY 0x04

using namespace std;

class CGame {
public:
	class CScene {
	public:
		CScene(CString name, WORD field[][FIELD_WIGHT],	CString rightSceneName, CString leftSceneName, CString upSceneName, CString downSceneName);
		CString msName;
		WORD mField[FIELD_HEIGHT][FIELD_WIGHT];
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

