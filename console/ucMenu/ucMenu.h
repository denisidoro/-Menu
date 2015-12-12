#ifndef UCMENU_H
#define UCMENU_H

#include <string.h>

#include "MenuItem.h"
#include "Display.h"
#include "MyHelper.h"

class ucMenu {
	public:
		ucMenu(int, int);
		void up();
		void down();
		void left();
		void right();
		void select();
		void cancel(bool = false);
		void setRoot(MenuItem*);
		void refresh();
		void message(string, MenuItem* = NULL);
		MenuItem* currentMenu;
		int getCurrentRow();
		int currentRow; 			// current row index
		bool changed;
		RowType getCurrentMode();
		void setMenu(MenuItem* = NULL, int = 0);
		Display* display;
		int customMenuId;			// 0: native
		MenuItem* nextMenu();
		bool lastRow();
	protected:
	private:
		int parentRow; 				// previous menu row index
		RowType currentMode;
		int firstRow;
		MenuItem* root;
		int rows, cols;
		MenuRow* r; 				// current menu row
		int pow10(int);
		bool power;
		int temp;
};

#endif
