#ifndef Display_H
#define Display_H

#include "Arduino.h"
#include <LiquidCrystal.h>

#include <stdlib.h>

#define MAX_DISPLAY_ROWS 6
#define REFRESH_SLEEP 0

using namespace std;

class Display
{
    public:
        Display(LiquidCrystal*, int, int);
        virtual ~Display();
        LiquidCrystal* lcd;
        void clear();
        void print(String);
        void setCursor(int, int);
        void debug(String);
        void blink(bool o = true);
        void setup();
        void power(bool);
        int x, y;
    protected:
    private:
    	int rows, cols;
        String s[MAX_DISPLAY_ROWS];
        String d;
        void error(String);
};

#endif // Display_H

