#pragma once
#include "AbstractView.h"

class CSceneView : public CAbstractView {
public:
	CSceneView(CGame** game, SIZE size, HANDLE hConsoleOutput);
	EViewType show();
	void keypressed(WORD keyCode);
private:
	bool mExitToMainMenu;
	bool mExitToBagView;
	CString formBottomString();
	void renderField();
	void renderCharacter();
	void renderCharacterInfo();
	void renderCharacterInfoFrame();
	void renderActivitiesCaption();

};

