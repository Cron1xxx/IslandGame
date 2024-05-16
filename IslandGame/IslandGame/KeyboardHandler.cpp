#pragma once

#include <windows.h>
#include <stdio.h>


#include "KeyboardHandler.h"

CKeyboardHandler::CKeyboardHandler() {
	mpListener = nullptr;
}

void CKeyboardHandler::setListener(IKeyboardListener* listener) {
	mpListener = listener;
}

void CKeyboardHandler::run() {
	HANDLE hStdin;
	DWORD cNumRead, fdwMode, i;
	INPUT_RECORD irInBuf[128];
	KEY_EVENT_RECORD rKeyEventRecord;

	hStdin = GetStdHandle(STD_INPUT_HANDLE);

	if (hStdin == INVALID_HANDLE_VALUE)
		printf("Error GetStdHandle\n");

	while (true) {
		ReadConsoleInput(hStdin, irInBuf, 128, &cNumRead);
		for (i = 0; i < cNumRead; i++) {
			if (irInBuf[i].EventType == KEY_EVENT && irInBuf[i].Event.KeyEvent.bKeyDown) {
				if (mpListener) {
					mpListener->keypressed(irInBuf[i].Event.KeyEvent.wVirtualKeyCode);
				}
			}
		}
	}
}


