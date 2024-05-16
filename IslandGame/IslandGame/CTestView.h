#pragma once

#include "AbstractView.h"

class CTestView : public CAbstractView{
public:
	CTestView(CGame* game, SIZE size);
	virtual NEXT_VIEW_INFO show();
	virtual void keypressed(WORD keyCode);
	
private:
	bool mExit;
};

