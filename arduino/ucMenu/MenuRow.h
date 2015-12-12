#ifndef MENUROW_H
#define MENUROW_H

#include "Arduino.h"

#include "RowType.h"
#include "MyHelper.h"

using namespace std;

class MenuItem;

class MenuRow
{
	public:
		MenuRow(String s, RowType t = TEXT);
		String text;
		const RowType rowType;
		virtual String fullText();
		void show();
		void hide();
		bool hidden;
	protected:
	private:
		
};

#endif
