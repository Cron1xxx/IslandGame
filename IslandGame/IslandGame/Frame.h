#pragma once

#include "Game.h"
#include "View.h"
#include "KeyboardHandler.h"

class CFrame {

public:
	CFrame();
	void run();
private:
	CGame* mpGame;
	IView* mpCurrentView;
	CKeyboardHandler* mpKeyboardHandler;
};

