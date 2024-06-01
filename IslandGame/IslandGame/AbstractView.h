#pragma once
#include "KeyboardListener.h"
#include "../IslandGameModel/Game.h"
#include "Structures.h"
#include "Surface.h"
#include <atlstr.h>

class CAbstractView : public IKeyboardListener {
public:
	CAbstractView(CGame** game, SIZE size, HANDLE hConsoleOutput);
	~CAbstractView();
	virtual EViewType show() = 0;
	virtual void keypressed(WORD keyCode) = 0;
	

protected:
	CGame** mpGame;
	SIZE mpSize;
	CSurface* mSurface;
	CString msCaption = "";
	CString msBottomString = "";
	HANDLE mhConsoleOutput;

	void drawCaption();
	void clean();
	void drawText(vector<CString> pText, EAlignment horizontalAlignment, EAlignment verticalAlignment, WORD attr);
	void drawBottomString();
	void ShowCursor(BOOL visible);
	void SetCursorPosition(COORD pos);
};

