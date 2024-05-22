#pragma once
#include "AbstractView.h"

class CSceneView : public CAbstractView {
public:
	CSceneView(CGame** game, SIZE size, HANDLE hConsoleOutput);
	NEXT_VIEW_INFO show();
	void keypressed(WORD keyCode);
private:
	bool mExitToMainMenu;
	CString formBottomString();
	void renderField();
	void renderCharacter();

};

