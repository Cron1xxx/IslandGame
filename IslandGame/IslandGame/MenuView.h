#pragma once
#include "AbstractView.h"

class CMenuView : public CAbstractView {
public:
	CMenuView(CGame* game, SIZE size);
	NEXT_VIEW_INFO show();
	void keypressed(WORD keyCode);

private:
	bool mExit;
	void render();
};

