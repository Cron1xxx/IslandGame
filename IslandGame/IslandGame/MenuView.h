#pragma once
#include "AbstractView.h"
#include <vector>

using namespace std;
class CMenuView : public CAbstractView {
private:
	class CMenu {
	public:
		class CAbstractMenuItem {
		public:
			CAbstractMenuItem(CString caption, BOOL enable, CGame** game);
			CString msCaption;
			BOOL mbEnable;
			CGame** mpGame;

			virtual EViewType action() = 0;
		};

		class CNewGameMenuItem : public CAbstractMenuItem {
		public:
			CNewGameMenuItem(CString caption, BOOL enable, CGame** game);
			EViewType action();
		};

		class CLoadGameMenuItem : public CAbstractMenuItem {
		public:
			CLoadGameMenuItem(CString caption, BOOL enable, CGame** game);
			EViewType action();
		};

		class CSaveGameMenuItem : public CAbstractMenuItem {
		public:
			CSaveGameMenuItem(CString caption, BOOL enable, CGame** game);
			EViewType action();
		};

		class CContinueGameMenuItem : public CAbstractMenuItem {
		public:
			CContinueGameMenuItem(CString caption, BOOL enable, CGame** game);
			EViewType action();
		};


		class CExitMenuItem : public CAbstractMenuItem {
		public:
			CExitMenuItem(CString caption, BOOL enable, CGame** game);
			EViewType action();
		};
		
		CMenu(CGame** game);
		vector<CAbstractMenuItem*> mvMenuItems;
		SHORT mCurrentPosition;
		SHORT mMaxItemCaptionLength = 0;
		//scroll menu UP or DOWN
		void scroll(EMenuScroll direction);
		EViewType action();

	private:
		CAbstractMenuItem* mCurrentItem;
		void addItem(CAbstractMenuItem* item);
		void setCurrentPosition(SHORT ind);
	};
public:
	CMenuView(CGame** game, SIZE size, HANDLE hConsoleOutput);
	EViewType show();
	void keypressed(WORD keyCode);

private:
	CMenu* mMenu;
	bool mExit;
	void drawMenu();
	void render();
	CString formBottomString();
};

