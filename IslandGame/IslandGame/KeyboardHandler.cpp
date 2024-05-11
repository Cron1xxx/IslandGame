#include "KeyboardHandler.h"

CKeyboardHandler::CKeyboardHandler() {
}

void CKeyboardHandler::setListener(IKeyboardListener* listener) {
	mpListener = listener;
}

void CKeyboardHandler::run() {
	//TODO: implement this method
	WORD keyCode = 5;
	 mpListener->keypressed(keyCode);
	// ...

}


