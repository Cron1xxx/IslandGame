#pragma once

#include <Windows.h>
#include "KeyboardListener.h"

class CKeyboardHandler {
public:
	CKeyboardHandler();
	void setListener(IKeyboardListener* listener);
	void run();

private:
	IKeyboardListener* mpListener;
	
};

