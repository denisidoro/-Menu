#include "MenuRow.h"

MenuRow::MenuRow(String s, RowType t) 
	: text(s), rowType(t), hidden(false) {
}

String MenuRow::fullText() {
	return text;
}

void MenuRow::show() {
	hidden = false;
}

void MenuRow::hide() {
	hidden = true;
}