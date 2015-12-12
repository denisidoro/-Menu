#include "MenuRowVar.h"

MenuRowVar::MenuRowVar(string s, int *v, string u, int mn, int mx) 
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

string MenuRowVar::fullText() {
	return this->text + ": " + string(this->maxDigits() - numDigits(*this->var), '0') + to_string(*this->var) + units;
}

bool MenuRowVar::isReadOnly() {
	return (_min == _max);
}

