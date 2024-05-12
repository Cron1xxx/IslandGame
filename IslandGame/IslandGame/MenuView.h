#pragma once
#include "AbstractView.h"
class CMenuView : public CAbstractView {
public:
	CMenuView(CGame* game);
	std::string show();
	void keypressed(WORD keyCode);

private:
	bool mExit;
};

