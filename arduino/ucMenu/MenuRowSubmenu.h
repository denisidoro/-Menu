#ifndef MENUROWSUBMENU_H
#define MENUROWSUBMENU_H

#include "MenuRow.h"

class MenuRowSubmenu : public MenuRow {
	public:
		MenuRowSubmenu(String, MenuItem*);
		MenuItem* getChild();
	protected:
	private:
		MenuItem* child;
};

#endif

