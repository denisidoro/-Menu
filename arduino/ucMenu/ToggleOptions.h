#ifndef TOGGLEOPTIONS_H
#define TOGGLEOPTIONS_H

using namespace std;

#include "MyHelper.h"
#define MAX_TOGGLE_OPTIONS 5

class ToggleOptions
{
	public:
		ToggleOptions(bool = false);
		void add(String, int);
		String getLabel(int);
		int getValue(int);
		int size();
		void clear();
	protected:
	private:
		String labels[MAX_TOGGLE_OPTIONS];
		int values[MAX_TOGGLE_OPTIONS];
		int optionCount;
		bool numbered;
		
};

#endif

