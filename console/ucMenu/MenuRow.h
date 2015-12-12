#ifndef MENUROW_H
#define MENUROW_H

#include <string>

#include "RowType.h"
#include "MyHelper.h"

using namespace std;

class MenuItem;

class MenuRow
{
	public:
		MenuRow(string s, RowType t = TEXT);
		string text;
		const RowType rowType;
		virtual string fullText();
		void show();
		void hide();
		bool hidden;
	protected:
	private:
		
};

#endif
