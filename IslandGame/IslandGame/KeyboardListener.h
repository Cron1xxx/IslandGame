#pragma once
#include <Windows.h>

class IKeyboardListener {
public:
	virtual void keypressed(WORD keyCode) = 0;
};

