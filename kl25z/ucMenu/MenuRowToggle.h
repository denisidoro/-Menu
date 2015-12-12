#ifndef MENUROWTOGGLE_H
#define MENUROWTOGGLE_H

#include "MenuRow.h"
#include "ToggleOptions.h"

class MenuRowToggle : public MenuRow {
	public:
		MenuRowToggle(string, ToggleOptions*, int*);
		string fullText();
		int* var;
		void increase(int);
	protected:
	private:
		ToggleOptions* options;
};

#endif

