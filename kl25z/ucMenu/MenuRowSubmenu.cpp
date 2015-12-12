#include "MenuRowSubmenu.h"

MenuRowSubmenu::MenuRowSubmenu(string s, MenuItem* c) 
	: MenuRow(s, SUBMENU), child(c) {
}

MenuItem* MenuRowSubmenu::getChild() {
	return child;
}

