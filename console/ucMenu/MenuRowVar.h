#ifndef MENUROWVAR_H
#define MENUROWVAR_H

#include "MenuRow.h"

class MenuRowVar : public MenuRow {
	public:
		MenuRowVar(string, int*, string = "", int = -1, int = -1);
		int* var;
		int maxDigits();
		void increase(int);
		void update(int);
		string fullText();
		bool isReadOnly();
	protected:
	private:
		int _min, _max;
		string units;
};

#endif
