#ifndef MENUROWVAR_H
#define MENUROWVAR_H

#include "MenuRow.h"

class MenuRowVar : public MenuRow {
	public:
		MenuRowVar(String, int*, String = "", int = -1, int = -1);
		int* var;
		int maxDigits();
		void increase(int);
		void update(int);
		String fullText();
		bool isReadOnly();
	protected:
	private:
		int _min, _max;
		String units;
};

#endif

