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
		string fullText();
	protected:
	private:
		
};

#endif

