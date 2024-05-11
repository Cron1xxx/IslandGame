#pragma once

#include <Windows.h>
#include "KeyboardListener.h"

class CKeyboardHandler {
public:
	CKeyboardHandler();
	void setListener(IKeyboardListener* listener);

private:
	IKeyboardListener* mpListener;
	void run();
};

