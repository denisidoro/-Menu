#include "Display.h"

Display::Display(LiquidCrystal* lc, int c, int r) 
	: lcd(lc), rows(r), cols(c) {
}

Display::~Display() {
}

void Display::clear() {
	lcd->clear();
}

void Display::print(String n) {
	lcd->print(n);
}

void Display::debug(String d) {
}

void Display::setCursor(int col, int row) {
    x = col;
    y = row;
    lcd->setCursor(col, row);
}

void Display::blink(bool b) {
	if (b)
		lcd->blink();
	else
		lcd->noBlink();
}

void Display::setup() {
	lcd->begin(cols, rows);
}

void Display::error(String msg) {
	return;
}

void Display::power(bool p) {
	if (p)
		lcd->display();
	else
		lcd->noDisplay();
}