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
	return rowCount;
}

MenuRow* MenuItem::getRow(int i) {
	if (i < rowCount)
		return rows[i];
	return new MenuRow("");
}


