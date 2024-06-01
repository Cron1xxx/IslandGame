#pragma once

#include "../IslandGameModel/Game.h"
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
	
	map<EViewType, CAbstractView*> mViews;

	CKeyboardHandler* mpKeyboardHandler;
	thread* mKeyboardHandlingThread;
	void setActiveView(EViewType nextViewType);
};

