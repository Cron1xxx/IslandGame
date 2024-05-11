#include "Frame.h"
#include "CTestView.h"

CFrame::CFrame() {
	mpCurrentView = new CTestView(this);
	mpKeyboardHandler = new CKeyboardHandler();
	mpKeyboardHandler->setListener((IKeyboardListener*)mpCurrentView);

}

void CFrame::run() {
	mpCurrentView->show();
}
