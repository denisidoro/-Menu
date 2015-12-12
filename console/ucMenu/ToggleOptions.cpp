#include "ToggleOptions.h"

ToggleOptions::ToggleOptions(bool n)
	: numbered(n) {
}

void ToggleOptions::add(string s, int i) {
	if (optionCount >= MAX_TOGGLE_OPTIONS)
		return;
	labels[optionCount] = s;
	values[optionCount] = i;
	optionCount++;
}

int ToggleOptions::getValue(int i) {
	return values[i];
}

string ToggleOptions::getLabel(int i) {
	return (numbered) ? 
		to_string(i) + '_' + labels[i] :
		labels[i];
}

int ToggleOptions::size() {
	return optionCount;
}

void ToggleOptions::clear() {
	optionCount = 0;
}
