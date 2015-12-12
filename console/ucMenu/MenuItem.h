#ifndef MENUITEM_H
#define MENUITEM_H

#define MAX_MENU_ROWS 10

#include "MenuRow.h"
#include "MenuRowVar.h"
#include "MenuRowToggle.h"
#include "MenuRowSubmenu.h"

class MenuItem
{
    public:
        MenuItem(MenuItem* = NULL);
        virtual ~MenuItem();
        void addRow(MenuRow*);
        MenuRow* getRow(int, bool = false);
        short int getRowCount();
    	const MenuItem* parent;
    protected:
    private:
    	MenuRow* rows[MAX_MENU_ROWS];
    	short int rowCount;
};

#endif // MENUITEM_H
