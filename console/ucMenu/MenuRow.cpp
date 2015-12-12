#include "MenuRow.h"

MenuRow::MenuRow(string s, RowType t) 
	: text(s), rowType(t), hidden(false) {
}

string MenuRow::fullText() {
	return text;
}

void MenuRow::show() {
	hidden = false;
}

void MenuRow::hide() {
	hidden = true;
}