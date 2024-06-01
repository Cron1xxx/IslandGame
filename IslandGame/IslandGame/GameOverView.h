#pragma once
#include "AbstractView.h"

class CGameOverView : public CAbstractView {

public:
	CGameOverView(CGame** game, SIZE size, HANDLE hConsoleOutput);
	EViewType show();
	void keypressed(WORD keyCode);
private:
	bool mExitToMainMenuView = false;
	CString formBottomString();

};

