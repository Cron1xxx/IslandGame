#pragma once
#include "View.h"
#include "KeyboardListener.h"
#include "../IslandGameModel/Game.h"
#include "Structures.h"
#include "Surface.h"
#include <atlstr.h>

class CAbstractView :public IView , public IKeyboardListener {
public:
	CAbstractView(CGame** game, SIZE size, HANDLE hConsoleOutput);
	~CAbstractView();
	virtual NEXT_VIEW_INFO show() = 0;
	virtual void keypressed(WORD keyCode) = 0;
	

protected:
	CGame** mpGame;
	SIZE mpSize;
	CSurface* mSurface;
	CString msCaption = "";
	CString msBottomString = "";
	HANDLE mhConsoleOutput;

	void drawCaption();
	void drawBottomString();
	void ShowCursor(BOOL visible);
	void SetCursorPosition(COORD pos);
};

