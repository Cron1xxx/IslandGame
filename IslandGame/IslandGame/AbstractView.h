#pragma once
#include "View.h"
#include "KeyboardListener.h"
#include "Game.h"
#include "Structures.h"

class CAbstractView :public IView , public IKeyboardListener {
public:
	CAbstractView(CGame* game, SIZE size);
	virtual NEXT_VIEW_INFO show() = 0;
	virtual void keypressed(WORD keyCode) = 0;

protected:
	CGame* mpGame;
	SIZE mpSize;
};

