#include "AbstractView.h"
#include <cstdio>

CAbstractView::CAbstractView(CGame* game, SIZE size, HANDLE hConsoleOutput) {
	mpGame = game;
	mpSize = size;
	mhConsoleOutput = hConsoleOutput;
	ShowCursor(FALSE);
	mSurface = new CSurface(size, hConsoleOutput);
	mSurface->fill(' ', F_BLACK);
	mSurface->drawRect({0, 0, mpSize.cx-1, mpSize.cy-1}, EFrameType::DOUBLE, F_WHITE);
}

CAbstractView::~CAbstractView() {
	delete mSurface;
}

void CAbstractView::drawCaption() {
	mSurface->drawText({3, 0}, " " + msCaption + " ", F_WHITE);
}

void CAbstractView::ShowCursor(BOOL visible) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mhConsoleOutput, &cursorInfo);
	cursorInfo.bVisible = visible;
	SetConsoleCursorInfo(mhConsoleOutput, &cursorInfo);
}

void CAbstractView::SetCursorPosition(COORD pos) {
	SetConsoleCursorPosition(mhConsoleOutput, {pos.X, pos.Y});
}

