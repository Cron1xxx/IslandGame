#pragma once
#include "AbstractView.h"
class CIntroView : public CAbstractView {
public:
	CIntroView(CGame** game, SIZE size, HANDLE hConsoleOutput);
	NEXT_VIEW_INFO show();
	void keypressed(WORD keyCode);
private:
	bool mExitToSceneView;
	CString formBottomString();
	void drawIntroText();
};

