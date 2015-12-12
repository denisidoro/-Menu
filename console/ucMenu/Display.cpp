#include "Display.h"

Display::Display(int c, int r) 
	: rows(r), cols(c) {
}

Display::~Display() {
}

void Display::clear() {
	for (int i = 0; i < rows; i++)
    	s[i] = "                ";
}

void Display::print(string n) {

	_sleep(REFRESH_SLEEP);
	
	// show error in invalid case
	if (x >= cols || y >= rows) {
		this->error("Out of bounds");
		return;
	}

	// trim, erase and insert
    n = n.substr(0, cols - x);
    s[y].erase(x, n.length());
    s[y].insert(x, n);

	// clear console
  	system("cls");
  	
  	// set output string
    string sep = string(cols, '=');
  	string text = "";
  	for (int i = 0; i < rows; i++) {
  		text += s[i];
  		if (i < rows - 1)
  			text += "\n";
	}
  	
  	// print
    cout << sep << endl << text << endl << sep << endl;
    
    // print debug
    cout << d << endl << endl; // debug

}

void Display::debug(string d) {
	this->d = d; 
}

void Display::setCursor(int col, int row) {
    x = col;
    y = row;
}

void Display::blink(bool o) {
	
	if (!o || x >= cols || y >= rows) 
		return;
	
	int cX = x;
	int cY = y;
	
	unsigned int w = 100; // ms
	char c = s[y][x];
	for (int i = 0; i < 3; i++) {
		_sleep(w);
		this->print("_");
		_sleep(w);
		string cs(1, c);
		this->print(cs);
	}
	
	this->setCursor(cX, cY);

}

void Display::setup() {
	//
}

void Display::power(bool p) {
	if (!p) {
		clear();
		setCursor(0, 0);
		print("");
	}
}

void Display::error(string msg) {
	this->clear();
	this->setCursor(0, 0);
	this->print("ERROR");
	this->setCursor(1, 0);
	this->print(msg);
}
