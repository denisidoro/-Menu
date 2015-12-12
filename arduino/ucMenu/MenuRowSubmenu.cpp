#include "MenuRowSubmenu.h"

MenuRowSubmenu::MenuRowSubmenu(String s, MenuItem* c) 
	: MenuRow(s, SUBMENU), child(c) {
}

MenuItem* MenuRowSubmenu::getChild() {
	return child;
}

