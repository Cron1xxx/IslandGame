#include "SceneView.h"

CSceneView::CSceneView(CGame* game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput) {
	mpGame = game;
	msCaption = "Scene";
	drawCaption();
	msBottomString = formBottomString();
	drawBottomString();
	mSurface->drawRect({1, 5, mpSize.cx - 2, mpSize.cy - 3}, EFrameType::SINGLE, F_WHITE);
}

NEXT_VIEW_INFO CSceneView::show() {
	while (true) {
		mSurface->print();
		Sleep(100);
	}
	return NEXT_VIEW_INFO();
}

void CSceneView::keypressed(WORD keyCode) {

}

CString CSceneView::formBottomString() {
	CString str = "";
	str.AppendChar((char)27);
	str.AppendChar((char)24);
	str.AppendChar((char)26);
	str.AppendChar((char)25);
	str = str + " - Move, M - Main Menu";
	return str;
}
