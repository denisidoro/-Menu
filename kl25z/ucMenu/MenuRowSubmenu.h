#ifndef MENUROWSUBMENU_H
#define MENUROWSUBMENU_H

#include "MenuRow.h"

class MenuRowSubmenu : public MenuRow {
	public:
		MenuRowSubmenu(string, MenuItem*);
		MenuItem* getChild();
	protected:
	private:
		MenuItem* child;
};

#endif

