#include <stdio.h>

/*
 * Andrew Letz, September 30th 2017
 */

/* 
 * Return 1 when any odd bit of x equals 1; 0 otherwise.
 * Assume w=32. 
 */
int any_odd_one(unsigned x) {
    // Create a mask with every odd bit as a 1
	unsigned int mask = 0b10101010101010101010101010101010;

    // If any of the bits are left over after the &, the result will be != 0,
    // proving it does in fact contain a 1 on an odd bit.
    return (x & mask) != 0;
}

int main(void)
{
    printf("%X: %i\n", 0x0, any_odd_one(0x0));
    printf("%X: %i\n", 0x1, any_odd_one(0x1));
    printf("%X: %i\n", 0x2, any_odd_one(0x2));
    printf("%X: %i\n", 0x3, any_odd_one(0x3));
    printf("%X: %i\n", 0xFFFFFFFF, any_odd_one(0xFFFFFFFF));
    printf("%X: %i", 0x55555555, any_odd_one(0x55555555));

    return 0;
}