#include "MenuRowVar.h"

MenuRowVar::MenuRowVar(String s, int *v, String u, int mn, int mx) 
	: MenuRow(s, VAR), _min(mn), _max(mx), var(v), units(u) {
}

int MenuRowVar::maxDigits() {
	return numDigits(_max);
}

void MenuRowVar::increase(int v) {
	
	if (isReadOnly())
		return;
	
	*this->var += v;
	if (*this->var > _max)
		*this->var = _max;
	if (*this->var < _min)
		*this->var = _min;
		
}

void MenuRowVar::update(int v) {
	*this->var = v;
}

String MenuRowVar::fullText() {
	String s = this->text + ": ";
	for (int i = 0; i < this->maxDigits() - numDigits(*this->var); i++)
		s += '0';
	s += to_string(*this->var) + units;
	return s;
}

bool MenuRowVar::isReadOnly() {
	return (_min == _max);
}

