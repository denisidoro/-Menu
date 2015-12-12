#include "ucMenu.h"

ucMenu::ucMenu(TextLCD* l, int c, int r) 
	: rows(r), cols(c), power(true), customMenuId(0) {
	display = new Display(l, c, r);
	display->setup();
}

void ucMenu::up() {
	
	// turn display on in case it is off
	if (!power) { display->power(true); power = true; return; }
	
	switch (currentMode) {
		case VAR:
			int order;
			order = r->text.length() + 2 + ((MenuRowVar*)r)->maxDigits() - display->x;
			((MenuRowVar*)r)->increase(pow(10, order));
			break;
		case TOGGLE:
			((MenuRowToggle*)r)->increase(1);
			break;
		default:
			currentRow--;
			if (currentRow < 0) {
				firstRow = currentMenu->getRowCount() - rows;
				if (firstRow < 0)
					firstRow = 0;
				currentRow = currentMenu->getRowCount() - 1;
			}
			break;
	}
	
}

void ucMenu::down() {
	
	// turn display on in case it is off
	if (!power) { display->power(true); power = true; return; }
	
	switch (currentMode) {
		case VAR:
			int order;
			order = r->text.length() + 2 + ((MenuRowVar*)r)->maxDigits() - display->x;
			((MenuRowVar*)r)->increase(-pow(10, order));
			break;
		case TOGGLE:
			((MenuRowToggle*)r)->increase(-1);
			break;
		default:
			currentRow++;
			if (currentRow >= currentMenu->getRowCount()) {
				firstRow = 0;
				currentRow = 0;
			}
			break;
	}
	
}

void ucMenu::left() {
	
	// turn display on in case it is off
	if (!power) { display->power(true); power = true; return; }
	
	switch (currentMode) {
		case VAR:
			if (display->x > r->text.length() + 3)
				display->x -= 1;
			display->blink();
			break;
		default:
			switch (r->rowType) {
				case TOGGLE:
					select();
					up();
					cancel();
					break;
				default:
					break;
			}
			break;
	}
	
}

void ucMenu::right() {
	
	// turn display on in case it is off
	if (!power) { display->power(true); power = true; return; }
	 
	switch (currentMode) {
		case VAR:
			if (display->x < ((MenuRowVar*)r)->text.length() + 3 + ((MenuRowVar*) r)->maxDigits() - 1)
				display->x += 1;
			display->blink();
			break;
		default:
			switch (r->rowType) {
				case TOGGLE:
					select();
					down();
					cancel();
					break;
				default:
					break;
			}
			break;
	}
	
}

void ucMenu::select() {
	
	// turn display on in case it is off
	if (!power) { display->power(true); power = true; return; }
	
	switch (currentMode) {
		case TOGGLE:
			cancel(true);
			return;
		case MESSAGE:
			parentRow = 0;
			this->setMenu();
			break;
		case VAR:
			cancel(true);
			return;
		default:
			break;
	}
	
	switch (r->rowType) {
		case SUBMENU:
			this->setMenu(((MenuRowSubmenu*)r)->getChild());
			break;
		case VAR:
			if (!((MenuRowVar*)r)->isReadOnly()) {
				temp = *((MenuRowVar*)r)->var;
				display->setCursor(r->text.length() + 3, currentRow - firstRow);
				display->blink(true);
				currentMode = VAR;
			}
			break;
		case TOGGLE:
			temp = *((MenuRowToggle*)r)->var;
			display->setCursor(r->text.length() + 3, currentRow - firstRow);
			display->blink(true);
			currentMode = TOGGLE;
			break;
		default:
			break;
	}
	
}

void ucMenu::cancel(bool emulated) {
	
	switch (currentMode) {
		case NONE:
			if (currentMenu == root) {	// turn display off
				display->power(false);
				power = false;
				return;
			}
			else
				this->setMenu();
			break;
		case MESSAGE:
			parentRow = 0;
			this->setMenu();
			break;
		case TOGGLE:
			if (!emulated)
				*((MenuRowToggle*)r)->var = temp;
			currentMode = NONE;
			break;
		case VAR:
			if (!emulated)
				*((MenuRowVar*)r)->var = temp;
			currentMode = NONE;
			break;
		default:
			currentMode = NONE;
			break;
	}
	
	display->blink(false);
	customMenuId = 0;
	
}

void ucMenu::setRoot(MenuItem* m) {
	root = m;
	this->setMenu(root);
}

void ucMenu::refresh() {
	
	// don't do anything if display is off
	if (!power)
		return;
	
	changed = false;
	
	// init vars
	MenuRow* l;
	int cX = display->x;
	int cY = display->y;
	
	// clear disp
	display->clear();
	
	// set first row
	if (currentRow >= firstRow && currentRow < firstRow + rows) {}
	else {
		if (currentRow < firstRow)
			firstRow--;
		else
			firstRow++;
	}
	
	// get and print rows
	for (int i = firstRow; i < firstRow + rows; i++) {
		
		l = currentMenu->getRow(i);
		display->setCursor(1, i - firstRow);
		display->print(l->fullText());
		
	}
	
	// set a '>' to current row
	display->setCursor(0, currentRow - firstRow);
	display->print(">");
	
	// set row indicators 
	if (firstRow > 0) {
		display->setCursor(cols - 1, 0);
		display->print(".");
	}
	if (firstRow + rows < currentMenu->getRowCount()) {
		display->setCursor(cols - 1, rows - 1);
		display->print(".");
	}	
	
	// debug...
	
	// set cursor to its initial position
	display->setCursor(cX, cY);
	
	// store current row
	r = currentMenu->getRow(currentRow);
		
}

void ucMenu::setMenu(MenuItem* m, int nextRow) {
	
	// default args
	if (m == NULL)
		return this->setMenu(const_cast<MenuItem*>(currentMenu->parent), parentRow);
	
	parentRow = currentRow;
	currentMenu = m;
	currentRow = nextRow;
	firstRow = nextRow - rows + 1;
	if (firstRow < 0)
		firstRow = 0;
	currentMode = NONE;
	
	// flag indicating that menu has been changed
	changed = true;
	
	
}

void ucMenu::message(string msg, MenuItem* targetMenu) {
	
	// default arg
	if (targetMenu == NULL)
		targetMenu = root;
	
	// init vars
	int start = 0;
	int len;
	string s;
	MenuItem* messageMenu = new MenuItem(targetMenu);
	
	// setup message menu
	while (start < msg.length()) {
		
		len = msg.length() - start;
		if (len > cols - 2)
			len = cols - 2;
			
		s = msg.substr(start, len);
		messageMenu->addRow(new MenuRow(s));
		
		start += len;
		
	}
	
	// set current menu
	this->setMenu(messageMenu);
	this->currentMode = MESSAGE;
	this->refresh();
	
}

int ucMenu::getCurrentRow() {
	return currentRow;
}

RowType ucMenu::getCurrentMode() {
	return currentMode;
}

MenuItem* ucMenu::nextMenu() {
	
	if (r->rowType == SUBMENU)
		return ((MenuRowSubmenu*)r)->getChild();
		
	return currentMenu;	
		
}

bool ucMenu::lastRow() {
	return currentRow == currentMenu->getRowCount() - 1;
}

