#pragma once

#include "View.h"
#include "KeyboardListener.h"
#include "Frame.h"

class CTestView : public IView, public IKeyboardListener{
public:
	CTestView(CFrame* frame);
	void show();
	void keypressed(WORD keyCode);
private:
	CFrame* mpFrame;
};

