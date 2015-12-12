#ifndef Display_H
#define Display_H

#include <string>
#include <stdlib.h>
#include <iostream>

#define MAX_DISPLAY_ROWS 6
#define REFRESH_SLEEP 0

using namespace std;

class Display
{
    public:
        Display(int, int);
        virtual ~Display();
        void clear();
        void print(string);
        void setCursor(int, int);
        void debug(string);
        void blink(bool o = true);
        void setup();
        void power(bool);
        int x, y;
    protected:
    private:
    	int rows, cols;
        string s[MAX_DISPLAY_ROWS];
        string d;
        void error(string);
};

#endif // Display_H
