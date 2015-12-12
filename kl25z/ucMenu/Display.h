#ifndef Display_H
#define Display_H

#include "TextLCD.h"

#include <string>
#include <stdlib.h>

#define MAX_DISPLAY_ROWS 6
#define REFRESH_SLEEP 0

using namespace std;

class LiquidCrystal {
	public:
	private:
};

class Display
{
    public:
        Display(TextLCD*, int, int);
        virtual ~Display();
        TextLCD* lcd;
        void clear();
        void print(string);
        void setCursor(int, int);
        void debug(string);
        void blink(bool o = true);
        void setup();
        int x, y;
    protected:
    private:
    	int rows, cols;
        string s[MAX_DISPLAY_ROWS];
        string d;
        void error(string);
};

#endif // Display_H

