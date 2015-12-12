#include "MenuRow.h"

MenuRow::MenuRow(string s, RowType t) 
	: text(s), rowType(t) {
}

string MenuRow::fullText() {
	return text;
}

