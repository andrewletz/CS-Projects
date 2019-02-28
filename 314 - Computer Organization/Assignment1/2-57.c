#include <stdio.h>

/*
 * Andrew Letz, September 27th 2017
 * Used code from figure 2.4 in Computer Systems - A 
 * Programmer's Perspective (Second Edition). Not much to
 * explain, basically just changed some text and implemented
 * simple test cases.
 */

typedef unsigned char* byte_pointer;

void show_bytes(byte_pointer start, int len) {
	int i;
	for (i = 0; i < len; i++)
		printf(" %.2x", start[i]);
	printf("\n");
}

void show_short(short x) {
	show_bytes((byte_pointer) &x, sizeof(int));
}

void show_long(long x) {
	show_bytes((byte_pointer) &x, sizeof(float));
}

void show_double(double x) {
	show_bytes((byte_pointer) &x, sizeof(double));
}

int main(void)
{
    short newshort = 8;
    long newlong = 256;
    double newdouble = 3.14;

    show_short(newshort);
    show_long(newlong);
    show_double(newdouble);

    return 0;
}