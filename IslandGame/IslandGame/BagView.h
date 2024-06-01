#pragma once
#include "AbstractView.h"
class CBagView : public CAbstractView {
public:
	CBagView(CGame** game, SIZE size, HANDLE hConsoleOutput);
	EViewType show();
	void keypressed(WORD keyCode);
private:
	bool mExitToSceneView;
	CString formBottomString();
	void drawBagItems();
};

