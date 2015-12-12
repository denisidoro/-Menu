#include "Display.h"

Display::Display(TextLCD* lc, int c, int r) 
	: lcd(lc), rows(r), cols(c) {
}

Display::~Display() {
}

void Display::clear() {
	lcd->cls();
}

void Display::print(string n) {
	const char *cstr = n.c_str();
	lcd->printf(cstr);
}

void Display::debug(string d) {
}

void Display::setCursor(int col, int row) {
    x = col;
    y = row;
    lcd->locate(col, row);
}

void Display::blink(bool b) {
    lcd->setCursor(b ? TextLCD::CurOn_BlkOn : TextLCD::CurOff_BlkOff);
}

void Display::setup() {
    blink(false);
}

void Display::error(string msg) {
	return;
}

