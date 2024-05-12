#pragma once
#include "View.h"
#include "KeyboardListener.h"
#include "Game.h"
//#include "Frame.h"

class CAbstractView :public IView , public IKeyboardListener {
public:
	CAbstractView(CGame* game);
	virtual std::string show() = 0;
	virtual void keypressed(WORD keyCode) = 0;

protected:
	CGame* mpGame;
};

