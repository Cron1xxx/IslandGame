#pragma once

#include "Game.h"
#include "KeyboardHandler.h"
#include "AbstractView.h"
#include <thread>
#include <string>
#include <map>

using namespace std;

class CFrame {

public:
	CFrame();
	void run();
	~CFrame();
private:
	CGame* mpGame;
	CAbstractView* mpActiveView;
	
	CAbstractView* mpMenuView;
	CAbstractView* mpTestView;

	CKeyboardHandler* mpKeyboardHandler;
	void runThreadKeyboardHandler(CKeyboardHandler* handler);
	thread* mKeyboardHandlingThread;
	void setActiveView(string viewName);
	//map<string, unique_ptr<CAbstractView>> *mViewMap;
	
};

