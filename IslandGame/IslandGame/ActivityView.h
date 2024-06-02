#pragma once
#include "AbstractView.h"
class CActivityView : public CAbstractView {

public:
	CActivityView(CGame** game, SIZE size, HANDLE hConsoleOutput);
	EViewType show();
	void keypressed(WORD keyCode);
private:
	bool mExitToSceneView = false;
	CString formBottomString();

};

