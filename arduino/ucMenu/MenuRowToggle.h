#ifndef MENUROWTOGGLE_H
#define MENUROWTOGGLE_H

#include "MenuRow.h"
#include "ToggleOptions.h"

class MenuRowToggle : public MenuRow {
	public:
		MenuRowToggle(String, ToggleOptions*, int*);
		String fullText();
		int* var;
		void increase(int);
	protected:
	private:
		ToggleOptions* options;
};

#endif

