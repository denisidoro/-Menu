#include "MenuItem.h"

MenuItem::MenuItem(MenuItem* p) 
	: rowCount(0), parent(p) { //ctor
} 

MenuItem::~MenuItem() {} //dtor

void MenuItem::addRow(MenuRow* l) {
	if (rowCount >= MAX_MENU_ROWS)
		return;
	rows[rowCount] = l;
	rowCount++;
}

short int MenuItem::getRowCount() {
	//return rowCount;
	int count = 0;
	for (int i = 0; i < rowCount; i++) {
		if (!getRow(i, true)->hidden)
			count++;
	}
	return count;
}

MenuRow* MenuItem::getRow(int i, bool absolute) {

	if (i < rowCount) {
		if (absolute)
			return rows[i];
		else {
			int c = 0;
			for (int j = 0; j < rowCount; j++) {
				if (!rows[j]->hidden) {
					if (c == i)
						return rows[j];
					c++;
				}
			}
		}
	}

	return new MenuRow("");

}
