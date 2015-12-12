#ifndef TOGGLEOPTIONS_H
#define TOGGLEOPTIONS_H

#include <string>
using namespace std;

#define MAX_TOGGLE_OPTIONS 5

class ToggleOptions
{
	public:
		ToggleOptions(bool = false);
		void add(string, int);
		string getLabel(int);
		int getValue(int);
		int size();
		void clear();
	protected:
	private:
		string labels[MAX_TOGGLE_OPTIONS];
		int values[MAX_TOGGLE_OPTIONS];
		int optionCount;
		bool numbered;
		
};

#endif
