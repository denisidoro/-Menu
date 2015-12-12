#include "MyHelper.h"

int pow(int b, int n) {
	int i = 1;
	for (int j = 0; j < n; j++)
		i *= b;
	return i;
}

int numDigits(int number) {
	if (number == 0)
		return 1;
    int d = 0;
    if (number < 0) d = 1;
    while (number) {
        number /= 10;
        d++;
    }
    return d; 
}

String to_string(int number) {
    char buf[10];
    sprintf(buf, "%d", number);
    return buf;
}

String to_string(float number) {
    char buf[10];
    sprintf(buf, "%.2f", number);
    return buf;
}
