#pragma once

#include "AbstractView.h"

class CTestView : public CAbstractView{
public:
	CTestView(CGame* game);
	virtual std::string show();
	virtual void keypressed(WORD keyCode);
	
private:
	bool mExit;
};

