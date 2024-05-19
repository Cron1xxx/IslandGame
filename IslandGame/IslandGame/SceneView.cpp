#include "SceneView.h"

CSceneView::CSceneView(CGame* game, SIZE size, HANDLE hConsoleOutput) : CAbstractView(game, size, hConsoleOutput) {
	msCaption = "Scene";
	drawCaption();
	mSurface->drawRect({1, 5, mpSize.cx - 2, mpSize.cy - 3}, EFrameType::SINGLE, F_WHITE);
}

NEXT_VIEW_INFO CSceneView::show() {
	while (true) {
		mSurface->print();
		Sleep(100);
	}
	return NEXT_VIEW_INFO();
}

void CSceneView::keypressed(WORD keyCode) {}
