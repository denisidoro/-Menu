#include "MenuRowToggle.h"

MenuRowToggle::MenuRowToggle(string s, ToggleOptions* o, int* v) 
	: MenuRow(s, TOGGLE), var(v), options(o) {
}

string MenuRowToggle::fullText() {
	return this->text + ": " + options->getLabel(*var);
}

void MenuRowToggle::increase(int v) {
	*var += v;
	if (*var < 0)
		*var = options->size() - 1;
	if (*var >= options->size())
		*var = 0;
}


