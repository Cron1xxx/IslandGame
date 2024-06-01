#include "AbstractView.h"
#include <cstdio>

CAbstractView::CAbstractView(CGame** game, SIZE size, HANDLE hConsoleOutput) {
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
	mSurface->drawRect({ 0, 0, mpSize.cx - 1, mpSize.cy - 1 }, EFrameType::DOUBLE, F_WHITE);
	mSurface->drawText({3, 0}, " " + msCaption + " ", F_WHITE);
}

void CAbstractView::clean() {
	for (SHORT y = 1; y < mpSize.cy - 2; y++) {
		for (SHORT x = 1; x < mpSize.cx - 1; x++) {
			mSurface->drawChar({x, y}, ' ', F_WHITE|B_BLACK);
		}
	}
}

void CAbstractView::drawText(vector<CString> pText, EAlignment horizontalAlignment, EAlignment verticalAlignment, WORD attr) {
	if (pText.empty()) {
		return;
	}
	
	SHORT y, x;
	
	if (verticalAlignment == EAlignment::CENTER) {
		y = (mpSize.cy - 2) / 2 - pText.size() / 2 - 1;
		if (y < 1) {
			y = 1;
		}
	} else {
		y = 1;
	}

	for (auto line : pText) {
		if (horizontalAlignment == EAlignment::CENTER) {
			x = (mpSize.cx - 2) / 2 - line.GetLength() / 2;
			if (x < 1) {
				x = 1;
			}
		} else {
			x = 1;
		}
		mSurface->drawText({x, y}, line, attr);
		y++;
	}
}

void CAbstractView::drawBottomString() {
	CString text = msBottomString;
	SHORT maxTextLen = mpSize.cx - 4;
	if (msBottomString.GetLength() >= maxTextLen) {
		text = text.Left(maxTextLen);
	} else {
		for (int i = 0; i < maxTextLen - msBottomString.GetLength(); i++) {
			text += " ";
		}
	}
	mSurface->drawText({1, (SHORT)(mpSize.cy - 2)}, " " + text + " ", F_BLACK | B_WHITE);
}

void CAbstractView::ShowCursor(BOOL visible) {
	CONSOLE_CURSOR_INFO cursorInfo;
	GetConsoleCursorInfo(mhConsoleOutput, &cursorInfo);
	cursorInfo.bVisible = visible;
	SetConsoleCursorInfo(mhConsoleOutput, &cursorInfo);
}

void CAbstractView::SetCursorPosition(COORD pos) {
	SetConsoleCursorPosition(mhConsoleOutput, pos);
}

